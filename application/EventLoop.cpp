
#include "EventLoop.hpp"

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
		if (SERVER_STOP == m_iCommand)
		{
			break;
		}
	}

	return 0;
}

void CEventLoop::OnTick()
{}
