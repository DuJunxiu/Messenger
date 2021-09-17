
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

int CMQBus::initialize(int iKey)
{
    // 创建共享内存
    m_pstShm = new CSharedMemory;
    if (nullptr == m_pstShm)
    {
        printf("mq_bus new CSharedMemory failed\n");
        return -1;
    }

    int iRet = m_pstShm->allocateShmSpace(iKey);
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

    return 0;
}


