
#include "EventLoop.hpp"
#include "TimeUtility.h"

int CEventLoop::m_iCommand = SERVER_NOTHING;

int CEventLoop::initialize()
{
	return 0;
}

int CEventLoop::release()
{
	return 0;
}

int CEventLoop::routine()
{
	while (true)
	{
		CTimeUtility::m_uiTime = time(NULL);
		if (SERVER_STOP == m_iCommand)
		{
			break;
		}
	}

	return 0;
}

void CEventLoop::OnTick()
{}
