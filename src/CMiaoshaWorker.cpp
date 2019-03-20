#include "CMiaoshaWorker.h"

const std::string getNonceStr(int iLen/* = 32*/)
{
    const std::string chars = "0123456789";
    int maxPos = chars.length();
    std::string noceStr = "";

    for (int i = 0; i < iLen; i++)
    {
        noceStr += chars.at(rand() % maxPos);
    }

    return noceStr;
}

CMiaoshaWorker::CMiaoshaWorker(MiaoshaService::AsyncService* service, ServerCompletionQueue* cq, CRedisPoolMgr* redisPool, CMysqlPoolMgr* mysqlPool)
: m_service(service), m_cq(cq), m_responder(&m_ctx), m_status(CREATE), m_redisPool(redisPool), m_mysqlPool(mysqlPool)
{
    excute();
}

void CMiaoshaWorker::excute()
{
    std::cout << "tid:" << pthread_self() << " CMiaoshaServer::excute status:" << m_status << std::endl;
    //处理业务逻辑
    if (CREATE == m_status)
    {
        m_status = PROCESS;
        m_service->Requestmiaosha(&m_ctx, &m_request, &m_responder, m_cq, m_cq, this);
    }
    else if (PROCESS == m_status)
    {
        new CMiaoshaWorker(m_service, m_cq, m_redisPool, m_mysqlPool);

        std::cout << "tid:" << pthread_self() << " deal start!" << std::endl;
        redisContext* redisConn = m_redisPool->getRedisConn();
        MYSQL* mysqlConn = m_mysqlPool->getMysqlConn();
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

        std::string strUserOpenid = m_request.user_openid();
        std::string strUserSession = m_request.user_session();
        std::cout << "strUserOpenid:" << strUserOpenid << std::endl;
        std::cout << "strUserSession:" << strUserSession << std::endl;

        //校验用户登录态
        checkUserLoginStatus(strUserOpenid, strUserSession);

        //检查用户是否已经秒杀成功
        if (checkUserMiaoshaSucc(strUserOpenid, redisConn, mysqlConn))
        {
            m_response.set_result("FAIL");
            m_response.set_ret_msg("User already miaosha succ!");
        }
        else
        {
            //继续秒杀
            miaoshaGoods(strUserOpenid, redisConn, mysqlConn);
        }

        m_status = FINISH;
        m_responder.Finish(m_response, Status::OK, this);
        m_redisPool->closeRedisConn(redisConn);
        m_mysqlPool->closeMysqlConn(mysqlConn);
    }
    else
    {
        GPR_ASSERT(m_status == FINISH);
        std::cout << "tid:" << pthread_self() << " deal finish!" << std::endl;
        delete this;
    }
}

void CMiaoshaWorker::checkUserLoginStatus(const std::string& strUserOpenid, const std::string& strUserSession)
{
    //校验用户登录态信息，此处省略实现
    return;
}

bool CMiaoshaWorker::checkUserMiaoshaSucc(const std::string& strUserOpenid, redisContext* redisConn, MYSQL* mysqlConn)
{
    if (NULL != redisConn)
    {
        //检查redis该用户是否已经秒杀成功
        redisReply * reply = (redisReply *)redisCommand(redisConn, "HGET miaosha_user %s", strUserOpenid.c_str());
        if (reply != NULL
            && reply->type == REDIS_REPLY_STRING
            && reply->str != NULL)
        {
            std::cout << "usr alread miaosha succ!" << std::endl;
            freeReplyObject(reply);
            return true;
        }
        else
        {
            freeReplyObject(reply);
            return false;
        }
    }
    else
    {
        //降级检查DB该用户是否已经秒杀成功
        char szSql[MAX_SQL_LEN];
        snprintf(szSql, sizeof(szSql),
            "SELECT Flist_id FROM miaosha.t_miaosha_order "
            "WHERE Fopenid = '%s' AND Fstock_id = '%s'",
            strUserOpenid.c_str(), STOCK_ID);
        std::string strSql = std::string(szSql);
        if (mysql_query(mysqlConn, strSql.c_str()))
        {
            std::cout << "query miaosha order failed!" << std::endl;
            return false;
        }
        else
        {
            MYSQL_RES* pRes = mysql_store_result(mysqlConn);
            int iRow = mysql_num_rows(pRes);
            if (1 == iRow)
            {
                MYSQL_ROW row = mysql_fetch_row(pRes);
                std::string strListId = row[0];
                std::cout << "usr alread miaosha succ! list_id:" << strListId << std::endl;
                mysql_free_result(pRes);
                return true;
            }
            else if (0 == iRow)
            {
                std::cout << "usr can do miaosha!" << std::endl;
                mysql_free_result(pRes);
                return false;
            }
            else
            {
                //理论上不应该走入该分支，DB唯一索引能拦截
                std::cout << "usr miaosha order > 1!" << std::endl;
                mysql_free_result(pRes);
                return true;
            }
        }
    }
}

void CMiaoshaWorker::miaoshaGoods(const std::string& strUserOpenid, redisContext* redisConn, MYSQL* mysqlConn)
{
    if (NULL == redisConn)
    {
        miaoshaGoodsInDB(strUserOpenid, mysqlConn);
        return;
    }

    //采用redis进行拦量，减少到DB的并发
    if (miaoshaGoodsInRedis(strUserOpenid, redisConn))
    {
        miaoshaGoodsInDB(strUserOpenid, mysqlConn);
    }

    return;
}

