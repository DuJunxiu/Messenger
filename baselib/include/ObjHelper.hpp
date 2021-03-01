
#ifndef __OBJ_HELPER_HPP__
#define __OBJ_HELPER_HPP__

#include <list>
#include <hash_map>
#include "SharedMemory.hpp"
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

    private:
        int m_iObjectID;    // 对象ID，用于一条链表上的索引
    };


    ////////////////////////////////////////////////////////////////////////////


    typedef CObj* (*Function_CreateObject)(void*);

    // 对象分配器
    class CObjAllocator
    {
    private:
        CObjAllocator() {}
        ~CObjAllocator() {}
    public:
        static CObjAllocator* onCreateByShm(const char* pszFileName, const size_t uiKey, int iObjCount, size_t uiObjSize, Function_CreateObject pfCreateObj)
        {
            if (nullptr == pszFileName || nullptr == pfCreateObj || uiKey == 0 || uiObjSize == 0 || iObjCount <= 0)
            {
                return nullptr;
            }

            int iShmSize = sizeof(CObjAllocator) + iObjCount * uiObjSize;

            CSharedMemory stSharedMemory;
            int iRet = stSharedMemory.allocateShmSpace(uiKey, iShmSize);
            if (iRet < 0)
            {
                return nullptr;
            }

            CObjAllocator* pstObjAllocator = (CObjAllocator*)stSharedMemory.getFreeAdress();
            if (nullptr == pstObjAllocator)
            {
                return nullptr;
            }

            pstObjAllocator->m_iMaxObjCount = iObjCount;
            pstObjAllocator->m_uiObjSize = uiObjSize;
            pstObjAllocator->m_iUsedCount = 0;

            return pstObjAllocator;
        }

    public:
        int onCreateObject()
        {
            std::list<CObj>::iterator it = m_stObjList.end();

            return 0;
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
        int m_iMaxObjCount;             // 最大对象数
        size_t m_uiObjSize;             // 单个对象大小
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
