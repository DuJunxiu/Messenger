
#include <stdio.h>

#include "ThreadPool.h"
#include "LogDeal.hpp"

using namespace MyMessenger;

void* PrintMyself(void* arg)
{
	printf("thread: %d is working %d\n", pthread_self(), *(int*)arg);

	return NULL;
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
		pstThreadPool->addTask(PrintMyself, &i);
	}

	delete pstThreadPool;

	return 0;
}

