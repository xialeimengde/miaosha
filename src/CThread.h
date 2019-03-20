#ifndef _CTHREAD_H__
#define _CTHREAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class CTRunnable
{
  public:
    CTRunnable();
    virtual ~CTRunnable();
    virtual void run() = 0;
};

class CThread
{
  public:
    CThread(CTRunnable *pRunnable);
    ~CThread();
    bool start();
    void join();
    void stop();

  private:
    CTRunnable *m_pRunnable;
    pthread_t m_pthread;
};

class CTMutex
{
  public:
    CTMutex();
    ~CTMutex();
    void lock();
    void unlock();

  private:
    pthread_mutex_t m_mutex;
};

#endif
