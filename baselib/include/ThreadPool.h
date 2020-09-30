
/*****************************************************
**
** Filename:         ThreadPool.h
** Author:           
** CreateTime:       2020/9/30
** description:      使用C++11的特性的简单的线程池类
**
******************************************************/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>

namespace MyMessenger
{
    const int MAX_THREAD_COUNT       =    5;
    const int MAX_WAIT_TASK_COUNT    =    1000;

    class CThreadPool
    {
    };
}

#endif
