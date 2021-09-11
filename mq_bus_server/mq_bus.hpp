
#ifndef __MQ_BUS_HPP__
#define __MQ_BUS_HPP__

namespace MyMessenger
{
    class CMQBus
    {
    public:
        CMQBus();
        ~CMQBus();

    public:
        int initialize(int iKey);

    private:
        CSharedMemory* m_pstShm;    // 共享内存
        CSemLock* m_pstSemLock;     // 互斥锁
    };

    // 一个bus中间件的实例
    typedef CSingleton<CMQBus> MQBusSingleton;

}

#endif

