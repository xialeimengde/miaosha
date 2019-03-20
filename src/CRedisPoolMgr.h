#ifndef _CREDIS_POOL_MGR_H__
#define _CREDIS_POOL_MGR_H__

#include <iostream>
#include <string>
#include <queue>
#include <hiredis/hiredis.h>
#include "CThread.h"

//redis连接池管理类
class CRedisPoolMgr
{
public:
    //单例模式
    static CRedisPoolMgr *getInstance();

    //析构函数
    ~CRedisPoolMgr();

    //设置连接参数
    void setHost(const char *pzHost);
    void setPort(unsigned int iPort = 0);
    void setMaxConnNum(unsigned int iMaxConnNum = 1);

    //获取连接
    redisContext *getRedisConn();

    //关闭连接
    void closeRedisConn(redisContext *redisConn);

private:
    //构造函数
    CRedisPoolMgr();

    //建立redis连接
    redisContext *createRedisConn();

private:
    std::queue<redisContext *> m_redisPool; //redis连接池队列
    std::string m_strHost;                  //redis主机地址
    unsigned int m_iPort;                   //redis端口
    unsigned int m_iMaxConnNum;             //redis连接池最大连接数量
    unsigned int m_iCurConnNum;             //redis连接池当前连接数量

private:
    static CTMutex m_redisPoolMutex;      //连接池互斥锁
    static CRedisPoolMgr *m_redisPoolMgr; //连接池管理类
};

#endif