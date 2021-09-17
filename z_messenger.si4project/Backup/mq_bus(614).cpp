
#include "mq_bus.hpp"
#include "SemLock.hpp"

using namespace MyMessenger;


CMQBus::CMQBus()
{
    m_pstShm = nullptr;
    m_pstSemLock = nullptr;
}

CMQBus::~CMQBus()
{}

int CMQBus::initialize(int iKey, int iSize)
{
    // 创建共享内存
    m_pstShm = new CSharedMemory;
    if (nullptr == m_pstShm)
    {
        printf("mq_bus new CSharedMemory failed\n");
        return -1;
    }

    int iRet = m_pstShm->allocateShmSpace(iKey, BUS_HEAD_LENGTH + iSize);
    if (iRet < 0)
    {
        printf("mq_bus allocateShmSpace failed\n");
        return -2;
    }

    // 创建互斥锁
    m_pstSemLock = new CSemLock;
    if (nullptr == m_pstSemLock)
    {
        printf("mq_bus new CSemLock failed\n");
        return -3;
    }

    m_pstSemLock->initialize(iKey);

    // 初始化队列头部
    memset(m_pstShm, 0, BUS_HEAD_LENGTH + iSize);
    m_pHead = (BusHead *)m_pstShm;
    m_pHead->m_iLength = iSize;
    m_pHead->m_iHead = 0;
    m_pHead->m_iTail = 0;
    m_pHead->m_iBlockNumber = 0;
    m_pHead->m_iUsedNumber = 0;

    TRACELOG("init bus mq --- key = %d, size = %d\n", iKey, iSize);

    return 0;
}

// 数据出队列
int CMQBus::busDequeue()
{
    return 0;
}

// 数据进队列
int CMQBus::busEequeue()
{
    return 0;
}

