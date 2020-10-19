
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

    while (true)
    {
		int iRet = pstShm->allocateShmSpace(4096, IPC_CREAT|0666);
		if (iRet < 0)
		{
			printf("allocateShmSpace failed\n");
			return -1;
		}

    }

    pstShm->destory();

    return 0;
}
