
#ifndef __OBJ_HELPER_HPP__
#define __OBJ_HELPER_HPP__

namespace MyMessenger
{
    // 对象分配器
    class CObjAllocator
    {
    private:
        CObjAllocator() {}
    public:
        static CObjAllocator* onCreateOByShm()
        {
            return nullptr;
        }
    };

    // 对象操作器
    template<typename T>
    class CObjHelper
    {};

    // 对象基类
    class CObj
    {
    public:
        CObj() {}
        virtual ~CObj() {}

    public:
        virtual int initialize() = 0;

    private:
        int m_iObjectID;    // 对象ID，用于一条链表上的索引
    };
}

#endif
