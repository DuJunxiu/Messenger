
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
        void* m_pArg;                   // 函数指针，参数
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
			// 初始化线程池
			threadpool_init(&m_stPool, MAX_THREAD_COUNT);

            m_iIdelCount = 0;
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
                if(0 != pthread_create(m_pstThread + i, NULL, routine, &m_stPool)) 
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
			// 唤醒所有线程
			if (m_iIdelCount < MAX_THREAD_COUNT)
			{
				broadcast();
			}

			for (int i = 0; i < MAX_THREAD_COUNT - m_iIdelCount; ++i)
			{
				wait();
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
			
			threadpool_destroy(&m_stPool);

            return 0;
        }

        // 执行任务
        int routine(void* arg)
        {
            while (true)
            {
                if (NULL == m_pstStart)
                {
                    // 没事情做就休息一下吧
                    // usleep(1000);
                    // continue;
                    break;
                }

                lock();

                --m_iIdelCount;

                TASK* pstRoutine = m_pstStart;
                m_pstStart = m_pstStart->m_pstNext;
                pstRoutine->m_pfRun(pstRoutine->m_pArg);
                delete pstRoutine;
                pstRoutine = NULL;
				
				wait();

                ++m_iIdelCount;

                unlock();
            }

            wait();

            return 0;
        }

        int addTask(void* (*run)(void *arg), void* arg)
        {
            if (NULL == run)
            {
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

            if (m_iIdelCount > 0)
            {
                signal();
            }

            unlock();

            return 0;
        }

        int lock()
        {
            return pthread_mutex_lock(&m_stMutex);
        }

        int unlock()
        {
            return pthread_mutex_unlock(&m_stMutex);
        }

        // 唤醒一个线程
        int signal()
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
        int m_iTaskCount;              // 当前队列任务数
        int m_iIdelCount;              // 空闲的线程数
        pthread_t* m_pstThread;        // 管理线程的数组
        pthread_mutex_t m_stMutex;     // 互斥锁
        pthread_cond_t m_stCond;       // 条件变量
        TASK* m_pstStart;              // 任务队列起始
        TASK* m_pstEnd;                // 任务队列结束
		thread_pool m_stPool;          // 线程池

    };
}

#endif