bool CMiaoshaWorker::miaoshaGoodsInRedis(const std::string& strUserOpenid, redisContext* redisConn)
{
    int iRetryTimes = 3;
    do
    {
        //查询redis当前库存数量
        redisReply* watchReply = (redisReply *)redisCommand(redisConn, "WATCH %s", "goods_stock_num");
        redisReply* getReply = (redisReply *)redisCommand(redisConn, "GET %s", "goods_stock_num");
        int iCurGoodsStockNum = 0;

        if (watchReply != NULL
            && getReply != NULL
            && watchReply->type == REDIS_REPLY_STATUS
            && (strcasecmp(watchReply->str, "OK") == 0))
        {
            iCurGoodsStockNum = atoi(getReply->str);
            freeReplyObject(watchReply);
            freeReplyObject(getReply);
        }
        else
        {
            freeReplyObject(watchReply);
            freeReplyObject(getReply);
            break;
        }

        if (iCurGoodsStockNum > 0)
        {
            //有库存，可以继续秒杀
            redisReply *multiReply = (redisReply *)redisCommand(redisConn, "MULTI");
            if (multiReply != NULL
                && multiReply->type == REDIS_REPLY_STATUS
                && (strcasecmp(multiReply->str, "OK") == 0))
            {
                //减库存，记录秒杀成功用户
                redisCommand(redisConn, "DECR %s", "goods_stock_num");
                redisCommand(redisConn, "HMSET miaosha_user %s %s", strUserOpenid.c_str(), strUserOpenid.c_str());

                //提交
                redisReply *execReply = (redisReply *)redisCommand(redisConn, "EXEC");
                if (execReply != NULL
                    && execReply->type == REDIS_REPLY_ARRAY
                    && (execReply->elements > 1))
                {
                    freeReplyObject(execReply);
                    return true;
                }
                else
                {
                    //重试
                    --iRetryTimes;
                    if (execReply != NULL)
                    {
                        freeReplyObject(execReply);
                    }
                    redisCommand(redisConn, "UNWATCH");
                    continue;
                }
            }
        }
        else
        {
            //库存不足，秒杀失败
            redisCommand(redisConn, "UNWATCH");
            break;
        }
    } while (iRetryTimes > 0);

    m_response.set_result("FAIL");
    m_response.set_ret_msg("user miaosha fail!");
    return false;
}

void CMiaoshaWorker::miaoshaGoodsInDB(const std::string& strUserOpenid, MYSQL* mysqlConn)
{
    do 
    {
        //开始事务
        int iRet = mysql_query(mysqlConn, "start transaction");
        if (iRet != 0)
        {
            std::cout << "start transaction error:" << mysql_error(mysqlConn) << std::endl;
            break;
        }

        //设置事务为手动提交
        iRet = mysql_query(mysqlConn, "SET AUTOCOMMIT=0");
        if (iRet != 0)
        {
            std::cout << "set autocommit = 0 error:" << mysql_error(mysqlConn) << std::endl;
            break;
        }

        //乐观锁更新商品库存
        char szSql[MAX_SQL_LEN];
        snprintf(szSql, sizeof(szSql),
            "UPDATE miaosha.t_goods_stock SET Fstock_num = Fstock_num - 1 "
            "WHERE Fstock_id = '%s' AND Fstock_num - 1 >= 0", STOCK_ID);
        std::string strSql = std::string(szSql);
        iRet = mysql_query(mysqlConn, strSql.c_str());
        if (iRet != 0)
        {
            std::cout << "update miaosha.t_goods_stock error:" << iRet << std::endl;
            break;
        }

        //生成订单号
        time_t timep;
        time(&timep);
        char date[16];
        strftime(date, sizeof(date), "%Y%m%d", localtime(&timep));
        std::stringstream ss;
        ss << std::string(date) << pthread_self() << getNonceStr(7);
        std::string strListId = ss.str();

        //插入秒杀成功订单
        memset(szSql, 0, MAX_SQL_LEN);
        snprintf(szSql, sizeof(szSql),
            "INSERT INTO miaosha.t_miaosha_order(Flist_id,Fopenid,Fstock_id,Fstatus) "
            "VALUES ('%s', '%s', '%s', 1)",
            strListId.c_str(), strUserOpenid.c_str(), STOCK_ID);
        strSql = std::string(szSql);
        iRet = mysql_query(mysqlConn, strSql.c_str());
        if (iRet != 0)
        {
            std::cout << "update miaosha.t_goods_stock error:" << iRet << std::endl;
            break;
        }

        //手动提交事务
        iRet = mysql_query(mysqlConn, "COMMIT");
        if (iRet != 0)
        {
            std::cout << "commit error:" << mysql_error(mysqlConn) << std::endl;
            break;
        }

        std::cout << "commit succ, user miaosha succ!" << std::endl;
        m_response.set_result("OK");
        m_response.set_ret_msg("user miaosha succ!");
    } while (0);

    m_response.set_result("FAIL");
    m_response.set_ret_msg("user miaosha fail!");
    return;
}
