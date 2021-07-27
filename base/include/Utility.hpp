
#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace MyMessenger
{
	const int SERVER_NOTHING 	= 0;
	const int SERVER_START		= 1;
	const int SERVER_STOP		= 2;
	const int SERVER_RELOAD		= 3;

	class CUtility
	{};

	class CLock
	{
	public:
		CLock()
		{
		#ifdef _WIN32
			InitializeCriticalSection(&m_critical_section);
		#else
			pthread_mutex_init(&m_lock, NULL);
		#endif
		}

		virtual ~CLock()
		{
		#ifdef _WIN32
			DeleteCriticalSection(&m_critical_section);
		#else
			pthread_mutex_destroy(&m_lock);
		#endif
		}

		void lock()
		{
		#ifdef _WIN32
			EnterCriticalSection(&m_critical_section);
		#else
			pthread_mutex_lock(&m_lock);
		#endif
		}

		void unlock()
		{
		#ifdef _WIN32
			LeaveCriticalSection(&m_critical_section);
		#else
			pthread_mutex_unlock(&m_lock);
		#endif
		}

		pthread_mutex_t& getMutex() { return m_lock; }
	#ifndef _WIN32
		virtual bool try_lock()
		{
			return pthread_mutex_trylock(&m_lock) == 0;
		}
	#endif
	private:
	#ifdef _WIN32
		CRITICAL_SECTION m_critical_section;
	#else
		pthread_mutex_t m_lock;
	#endif
	};

}

#endif