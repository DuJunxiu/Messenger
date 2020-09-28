
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "ThreadPool.h"

using namespace MyMessenger;

void* PrintMyself(void* arg)
{
	printf("thread %lu is working for %d\n", pthread_self(), *(int*)arg);

    	sleep(1);

	return NULL;
}

static int g_asiArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{
	CThreadPool pstThreadPool;

	for (int i = 0; i < 10; ++i)
	{
		pstThreadPool.addTask(PrintMyself, (void*)&g_asiArray[i]);
	}

    while (true)
    {
        if (!pstThreadPool.isEmpty())
        {
            //printf("process excuting ... \n");
            //sleep(1);
        }
        else
        {
            printf("try release\n");
            pstThreadPool.release();
            printf("release sucess\n");
			break;
        }
    }

    return 0;
}

