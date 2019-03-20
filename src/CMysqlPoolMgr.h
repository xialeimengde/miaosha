#ifndef _CMYSQL_POOL_MGR_H__
#define _CMYSQL_POOL_MGR_H__

#include <iostream>
#include <string>
#include <queue>
#include <mysql/mysql.h>
#include "CThread.h"

//Mysql连接池管理类
class CMysqlPoolMgr
{
public:
    //单例模式
    static CMysqlPoolMgr *getInstance();

    //析构函数
    ~CMysqlPoolMgr();

    //设置连接参数
    void setHost(const char *pzHost);
    void setUsr(const char *pzUser);
    void setPwd(const char *pzPwd);
    void setPort(unsigned int iPort = 0);
    void setMaxConnNum(unsigned int iMaxConnNum = 1);

    //获取连接
    MYSQL *getMysqlConn();

    //关闭连接
    void closeMysqlConn(MYSQL *mysqlConn);

private:
    //构造函数
    CMysqlPoolMgr();

    //建立mysql连接
    MYSQL *createMysqlConn();

private:
    std::queue<MYSQL *> m_mysqlPool; //mysql连接池队列
    std::string m_strHost;           //mysql主机地址
    std::string m_strUsr;            //mysql用户名
    std::string m_strPwd;            //mysql密码
    unsigned int m_iPort;            //mysql端口
    unsigned int m_iMaxConnNum;      //mysql连接池最大连接数量
    unsigned int m_iCurConnNum;      //mysql连接池当前连接数量

private:
    static CTMutex m_mysqlPoolMutex;      //连接池互斥锁
    static CMysqlPoolMgr *m_mysqlPoolMgr; //连接池管理类
};

#endif
