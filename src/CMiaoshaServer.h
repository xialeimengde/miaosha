#ifndef _CMIAOSHA_SERVER_H__
#define _CMIAOSHA_SERVER_H__

#include <iostream>
#include <string>
#include <queue>
#include <mysql/mysql.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "CThread.h"
#include "CRedisPoolMgr.h"
#include "CMysqlPoolMgr.h"
#include "miaosha.pb.h"
#include "miaosha.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using miaosha::MiaoshaRequest;
using miaosha::MiaoshaResponse;
using miaosha::MiaoshaService;

//秒杀服务管理类
class CMiaoshaServer : public CTRunnable
{
public:
    CMiaoshaServer();
    ~CMiaoshaServer();
    void setAddress(const char* pzAddress);
    void setRedisPoolMgr(CRedisPoolMgr* redisPool);
    void setMysqlPoolMgr(CMysqlPoolMgr* mysqlPool);
    void setThreadCount(unsigned int iThreadCount = 1);
    void startMiaoshaServer();
    virtual void run();
private:
    std::string m_strAddress;//服务地址
    CRedisPoolMgr* m_redisPool;//redis连接池
    CMysqlPoolMgr* m_mysqlPool;//mysql连接池
    unsigned int m_iThreadCount;//线程池数量
    std::vector<CThread*> m_threadPool;//线程池
    std::unique_ptr<ServerCompletionQueue> m_cq;
    MiaoshaService::AsyncService m_service;
    std::unique_ptr<Server> m_server;
};

#endif
