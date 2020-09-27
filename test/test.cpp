

#include "ThreadPool.h"
#include "LogDeal.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace MyMessenger;


void* mytask(void *arg)
{
    printf("thread %d is working on task %d\n", (int)pthread_self(), *(int*)arg);
    sleep(1);
    free(arg);
    return NULL;
}

//测试代码
int main(void)
{
    CThreadPool pool;
    //创建十个任务
    for(int i = 0; i < 10; ++i)
    {
        int *arg = (int*)malloc(sizeof(int));
        *arg = i;
        pool.addTask(mytask, (void*)arg);
        
    }

    return 0;
}
