
#ifndef __SHARED_MEMORY_HPP__
#define __SHARED_MEMORY_HPP__

#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>

struct ShmTest
{
	char m_acBuffer[32];
};

const char* SHM_KEY_FILE = "../../tmp";

class CSharedMemory
{
public:
    CSharedMemory();
    ~CSharedMemory();

private:
    int initialize()
    {
        m_uiShmKey = 0;
        m_iShmID = 0;
        m_iFreeOffset = 0;
        m_pShmAdress = NULL;

        printf("----- initialize -----\n");

        return 0;
    }

    int destory()
    {
        if (m_iShmID <= 0)
        {
            return 0;
        }

        printf("----- destory -----\n");

        return shmctl(m_iShmID, IPC_RMID, NULL);
    }

public:
    key_t getShmKey() { return m_uiShmKey; }

    // 申请分配共享内存空间
    int allocateShmSpace(int iSize = 4096, int iFlag = IPC_CREAT|IPC_EXCL|0666)
    {
        key_t m_uiShmKey = ftok(SHM_KEY_FILE, 255);
        if (m_uiShmKey < 0)
        {
            printf("allocate shm space error, ftok failed\n");
            return -1;
        }

        m_iShmID = shmget(m_uiShmKey, iSize, iFlag);
        if (m_iShmID < 0)
        {
            printf("allocate shm space error, shmget failed\n");
            return -1;
        }

        m_pShmAdress = (char*)shmat(m_iShmID, NULL, 0);
        if (NULL == m_pShmAdress)
        {
            printf("allocate shm space error, shmat failed\n");
            return -1;
        }

        m_iShmSize = iSize;

        return 0;
    }

    // 
    const char* getInitAdress() { return m_pShmAdress; }

    // 
    const char* getFreeAdress() { return m_pShmAdress + m_iFreeOffset; }

    // 
    int setFreeAdress(int iSize)
    {
        if (iSize <= 0)
        {
            printf("use shm space error, size: %d\n", iSize);
            return -1;
        }

        if (iSize > (m_iShmSize - m_iFreeOffset))
        {
            printf("use shm space error, shm space full\n");
            return -1;
        }

        m_iFreeOffset += iSize;

        return 0;
    }

private:
    key_t m_uiShmKey;   // 
    int m_iShmID;       // 
    int m_iShmSize;     // 
    int m_iFreeOffset;  // 空闲的偏移量
    char* m_pShmAdress; // 指向共享内存第一个字节地址的指针
};

#endif