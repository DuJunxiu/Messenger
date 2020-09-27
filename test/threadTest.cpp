
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

<<<<<<< HEAD
    //sleep(1);

	for (int i = 0; i < 10; ++i)
	{
		pstThreadPool.addTask(PrintMyself, (void*)&g_asiArray[i]);
	}

=======
    sleep(1);

	for (int i = 0; i < 10; ++i)
	{
        // sleep(1);
		pstThreadPool.addTask(PrintMyself, (void*)&g_asiArray[i]);

       // sleep(1);
	}

    //sleep(1);

>>>>>>> 589b9e4f97f533f329b387745135ed7a3d518bfb
    while (true)
    {
        if (!pstThreadPool.isEmpty())
        {
            //printf("process excuting ... \n");
            //sleep(1);
        }
        else
        {
<<<<<<< HEAD
            printf("try release\n");
            pstThreadPool.release();
            printf("release sucess\n");
			break;
=======
            printf("try delete sucess\n");
            pstThreadPool.release();
            printf("delete sucess\n");
>>>>>>> 589b9e4f97f533f329b387745135ed7a3d518bfb
        }
    }

	return 0;
}

