
#ifndef __LAUNCHER_CPP__
#define __LAUNCHER_CPP__

#include "EventLoop.hpp"
#include "ThreadPool.hpp"

using namespace MyMessenger;

int main()
{
	CEventLoop* pstLoop = new CEventLoop;
	if (nullptr == pstLoop)
	{
		return -1;
	}
	
	pstLoop->initialize();

	pstLoop->routine();

	pstLoop->release();

	return 0;
}

#ednif
