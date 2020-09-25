
#include <stdio.h>

#include "ThreadPool.h"
#include "LogDeal.hpp"

using namespace MyMessenger;

void PrintMyself()
{
	printf();

	return;
}

int main()
{
	CThreadPool* pstThreadPool = new CThreadPool;
	if (NULL == pstThreadPool)
	{
		TRACELOG("new ThreadPool failed\n");
		return -1;
	}

	for (int i = 0; i < 10; ++i)
	{
		pstThreadPool->addTask(PrintMyself);
	}

	delete pstThreadPool;

	return 0;
}

