#include "CMysqlPoolMgr.h"

CMysqlPoolMgr *CMysqlPoolMgr::m_mysqlPoolMgr = NULL;
CTMutex CMysqlPoolMgr::m_mysqlPoolMutex;

CMysqlPoolMgr *CMysqlPoolMgr::getInstance()
{
    if (NULL == m_mysqlPoolMgr)
    {
        m_mysqlPoolMgr = new CMysqlPoolMgr();
    }

    return m_mysqlPoolMgr;
}

CMysqlPoolMgr::~CMysqlPoolMgr()
{
    CMysqlPoolMgr::m_mysqlPoolMutex.lock();
    while (0 != m_mysqlPool.size())
    {
        MYSQL *mysqlConn = m_mysqlPool.front();
        mysql_close(mysqlConn);
        m_mysqlPool.pop();
        --m_iCurConnNum;
    }
    CMysqlPoolMgr::m_mysqlPoolMutex.unlock();
}

void CMysqlPoolMgr::setHost(const char *pzHost)
{
    m_strHost = pzHost;
}

void CMysqlPoolMgr::setUsr(const char *pzUser)
{
    m_strUsr = pzUser;
}

void CMysqlPoolMgr::setPwd(const char *pzPwd)
{
    m_strPwd = pzPwd;
}

void CMysqlPoolMgr::setPort(unsigned int iPort/* = 0*/)
{
    m_iPort = iPort;
}

void CMysqlPoolMgr::setMaxConnNum(unsigned int iMaxConnNum/* = 1*/)
{
    m_iMaxConnNum = iMaxConnNum;
}

MYSQL *CMysqlPoolMgr::getMysqlConn()
{
    CMysqlPoolMgr::m_mysqlPoolMutex.lock();
    MYSQL *mysqlConn = NULL;

    if (m_mysqlPool.empty())
    {
        if (m_iCurConnNum < m_iMaxConnNum)
        {
            mysqlConn = createMysqlConn();
            if (mysqlConn != NULL)
            {
                ++m_iCurConnNum;
                std::cout << "create mysql connect succ!" << std::endl;
            }
            else
            {
                std::cout << "create mysql connect fail!" << std::endl;
            }
        }
        else
        {
            std::cout << "m_iCurConnNum:" << m_iCurConnNum << std::endl;
            std::cout << "m_iMaxConnNum:" << m_iMaxConnNum << std::endl;
            std::cout << "reach max mysql connect num!" << std::endl;
        }
    }
    else
    {
        mysqlConn = m_mysqlPool.front();
        m_mysqlPool.pop();
        std::cout << "get mysql connect succ!" << std::endl;
    }

    CMysqlPoolMgr::m_mysqlPoolMutex.unlock();
    return mysqlConn;
}

void CMysqlPoolMgr::closeMysqlConn(MYSQL *mysqlConn)
{
    if (NULL != mysqlConn)
    {
        CMysqlPoolMgr::m_mysqlPoolMutex.lock();
        m_mysqlPool.push(mysqlConn);
        CMysqlPoolMgr::m_mysqlPoolMutex.unlock();
    }
}

CMysqlPoolMgr::CMysqlPoolMgr()
{
    m_iPort = 0;
    m_iMaxConnNum = 0;
    m_iCurConnNum = 0;
}

MYSQL *CMysqlPoolMgr::createMysqlConn()
{
    MYSQL *mysqlConn = NULL;
    mysqlConn = mysql_init(mysqlConn);
    if (NULL != mysqlConn)
    {
        if (mysql_real_connect(mysqlConn, m_strHost.c_str(), m_strUsr.c_str(), m_strPwd.c_str(), NULL, m_iPort, NULL, 0))
        {
            std::cout << "mysql_real_connect succ!" << std::endl;
        }
        else
        {
            std::cout << "mysql_real_connect fail! error:" << mysql_error(mysqlConn) << std::endl;
            mysqlConn = NULL;
        }
    }
    else
    {
        std::cout << "init mysql object fail!" << std::endl;
    }

    return mysqlConn;
}
