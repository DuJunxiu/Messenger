
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>
#include <queue>
#include <stdio.h>

namespace MyMessenger
{
    const int MAX_THREAD_COUNT       =    5;
    const int MAX_WAIT_TASK_COUNT    =    1000;

    typedef struct tagTask
    {
        void* (*m_pfRun)(void* arg);    // 函数指针，指向一个任务
        void* m_pArg;                   // 函数参数
    } TASK;

    class CThreadPool
    {
    public:
        CThreadPool() { initialize(); }
        ~CThreadPool() { release(); }

    public:
        int initialize()
        {
            bStop = false;

            m_iIdelCount = MAX_THREAD_COUNT;
            m_pstThread = NULL;
            pthread_mutex_init(&m_stMutex, NULL);
            pthread_cond_init(&m_stCond, NULL);

            m_iTaskCount = 0;

            // 创建线程并分离
            m_pstThread = new pthread_t[MAX_THREAD_COUNT];
            for (int i = 0; i < MAX_THREAD_COUNT; ++i)
            {
                if(0 != pthread_create(m_pstThread + i, NULL, routine, (void*)this)) 
                {
                    delete[] m_pstThread;
                    return -1;
                }

                if(0 != pthread_detach(m_pstThread[i]))
                {
                    delete[] m_pstThread;
                    return -1;
                }

                printf("thread %d id %lu\n", i + 1, m_pstThread[i]);
            }

            return 0;
        }

        int release()
        {
            if (bStop)
            {
                return 0;
            }

            bStop = true;

            // 唤醒所有线程
            if (m_iIdelCount < MAX_THREAD_COUNT)
            {
                broadcast();
            }

            int i = 0;
            while (m_pstThread && i < MAX_THREAD_COUNT)
            {
                pthread_join(m_pstThread[i], NULL);
                ++i;
            }

            m_iIdelCount = 0;
            pthread_mutex_destroy(&m_stMutex);
            pthread_cond_destroy(&m_stCond);

            // 释放内存
            for (int i = 0; i < m_stTaskQueue.size(); ++i)
            {
                TASK* pstTemp = m_stTaskQueue.front();
                m_stTaskQueue.pop();
                delete pstTemp;
            }

            m_iTaskCount = 0;

            delete[] m_pstThread;
            m_pstThread = NULL;

            return 0;
        }

        // 执行任务
        static void* routine(void* arg)
        {
            //printf("routine thread %lu\n", pthread_self());

            CThreadPool* pstThreadPool = (CThreadPool*)arg;
            if (NULL == pstThreadPool)
            {
                return NULL;
            }

            while (!pstThreadPool->bStop)
            {
                //printf("before lock thread %lu\n", pthread_self());
                pstThreadPool->lock();
                //printf("after lock thread %lu\n", pthread_self());

                while (pstThreadPool->m_stTaskQueue.empty() && !pstThreadPool->bStop)
                {
                    // printf("thread %lu is waiting\n", pthread_self());
                    pstThreadPool->wait();
                }

                if (pstThreadPool->bStop)
                {
                    // printf("thread %lu is stop\n", pthread_self());
                    pstThreadPool->unlock();
                    break;
                }
                else if (pstThreadPool->m_stTaskQueue.empty())
                {
                    // printf("thread %lu is empty\n", pthread_self());
                    pstThreadPool->unlock();
                    continue;
                }

                // printf("thread %lu is working\n", pthread_self());

                --pstThreadPool->m_iIdelCount;

                TASK* pstRoutine = pstThreadPool->m_stTaskQueue.front();
                pstThreadPool->m_stTaskQueue.pop();

                ++pstThreadPool->m_iIdelCount;

                --pstThreadPool->m_iTaskCount;

                pstThreadPool->unlock();

                pstRoutine->m_pfRun(pstRoutine->m_pArg);
                delete pstRoutine;
                pstRoutine = NULL;
            }

            return NULL;
        }

        int addTask(void* (*run)(void *arg), void* arg)
        {
            if (NULL == run)
            {
                return -1;
            }

            lock();

            if (m_iTaskCount >= MAX_WAIT_TASK_COUNT)
            {
                return -1;
            }

            TASK* pstTask = new TASK;
            pstTask->m_pfRun = run;
            pstTask->m_pArg = arg;

            m_stTaskQueue.push(pstTask);

            ++m_iTaskCount;

            unlock();

            if (m_iIdelCount > 0)
            {
                // printf("add task sucess, try to wakeup\n");
                wakeup();
            }

            return 0;
        }

        bool isEmpty()
        {
            lock();
            bool bEmpty = m_stTaskQueue.empty();
            unlock();
            return bEmpty;
        }

    private:
        int lock()
        {
            return pthread_mutex_lock(&m_stMutex);
        }

        int unlock()
        {
            return pthread_mutex_unlock(&m_stMutex);
        }

        // 唤醒
        int wakeup()
        {
            return pthread_cond_signal(&m_stCond);
        }

        // 唤醒所有线程
        int broadcast()
        {
            return pthread_cond_broadcast(&m_stCond);
        }

        // 等待
        int wait()
        {
            return pthread_cond_wait(&m_stCond, &m_stMutex);
        }

    private:
        bool bStop;
        int m_iTaskCount;              // 当前队列任务数
        int m_iIdelCount;              // 空闲的线程数
        pthread_t* m_pstThread;        // 管理线程的数组
        pthread_mutex_t m_stMutex;     // 互斥锁
        pthread_cond_t m_stCond;       // 条件变量
        std::queue<TASK*> m_stTaskQueue;        // 任务队列

    };
}

#endif
