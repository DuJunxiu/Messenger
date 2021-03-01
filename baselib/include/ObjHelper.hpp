
#ifndef __OBJ_HELPER_HPP__
#define __OBJ_HELPER_HPP__

#include <list>
#include <hash_map>
// #include "HashMap.hpp"

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

        int getObjectID() { return m_iObjectID; }

    private:
        int m_iObjectID;    // 对象ID，用于一条链表上的索引
    };


    ////////////////////////////////////////////////////////////////////////////


    // 对象分配器
    class CObjAllocator
    {
    private:
        CObjAllocator() {}
        ~CObjAllocator() {}
    public:
        static CObjAllocator* onCreateOByShm()
        {
            return nullptr;
        }

        CObj* getObjByID(int iObjID)
        {
            for (std::list<CObj>::iterator it = m_stObjList.begin(); it != m_stObjList.end(); ++it)
            {
                if (it->getObjectID() == iObjID)
                {
                    return &(*it);
                }
            }

            return nullptr;
        }

    private:
        std::list<CObj> m_stObjList;    // 对象列表
        int m_iUsedCount;               // 已用对象数
        int m_iFreeHeadIndex;           // 空闲对象头索引
    };


    ////////////////////////////////////////////////////////////////////////////


    // 对象操作器
    template<typename OBJECT_TYPE>
    class CObjHelper
    {
    public:

    private:
        static CObjAllocator* m_pstAllocator;
        static std::hash_map<int , OBJECT_TYPE>* m_pstHashMap;
    };

    template<typename OBJECT_TYPE>
    CObjAllocator* CObjHelper<OBJECT_TYPE>::m_pstAllocator = nullptr;

    template<typename OBJECT_TYPE>
    std::hash_map<int , OBJECT_TYPE>* CObjHelper<OBJECT_TYPE>::m_pstHashMap = nullptr;

}

#endif
