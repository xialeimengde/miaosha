#include "CRedisPoolMgr.h"

CRedisPoolMgr *CRedisPoolMgr::m_redisPoolMgr = NULL;
CTMutex CRedisPoolMgr::m_redisPoolMutex;

CRedisPoolMgr *CRedisPoolMgr::getInstance()
{
    if (NULL == m_redisPoolMgr)
    {
        m_redisPoolMgr = new CRedisPoolMgr();
    }

    return m_redisPoolMgr;
}

CRedisPoolMgr::~CRedisPoolMgr()
{
    m_redisPoolMutex.lock();
    while (0 != m_redisPool.size())
    {
        redisContext *redisConn = m_redisPool.front();
        redisFree(redisConn);
        m_redisPool.pop();
        --m_iCurConnNum;
    }
    m_redisPoolMutex.unlock();
}

void CRedisPoolMgr::setHost(const char *pzHost)
{
    m_strHost = pzHost;
}

void CRedisPoolMgr::setPort(unsigned int iPort/* = 0*/)
{
    m_iPort = iPort;
}

void CRedisPoolMgr::setMaxConnNum(unsigned int iMaxConnNum /*= 1*/)
{
    m_iMaxConnNum = iMaxConnNum;
}

redisContext *CRedisPoolMgr::getRedisConn()
{
    m_redisPoolMutex.lock();
    redisContext *redisConn = NULL;

    if (m_redisPool.empty())
    {
        if (m_iCurConnNum < m_iMaxConnNum)
        {
            redisConn = createRedisConn();
            if (NULL != redisConn)
            {
                ++m_iCurConnNum;
                std::cout << "create redis connect succ!" << std::endl;
            }
            else
            {
                std::cout << "create redis connect fail!" << std::endl;
            }
        }
        else
        {
            std::cout << "reach max redis connect num!" << std::endl;
        }
    }
    else
    {
        redisConn = m_redisPool.front();
        m_redisPool.pop();
        std::cout << "get redis connect succ!" << std::endl;
    }

    m_redisPoolMutex.unlock();
    return redisConn;
}

void CRedisPoolMgr::closeRedisConn(redisContext *redisConn)
{
    if (NULL != redisConn)
    {
        m_redisPoolMutex.lock();
        m_redisPool.push(redisConn);
        m_redisPoolMutex.unlock();
    }
}

CRedisPoolMgr::CRedisPoolMgr()
{
    m_iPort = 0;
    m_iMaxConnNum = 0;
    m_iCurConnNum = 0;
}

redisContext *CRedisPoolMgr::createRedisConn()
{
    redisContext *redisConn = NULL;
    redisConn = redisConnect(m_strHost.c_str(), m_iPort);
    if (NULL == redisConn || redisConn->err)
    {
        if (NULL != redisConn)
        {
            std::cout << "redis connect fail! error:" << redisConn->errstr << std::endl;
            redisFree(redisConn);
            redisConn = NULL;
        }
        else
        {
            std::cout << "redis connect fail! unknow error" << std::endl;
        }
    }
    else
    {
        std::cout << "redisConnect succ!" << std::endl;
    }

    return redisConn;
}
