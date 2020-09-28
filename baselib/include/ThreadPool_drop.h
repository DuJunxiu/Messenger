
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>

#include "LogDeal.hpp"

namespace MyMessenger
{
    const int MAX_THREAD_COUNT       =    5;
    const int MAX_WAIT_TASK_COUNT    =    1000;

    typedef struct tagTask
    {
        void* (*m_pfRun)(void*);        // 函数指针，指向一个任务
        void* m_pArg;                   // 函数参数
        struct tagTask* m_pstNext;      // 指向下一个任务结构
    } TASK;

    class CThreadPool
    {
    public:
        CThreadPool() { initialize(); }
        ~CThreadPool() { release(); }

    public:
        int initialize()
        {
            m_iIdelCount = MAX_THREAD_COUNT;
            m_pstThread = NULL;
            pthread_mutex_init(&m_stMutex, NULL);
            pthread_cond_init(&m_stCond, NULL);

            m_pstStart = NULL;
            m_pstEnd = NULL;
            m_iTaskCount = 0;

            // 创建线程并分离
            m_pstThread = new pthread_t[MAX_THREAD_COUNT];
            for (int i = 0; i < MAX_THREAD_COUNT; ++i)
            {
                if(0 != pthread_create(m_pstThread + i, NULL, routine, (void*)this)) 
                {
                    delete[] m_pstThread;
                    
                    TRACELOG("Error create thread failed !\n");
                    return -1;
                }

                if(0 != pthread_detach(m_pstThread[i]))
                {
                    delete[] m_pstThread;
                    
                    TRACELOG("Error detach thread failed !\n");
                    return -1;
                }
            }

            return 0;
        }

        int release()
        {
            if (bStop)
            {
				// 避免多次 delete
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
            if (m_pstStart)
            {
                TASK* pstTemp = m_pstStart->m_pstNext;
                while (m_pstStart)
                {
                    delete m_pstStart;
                    m_pstStart = pstTemp;
                }
            }

            m_pstStart = NULL;
            m_pstEnd = NULL;
            m_iTaskCount = 0;

            delete[] m_pstThread;
            m_pstThread = NULL;

            return 0;
        }

        // 执行任务
        static void* routine(void* arg)
        {
            CThreadPool* pstThreadPool = (CThreadPool*)arg;
            if (NULL == pstThreadPool)
            {
                return NULL;
            }

            while (!pstThreadPool->bStop)
            {
                pstThreadPool->lock();

                while (pstThreadPool-isEmpty() && !pstThreadPool->bStop)
                {
                    pstThreadPool->wait();
                }

				// 收到 stop 命令了
                if (pstThreadPool->bStop)
                {
                    pstThreadPool->unlock();
                    break;
                }
				// 任务队列为空
                else if (pstThreadPool->isEmpty())
                {
                    pstThreadPool->unlock();
                    continue;
                }

                --pstThreadPool->m_iIdelCount;

                TASK* pstRoutine = pstThreadPool->m_pstStart;
                pstThreadPool->m_pstStart = pstThreadPool->m_pstStart->m_pstNext;

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

            if (m_iTaskCount >= MAX_WAIT_TASK_COUNT)
            {
                TRACELOG("MAX Wait Tasks Count !\n");
                return -1;
            }

            lock();

            TASK* pstTask = new TASK;
            pstTask->m_pfRun = run;
            pstTask->m_pArg = arg;
            pstTask->m_pstNext = NULL;

            if (NULL == m_pstStart)
            {
                m_pstStart = pstTask;
                m_pstEnd = pstTask;
            }
            else
            {
                m_pstEnd->m_pstNext = pstTask;
            }

            ++m_iTaskCount;

            unlock();

            if (m_iIdelCount > 0)
            {
                wakeup();
            }

            return 0;
        }

        bool isEmpty()
        {
            lock();
            bool bEmpty = (NULL == m_pstStart);
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

        // 唤醒一个线程
        int wakeup()
        {
            return pthread_cond_signal(&m_stCond);
        }
        
        // 唤醒所有线程
        int broadcast()
        {
            return pthread_condition_broadcast(&m_stCond);
        }

        // 等待
        int wait()
        {
            return pthread_cond_wait(&m_stCond);
        }

    private:
        bool bStop;
        int m_iTaskCount;              // 当前队列任务数
        int m_iIdelCount;              // 空闲的线程数
        pthread_t* m_pstThread;        // 管理线程的数组
        pthread_mutex_t m_stMutex;     // 互斥锁
        pthread_cond_t m_stCond;       // 条件变量
        TASK* m_pstStart;              // 任务队列起始
        TASK* m_pstEnd;                // 任务队列结束

    };
}

#endif
