
#include <sys/shm.h>
#include <sys/types.h>

#include "LogDeal.h"
#include "SharedMemory.hpp"

using namespace MyMessenger;

CSharedMemory::CSharedMemory()
{
    initialize();
}

CSharedMemory::~CSharedMemory()
{
    destory();
}

// 初始化工作
int CSharedMemory::initialize()
{
    m_uiShmKey = 0;
    m_iShmID = 0;
    m_iFreeOffset = 0;
    m_pShmAdress = NULL;

    return 0;
}

// 销毁共享内存
int CSharedMemory::destory()
{
    if (m_iShmID <= 0)
    {
        return 0;
    }

    return shmctl(m_iShmID, IPC_RMID, NULL);
}

key_t CSharedMemory::getShmKey()
{
    return m_uiShmKey;
}

int CSharedMemory::getShmID()
{
    return m_iShmID;
}

// 申请分配共享内存空间
int CSharedMemory::allocateShmSpace(int iSize, int iFlag)
{
    key_t m_uiShmKey = ftok(SHM_KEY_FILE, 110);
    if (m_uiShmKey < 0)
    {
        TRACELOG("allocate shm space error, ftok failed\n");
        return -1;
    }

    m_iShmID = shmget(m_uiShmKey, iSize, iFlag);
    if (m_iShmID < 0)
    {
        TRACELOG("allocate shm space error, shmget failed\n");
        return -1;
    }

    m_pShmAdress = (char*)shmat(m_iShmID, NULL, 0);
    if (NULL == m_pShmAdress)
    {
        TRACELOG("allocate shm space error, shmat failed\n");
        return -1;
    }

    m_iShmSize = iSize;

    return 0;
}

// 
const char* CSharedMemory::getInitAdress()
{
    return m_pShmAdress;
}

// 
const char* CSharedMemory::getFreeAdress()
{
    return m_pShmAdress + m_iFreeOffset;
}

// 
int CSharedMemory::setFreeAdress(int iSize)
{
    if (iSize <= 0)
    {
        TRACELOG("use shm space error, size: %d\n", iSize);
        return -1;
    }

    if (iSize > (m_iShmSize - m_iFreeOffset))
    {
        TRACELOG("use shm space error, shm space full\n");
        return -1;
    }

    m_iFreeOffset += iSize;

    return 0;
}
