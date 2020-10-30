
#ifndef __OBJ_HPP__
#define __OBJ_HPP__

namespace MyMessenger
{
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
