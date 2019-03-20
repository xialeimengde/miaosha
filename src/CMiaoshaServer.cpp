#include "CMiaoshaServer.h"
#include "CMiaoshaWorker.h"

CMiaoshaServer::CMiaoshaServer()
{
    m_redisPool = NULL;
    m_mysqlPool = NULL;
    m_iThreadCount = 0;
}

CMiaoshaServer::~CMiaoshaServer()
{
    m_server->Shutdown();
    m_cq->Shutdown();
}

void CMiaoshaServer::setAddress(const char* pzAddress)
{
    m_strAddress = pzAddress;
}

void CMiaoshaServer::setRedisPoolMgr(CRedisPoolMgr* redisPool)
{
    m_redisPool = redisPool;
}

void CMiaoshaServer::setMysqlPoolMgr(CMysqlPoolMgr* mysqlPool)
{
    m_mysqlPool = mysqlPool;
}

void CMiaoshaServer::setThreadCount(unsigned int iThreadCount/* = 1*/)
{
    m_iThreadCount = iThreadCount;
}

void CMiaoshaServer::startMiaoshaServer()
{
    //启动服务
    ServerBuilder builder;
    builder.AddListeningPort(m_strAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&m_service);
    m_cq = builder.AddCompletionQueue();
    m_server = builder.BuildAndStart();
    std::cout << "Server listening on " << m_strAddress << std::endl;

    //初始化线程池
    for (unsigned int i = 0; i < m_iThreadCount; ++i)
    {
        CThread* thread = new CThread(this);
        if (false == thread->start())
        {
            std::cout << "start thread failed!" << std::endl;
            exit(1);
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

void CMiaoshaServer::run()
{
    new CMiaoshaWorker(&m_service, m_cq.get(), m_redisPool, m_mysqlPool);

    void* tag;
    bool ok;
    while (true)
    {
        std::cout << "tid:" << pthread_self() << " CMiaoshaServer::run" << std::endl;
        GPR_ASSERT(m_cq->Next(&tag, &ok));
        std::cout << "tid:" << pthread_self() << " CMiaoshaServer Next ok:" << ok << std::endl;
        GPR_ASSERT(ok);
        static_cast<CMiaoshaWorker*>(tag)->excute();
    }
}
