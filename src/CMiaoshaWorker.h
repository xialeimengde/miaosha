#ifndef _CMIAOSHA_WORKER_H__
#define _CMIAOSHA_WORKER_H__

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <time.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "comm_def.h"
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

//秒杀服务业务处理类
class CMiaoshaWorker
{
public:
    CMiaoshaWorker(MiaoshaService::AsyncService* service, ServerCompletionQueue* cq, CRedisPoolMgr* redisPool, CMysqlPoolMgr* mysqlPool);
    void excute();

private:
    void checkUserLoginStatus(const std::string& strUserOpenid, const std::string& strUserSession);
    bool checkUserMiaoshaSucc(const std::string& strUserOpenid, redisContext* redisConn, MYSQL* mysqlConn);
    void miaoshaGoods(const std::string& strUserOpenid, redisContext* redisConn, MYSQL* mysqlConn);
    bool miaoshaGoodsInRedis(const std::string& strUserOpenid, redisContext* redisConn);
    void miaoshaGoodsInDB(const std::string& strUserOpenid, MYSQL* mysqlConn);
private:
    typedef enum tapStatus
    {
        CREATE = 1,
        PROCESS = 2,
        FINISH = 3
    }EnStatus;

    MiaoshaService::AsyncService* m_service;
    ServerCompletionQueue* m_cq;
    ServerContext m_ctx;
    MiaoshaRequest m_request;
    MiaoshaResponse m_response;
    ServerAsyncResponseWriter<MiaoshaResponse> m_responder;

    EnStatus m_status;//当前处理状态
    CRedisPoolMgr* m_redisPool;//redis连接池
    CMysqlPoolMgr* m_mysqlPool;//mysql连接池
};

#endif

