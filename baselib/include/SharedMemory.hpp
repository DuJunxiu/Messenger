
#ifndef __SHARED_MEMORY_HPP__
#define __SHARED_MEMORY_HPP__

const char* SHM_KEY_FILE = "../../tmp/key.txt";

class CSharedMemory
{
public:
    CSharedMemory();
    ~CSharedMemory();

private:
    int initialize();

    int destory();

public:
    key_t getShmKey();

    int getShmID();

    // #define IPC_CREAT    01000    /* Create key if key does not exist. */
    // #define IPC_EXCL     02000    /* Fail if key exists.  */
    // 申请分配共享内存空间
    int allocateShmSpace(int iSize = 4096, int iFlag = IPC_CREAT|IPC_EXCL|0666);

    // 
    const char* getInitAdress() const;

    // 
    const char* getFreeAdress() const;

    // 
    int setFreeAdress(int iSize);

private:
    key_t m_uiShmKey;   // 
    int m_iShmID;       // 
    int m_iShmSize;     // 
    int m_iFreeOffset;  // 空闲的偏移量
    char* m_pShmAdress; // 指向共享内存第一个字节地址的指针
};

#endif