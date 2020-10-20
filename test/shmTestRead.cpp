
#include <unistd.h>
#include "SharedMemory.hpp"

int main()
{
    CSharedMemory* pstShm = new CSharedMemory;
    if (NULL == pstShm)
    {
        printf("new CSharedMemory failed\n");
        return -1;
    }

    pstShm->initialize();

    int iRet = pstShm->allocateShmSpace(4096, IPC_CREAT|0666);
    if (iRet < 0)
    {
        printf("allocateShmSpace failed\n");
        return -1;
    }

    const char* pcInitAddress = pstShm->getInitAddress();
    const char* pcDataAddress = pcInitAddress + sizeof(int);

    int i = 0;
    while (i < 5)
    {
        if (i < *(int*)pcInitAddress)
        {
            printf("read from shm : %d ---> %d: %s\n", pstShm->getShmID(), i, *(ShmTest*)(pcDataAddress + sizeof(ShmTest) * i));
            ++i;
        }

		sleep(1);
    }

    pstShm->destory();

    return 0;
}
