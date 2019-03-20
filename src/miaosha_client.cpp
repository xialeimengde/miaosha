#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>

#include "miaosha.pb.h"
#include "miaosha.grpc.pb.h"
#include "comm_def.h"
#include "CMiaoshaClient.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using miaosha::MiaoshaRequest;
using miaosha::MiaoshaResponse;
using miaosha::MiaoshaService;

int main(int argc, char** argv)
{
    //多线程并发请求
    CMiaoshaClient miaoshaClient;
    miaoshaClient.setSvrAddress(SERVER_ADDR);
    miaoshaClient.setThreadCount(CLIENT_THREAD_NUM);

    std::cout << "startMiaoshaClient begin! svrAddr:" << SERVER_ADDR << " thread_num:" << CLIENT_THREAD_NUM << std::endl;
    miaoshaClient.startMiaoshaClient();

    return 0;
}
