
/*
*   消息队列中间件(循环队列)
*/

#ifndef __MQ_BUS_HPP__
#define __MQ_BUS_HPP__

namespace MyMessenger
{
/*
*    head | block_head_1 | block_data_1 | block_head_2 | block_data_2 ...
*/

    typedef struct tagBusHead
    {
        int m_iLength;      // 队列总长度(byte)
        int m_iHead;        // 数据起始偏移量(byte)
        int m_iTail;        // 数据结束偏移量(byte)
        int m_iBlockNumber; // 数据块总数
        int m_iUsedNumber;  // 已使用的数据块
    } BusHead;

    typedef struct tagBlockHead
    {
        int m_iIndex;       // 数据库索引
        int m_iLength;      // 数据长度(byte)
    } BlockHead;

    const int BUS_HEAD_LENGTH = sizeof(BusHead);

    class CMQBus
    {
    public:
        CMQBus();
        ~CMQBus();

    public:
        int initialize(int iKey, int iSize);

        // 数据出队列
        int busDequeue();

        // 数据进队列
        int busEequeue();

    private:
        CSharedMemory* m_pstShm;    // 共享内存
        CSemLock* m_pstSemLock;     // 互斥锁
        BusHead* m_pHead;           // 头部指针
    };

    // 一个bus中间件的实例
    typedef CSingleton<CMQBus> MQBusSingleton;

}

#endif

