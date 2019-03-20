#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>

#include "comm_def.h"
#include "miaosha.pb.h"
#include "miaosha.grpc.pb.h"
#include "CRedisPoolMgr.h"
#include "CMysqlPoolMgr.h"
#include "CMiaoshaServer.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using miaosha::MiaoshaRequest;
using miaosha::MiaoshaResponse;
using miaosha::MiaoshaService;

void initMysqlData(CMysqlPoolMgr* mysqlPool)
{
    MYSQL * mysqlConn = mysqlPool->getMysqlConn();
    if (NULL == mysqlConn)
    {
        std::cout << "get mysql connect fail!" << std::endl;
        exit(1);
    }

    char szSql[MAX_SQL_LEN];

    //建立库
    snprintf(szSql, sizeof(szSql),
        "CREATE DATABASE IF NOT EXISTS miaosha;");
    std::string strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "create database miaosha error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    //建立商品库存表
    memset(szSql, 0, MAX_SQL_LEN);
    snprintf(szSql, sizeof(szSql),
        "CREATE TABLE IF NOT EXISTS miaosha.t_goods_stock ("
        "`Fstock_id` varchar(16) NOT NULL default '',"
        "`Fgoods_name` varchar(64) NOT NULL default '',"
        "`Fstock_num` int NOT NULL default 0 ,"
        "PRIMARY KEY(`Fstock_id`)"
        ") ENGINE = InnoDB DEFAULT CHARSET = latin1;");
    strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "create table miaosha.t_goods_stock error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    //清空商品库存表
    memset(szSql, 0, MAX_SQL_LEN);
    snprintf(szSql, sizeof(szSql),
        "TRUNCATE TABLE miaosha.t_goods_stock;");
    strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "truncate table miaosha.t_goods_stock error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    //写入测试数据到表中
    memset(szSql, 0, MAX_SQL_LEN);
    snprintf(szSql, sizeof(szSql),
        "INSERT INTO miaosha.t_goods_stock(Fstock_id, Fgoods_name, Fstock_num) "
        "VALUES ('%s', 'test goods', 50);", STOCK_ID);
    strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "insert into miaosha.t_goods_stock error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    //建立秒杀订单表
    snprintf(szSql, sizeof(szSql),
        "CREATE TABLE IF NOT EXISTS miaosha.t_miaosha_order ("
        "`Flist_id` varchar(32) NOT NULL default '' ,"
        "`Fopenid` varchar(32) NOT NULL default '' ,"
        "`Fstock_id` varchar(16) NOT NULL default '' ,"
        "`Fstatus` tinyint NOT NULL default 0 ,"
        "PRIMARY KEY(`Flist_id`),"
        "UNIQUE KEY(`Fopenid`,`Fstock_id`)"
        ") ENGINE = InnoDB DEFAULT CHARSET = latin1 ;");
    strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "create table miaosha.t_miaosha_order error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    //清空秒杀订单表
    memset(szSql, 0, MAX_SQL_LEN);
    snprintf(szSql, sizeof(szSql),
        "TRUNCATE TABLE miaosha.t_miaosha_order");
    strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "truncate miaosha.t_miaosha_order error:" << mysql_error(mysqlConn) << std::endl;
        exit(1);
    }

    mysqlPool->closeMysqlConn(mysqlConn);
}

void initRedisData(CMysqlPoolMgr* mysqlPool, CRedisPoolMgr* redisPool)
{
    MYSQL * mysqlConn = mysqlPool->getMysqlConn();
    redisContext * redisConn = redisPool->getRedisConn();
    if (NULL == mysqlConn)
    {
        std::cout << "get mysql connect fail!" << std::endl;
        exit(1);
    }

    if (NULL == redisConn)
    {
        std::cout << "get redis connect fail!" << std::endl;
        exit(1);
    }


    //清空redis数据
    redisReply *reply = NULL;
    reply = (redisReply *)redisCommand(redisConn, "DEL %s", "goods_stock_num");
    freeReplyObject(reply);
    reply = NULL;

    reply = (redisReply *)redisCommand(redisConn, "DEL %s", "miaosha_user");
    freeReplyObject(reply);
    reply = NULL;

    //查询商品库存信息
    char szSql[MAX_SQL_LEN];
    snprintf(szSql, sizeof(szSql),
        "SELECT Fstock_id,Fgoods_name,Fstock_num FROM miaosha.t_goods_stock LIMIT 1");
    std::string strSql = std::string(szSql);
    if (mysql_query(mysqlConn, strSql.c_str()))
    {
        std::cout << "query goods stock failed!" << std::endl;
        exit(1);
    }
    else
    {
        MYSQL_RES* pRes = mysql_store_result(mysqlConn);
        int iRow = mysql_num_rows(pRes);
        if (1 != iRow)
        {
            std::cout << "query goods stock failed!" << std::endl;
            exit(1);
        }

        MYSQL_ROW row = mysql_fetch_row(pRes);
        std::string strStockId = row[0];
        std::string strGoodsName = row[1];
        int iStockNum = atoi(row[2]);
        mysql_free_result(pRes);

        //刷新商品库存信息到redis
        std::string strStockNum = std::to_string(iStockNum);
        reply = (redisReply *)redisCommand(redisConn, "SET %s %s", "goods_stock_num", strStockNum.c_str());

        if (reply != NULL
            && reply->type == REDIS_REPLY_STATUS
            && (strcasecmp(reply->str, "OK") == 0))
        {
            std::cout << "set goods_stock_num to redis success!" << std::endl;
            freeReplyObject(reply);
            reply = NULL;
        }
        else
        {
            std::cout << "set goods_stock_num to redis fail" << std::endl;
            if (reply != NULL)
            {
                std::cout << "error message:" << redisConn->errstr << std::endl;
                freeReplyObject(reply);
                reply = NULL;
            }
        }
    }

    mysqlPool->closeMysqlConn(mysqlConn);
    redisPool->closeRedisConn(redisConn);
}

int main(int argc, char** argv)
{
    //初始化redis
    CRedisPoolMgr* redisPool = CRedisPoolMgr::getInstance();
    redisPool->setHost(REDIS_IP);
    redisPool->setPort(REDIS_PORT);
    redisPool->setMaxConnNum(REDIS_MAX_CONN_NUM);

    //初始化数据库
    CMysqlPoolMgr* mysqlPool = CMysqlPoolMgr::getInstance();
    mysqlPool->setHost(MYSQL_IP);
    mysqlPool->setPort(MYSQL_PORT);
    mysqlPool->setUsr(MYSQL_USR);
    mysqlPool->setPwd(MYSQL_PWD);
    mysqlPool->setMaxConnNum(MYSQL_MAX_CONN_NUM);

    //初始化数据
    initMysqlData(mysqlPool);
    initRedisData(mysqlPool, redisPool);

    //启动server
    CMiaoshaServer miaoshaServer;
    miaoshaServer.setAddress(SERVER_ADDR);
    miaoshaServer.setMysqlPoolMgr(mysqlPool);
    miaoshaServer.setRedisPoolMgr(redisPool);
    miaoshaServer.setThreadCount(SERVER_THREAD_NUM);
    miaoshaServer.startMiaoshaServer();

    //释放资源
    delete redisPool;
    delete mysqlPool;

    return 0;
}
