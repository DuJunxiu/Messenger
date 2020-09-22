
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>

namespace MyMessenger
{
	const int MAX_THREAD_COUNT = 5;
	
	tempalte<class T>
	class CThreadPool
	{
	public:
		CThreadPool() {}
		~CThreadPool() {}

	public:
		int initialize()
		{
			m_iIdel = MAX_THREAD_COUNT;
			pthread_mutex_init(&m_stMutex, NULL);
			pthread_cond_init(&m_stCond, NULL);
			
			return 0;
		}
		
		int release()
		{
			m_iIdel = 0;
			pthread_mutex_destroy(&m_stMutex);
			pthread_cond_destroy(&m_stCond);
			
			return 0;
		}
		
		int routine()
		{
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
		
		int signal()
		{
			return pthread_cond_signal(&m_stCond);
		}
		
		int wait()
		{
			return pthread_cond_wait(&m_stCond);
		}

	private:
		int m_iIdel;				// 空闲的线程数
		pthread_mutex_t m_stMutex;	// 互斥锁
		pthread_cond_t	m_stCond;	// 条件变量
	};
}

#endif