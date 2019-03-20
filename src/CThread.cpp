#include "CThread.h"

void *CThreadFun(void *lParam)
{
    CTRunnable *pRunnable = (CTRunnable *)lParam;
    pRunnable->run();
    return 0;
}

CTRunnable::CTRunnable()
{
}

CTRunnable::~CTRunnable()
{
}

CThread::CThread(CTRunnable *pRunnable) : m_pRunnable(pRunnable), m_pthread(0)
{
}

CThread::~CThread()
{
}

bool CThread::start()
{
    if (0 == m_pRunnable)
    {
        return false;
    }

    if (pthread_create(&m_pthread, NULL, CThreadFun, (void *)m_pRunnable) != 0)
    {
        perror("pthread_create");
        return false;
    }

    return true;
}

void CThread::join()
{
    pthread_join(m_pthread, NULL);
}

void CThread::stop()
{
    pthread_cancel(m_pthread);
}

CTMutex::CTMutex()
{
    pthread_mutexattr_t mutex_attribute;
    pthread_mutexattr_init(&mutex_attribute);
    pthread_mutexattr_settype(&mutex_attribute, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_mutex, &mutex_attribute);
}

CTMutex::~CTMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void CTMutex::lock()
{
    pthread_mutex_lock(&m_mutex);
}

void CTMutex::unlock()
{
    pthread_mutex_unlock(&m_mutex);
}

