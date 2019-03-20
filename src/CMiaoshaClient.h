#ifndef _CMIAOSHA_CLIENT_H__
#define _CMIAOSHA_CLIENT_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "miaosha.pb.h"
#include "miaosha.grpc.pb.h"
#include "CThread.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using miaosha::MiaoshaRequest;
using miaosha::MiaoshaResponse;
using miaosha::MiaoshaService;

//秒杀客户端管理类
class CMiaoshaClient : public CTRunnable
{
public:
    CMiaoshaClient();
    ~CMiaoshaClient();
    void setSvrAddress(const char* pzSvrAddress);
    void setThreadCount(unsigned int iThreadCount = 1);
    void startMiaoshaClient();
    virtual void run();
private:
    std::string m_strSvrAddress;//服务地址
    unsigned int m_iThreadCount;//线程池数量
    std::vector<CThread*> m_threadPool;//线程池

private:
    static CTMutex m_mutex;//互斥锁
    static int m_iMiaoshaSuccNum;//秒杀成功个数
};

#endif
