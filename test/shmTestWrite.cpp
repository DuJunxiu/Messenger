
#include <string.h>

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

    int* piCount = (int*)pstShm->getFreeAdress();
    if (NULL == piCount)
    {
        printf("piCount is NULL\n");
        return -1;
    }

    *piCount = 0;
    pstShm->setFreeAdress(sizeof(*piCount));

    while (*piCount <= 5)
    {
        const char* pFreeAdress = pstShm->getFreeAdress();
        if (NULL == pFreeAdress)
        {
            printf("pFreeAdress is NULL\n");
            break;
        }

        ShmTest* pstTest = (ShmTest*)pFreeAdress;
        if (NULL == pstTest)
        {
            break;
        }

        pstTest->m_acBuffer = "Hello World ";
        pstShm->setFreeAdress(sizeof(ShmTest));
        ++(*piCount);

        sleep(1000);
    }

    pstShm->destory();

    return 0;
}
