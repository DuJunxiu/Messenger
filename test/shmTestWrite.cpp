
#include <string.h>
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

    int iRet = pstShm->allocateShmSpace();
    if (iRet < 0)
    {
        printf("allocateShmSpace failed\n");
        return -1;
    }

    int* piCount = (int*)pstShm->getFreeAddress();
    if (NULL == piCount)
    {
        printf("piCount is NULL\n");
        return -1;
    }

    *piCount = 0;
    pstShm->setFreeAddress(sizeof(*piCount));

    sleep(5);

    while (*piCount <= 5)
    {
        const char* pFreeAddress = pstShm->getFreeAddress();
        if (NULL == pFreeAddress)
        {
            printf("pFreeAddress is NULL\n");
            break;
        }

        ShmTest* pstTest = (ShmTest*)pFreeAddress;
        if (NULL == pstTest)
        {
            break;
        }

        strncpy(pstTest->m_acBuffer, "Hello World", 32);

        printf("write in  shm : %d ---> %d: %s\n", pstShm->getShmID(), *piCount, pstTest->m_acBuffer);

        pstShm->setFreeAddress(sizeof(ShmTest));
        ++(*piCount);

        sleep(1);
    }

    pstShm->destory();

    return 0;
}
