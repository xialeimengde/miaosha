#include "CMiaoshaClient.h"

CTMutex CMiaoshaClient::m_mutex;
int CMiaoshaClient::m_iMiaoshaSuccNum = 0;

const std::string getNonceStr(int iLen/* = 32*/)
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int maxPos = chars.length();
    std::string noceStr = "";

    for (int i = 0; i < iLen; i++)
    {
        noceStr += chars.at(rand() % maxPos);
    }

    return noceStr;
}

CMiaoshaClient::CMiaoshaClient()
{
    m_iThreadCount = 0;

}

CMiaoshaClient::~CMiaoshaClient()
{

}

void CMiaoshaClient::setSvrAddress(const char* pzSvrAddress)
{
    m_strSvrAddress = pzSvrAddress;
}

void CMiaoshaClient::setThreadCount(unsigned int iThreadCount/* = 1*/)
{
    m_iThreadCount = iThreadCount;
}

void CMiaoshaClient::startMiaoshaClient()
{
    //初始化线程池
    for (unsigned int i = 0; i < m_iThreadCount; ++i)
    {
        CThread* thread = new CThread(this);
        if (false == thread->start())
        {
            std::cout << "start thread failed!" << std::endl;
        }

        m_threadPool.push_back(thread);
    }

    //等待线程执行结束
    for (unsigned int i = 0; i < m_iThreadCount; ++i)
    {
        CThread* thread = m_threadPool[i];
        thread->join();
    }
}

void CMiaoshaClient::run()
{
    std::cout << "tid:" << pthread_self() << " CMiaoshaClient::run" << std::endl;
    std::shared_ptr<Channel> channel = grpc::CreateChannel(m_strSvrAddress.c_str(), grpc::InsecureChannelCredentials());
    std::unique_ptr<MiaoshaService::Stub> stub(MiaoshaService::NewStub(channel));

    MiaoshaRequest request;
    request.set_user_openid(getNonceStr(16));
    request.set_user_session(getNonceStr(32));

    std::cout << "tid:" << pthread_self()
        << " openid:" << request.user_openid()
        << " session:" << request.user_session() << std::endl;

    MiaoshaResponse response;
    ClientContext context;
    CompletionQueue cq;
    Status status;
    std::unique_ptr<ClientAsyncResponseReader<MiaoshaResponse> > rpc(
        stub->PrepareAsyncmiaosha(&context, request, &cq));

    std::cout << "tid:" << pthread_self() << " rpc start call" << std::endl;
    rpc->StartCall();
    rpc->Finish(&response, &status, (void*)1);
    std::cout << "tid:" << pthread_self() << " rpc finish call" 
        << " status:" << status.ok() << std::endl;

    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    std::cout << "tid:" << pthread_self() << " next got_tag:" << got_tag << std::endl;
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);
    if (status.ok())
    {
        //调用接口成功
        std::string strResult = response.result();
        std::string strRetMsg = response.ret_msg();
        std::cout << "tid:" << pthread_self()
            << " strResult:" << strResult
            << " strRetMsg:" << strRetMsg << std::endl;
        if (std::string("OK") == strResult)
        {
            m_mutex.lock();
            ++m_iMiaoshaSuccNum;
            m_mutex.unlock();
            std::cout << "miaosha succ! succ_num:" << m_iMiaoshaSuccNum << std::endl;
        }
        else
        {
            std::cout << "miaosha failed! errmsg:" << strRetMsg << std::endl;
        }
    }
    else
    {
        //调用接口失败
        std::cout << "RPC failed!" << std::endl;
    }
}

