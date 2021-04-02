
#ifndef __OBJ_HELPER_HPP__
#define __OBJ_HELPER_HPP__

#include <list>
#include <unordered_map>
#include <hash_map>
#include "SharedMemory.hpp"
// #include "HashMap.hpp"

namespace MyMessenger
{

    class CObj;

    typedef enum enmIdxUseFlag
    {
        EIUF_FREE = 0, //该对象未被使用
        EIUF_USED = 1, //该对象已被使用
    } ENMIDXUSEFLAG;

    //索引类，仅在CObjAllocator中使用，外层一般不用
    class CIdx
    {
    public:
        CIdx();
        ~CIdx();

    public:
        // 初始化函数
        int Initialize()
        {
            m_iNextIdx = -1;
            m_iPrevIdx = -1;
            m_iUseFlag = 0;
            m_pAttachedObj = nullptr;

            return 0;
        }

        // 将对象设置为未使用
        inline void SetFree() { m_iUseFlag = EIUF_FREE; }

        // 将对象设置为已使用
        inline void SetUsed() { m_iUseFlag = EIUF_USED; }

        // 判断对象是否已被使用
        inline bool IsUsed() const { return m_iUseFlag == EIUF_USED; }

        // 获取所在链表下一个索引
        inline int GetNextIdx() const { return m_iNextIdx; }

        // 设置所在链表下一个索引
        inline void SetNextIdx(int iIdx) { m_iNextIdx = iIdx; }

        // 获取所在链表上一个索引
        inline int GetPrevIdx() const { return m_iPrevIdx; }

        // 设置所在链表上一个索引
        inline void SetPrevIdx(int iIdx) { m_iPrevIdx = iIdx; }

        // 获取指向的对象
        inline CObj* GetAttachedObj() const { return m_pAttachedObj; }

        // 设置指向的对象
        inline void SetAttachedObj(CObj *pObj) { m_pAttachedObj = pObj; }

    private:
        int m_iNextIdx;         // 对象索引块链表指针，指向后一个闲/忙索引
        int m_iPrevIdx;         // 对象索引块链表指针，指向前一个闲/忙索引
        int m_iUseFlag;         // 该对象是否已经被使用标志
        CObj *m_pAttachedObj;   // 所指向的对象指针
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

            int iShmSize = sizeof(CObjAllocator) + sizeof(CIdx) * iObjCount /*+ iObjCount * uiObjSize*/;

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
            pstObjAllocator->m_astIndex = (CIdx*)((char*)stSharedMemory.getFreeAdress() + sizeof(CObjAllocator));

            return pstObjAllocator;
        }

    public:
        int onCreateObject()
        {
            if (nullptr == m_astIndex)
            {
                return -1;
            }

            if (m_iUsedCount >= m_iMaxObjCount)
            {
                return -2;
            }

            int iInsertIdx = m_iUsedCount;
            if (m_iFreeHeadIndex >= 0)
            {
                // 尝试在空闲节点上创建
                iInsertIdx = m_iFreeHeadIndex;
            }

            m_astIndex[iInsertIdx].SetUsed();
            m_astIndex[iInsertIdx].SetPrevIdx(m_iUsedCount);
            m_astIndex[iInsertIdx].SetNextIdx(-1);

            if (m_iFreeHeadIndex >= 0)
            {
                m_astIndex[iInsertIdx].SetPrevIdx(m_iFreeHeadIndex > 0 ? m_iFreeHeadIndex - 1 : -1);    // m_iFreeHeadIndex 是否是第一个节点
                m_astIndex[iInsertIdx].SetNextIdx(m_iFreeHeadIndex != m_iUsedCount + 1 ? m_iFreeTailIndex + 1 : -1);    // m_iFreeHeadIndex 是否是最后一个节点
                ++m_iFreeHeadIndex;
                if (m_iFreeHeadIndex > m_iFreeTailIndex)
                {
                    m_iFreeTailIndex = m_iFreeHeadIndex = -1;
                }
            }

            CObj* pstObject = m_astIndex[iInsertIdx].GetAttachedObj();
            if (nullptr == pstObject)
            {
                return -3;
            }

            memset(pstObject, 0, m_uiObjSize);
            (*m_pfCreateObject)((char*)pstObject);
            pstObject->setObjectID(iInsertIdx);
            pstObject->initialize();

            ++m_iUsedCount;

            return iInsertIdx;
        }

        int onDestoryObject(int iObjectID)
        {
            if (iObjectID < 0 || iObjectID >= m_iMaxObjCount)
            {
                return -1;
            }

            if (!m_astIndex[iObjectID].IsUsed())
            {
                return -1;
            }

            int iPrevIdx = m_astIndex[iObjectID].GetPrevIdx();
            int iNextIdx = m_astIndex[iObjectID].GetNextIdx();

            if (iPrevIdx >= 0)
            {
                m_astIndex[iPrevIdx].SetNextIdx(iNextIdx);
            }
            if (iNextIdx >= 0)
            {
                m_astIndex[iNextIdx].SetPrevIdx(iPrevIdx);
            }

            m_astIndex[iObjectID].SetFree();
            m_astIndex[iObjectID].SetPrevIdx(-1);
            m_astIndex[iObjectID].SetNextIdx(-1);

            --m_iUsedCount;

            return 0;
        }

        CObj* getObjByID(int iObjectID)
        {
            if (nullptr == m_astIndex)
            {
                return nullptr;
            }

            if (iObjectID < 0 || iObjectID >= m_iMaxObjCount)
            {
                return nullptr;
            }

            if (!m_astIndex[iObjectID].IsUsed())
            {
                return nullptr;
            }

            return m_astIndex[iObjectID].GetAttachedObj();
        }

        CObj* getNextObj(int iObjectID)
        {
            if(iObjectID < 0 || iObjectID >= m_iMaxObjCount)
            {
                return nullptr;
            }

            if(!m_astIndex[iObjectID].IsUsed())
            {
                return nullptr;
            }

            CIdx* pIdx = &m_astIndex[iObjectID];
            if (nullptr == pIdx)
            {
                return nullptr;
            }

            int iNextObjIdx = pIdx->GetNextIdx();

            return getObjByID(iNextObjIdx);
        }

        int getUsedCount() { return m_iUsedCount; }

        CIdx* getIndex(const int iObjectID)
        {
            if(iObjectID < 0 || iObjectID >= m_iMaxObjCount)
            {
                return nullptr;
            }

            if (nullptr == m_astIndex)
            {
                return nullptr;
            }

            if (!m_astIndex[iObjectID].IsUsed())
            {
                return nullptr;
            }

            return &m_astIndex[iObjectID];
        }

    private:
        CIdx* m_astIndex;                           // 索引数组，用于管理对象链表
        int m_iUsedCount;                           // 已用对象数
        int m_iMaxObjCount;                         // 最大对象数
        size_t m_uiObjSize;                         // 单个对象大小
        int m_iFreeHeadIndex;                       // 空闲的头索引
        int m_iFreeTailIndex;                       // 空闲的尾索引
        Function_CreateObject m_pfCreateObject;     // 在内存上创建CObj对象的函数，每个子类需要自己实现
    };


    ////////////////////////////////////////////////////////////////////////////


    // 对象操作器
    template<typename OBJECT_TYPE>
    class CObjHelper
    {
    public:
        static OBJECT_TYPE* createObjByKey(const int iKey)
        {
            int iIndex = m_pstAllocator->onCreateObject();
            if (iIndex < 0)
            {
                return nullptr;
            }

            m_pstHashMap[iIndex] = iKey;

            return (OBJECT_TYPE*)m_pstAllocator->getObjByID(iIndex);
        }

        static int destoryObjByKey(const int iKey)
        {
            // 先删哈希表
            int iIndex = m_pstHashMap->find(iKey)->second();
            m_pstHashMap->erase(iKey);

            // 再删共享内存上的对象
            int iRet = m_pstAllocator->onDestoryObject(iIndex);
            if (iRet < 0)
            {
                return -1;
            }

            return 0;
        }

        static int getUsedCount()
        {
            return m_pstAllocator->getUsedCount();
        }

        static int getNextIndex(const int iIndex)
        {
            CIdx* pIndex = m_pstAllocator->getIndex(iIndex);
            if (nullptr == pIndex)
            {
                return -1;
            }

            return pIndex->GetNextIdx();
        }

    public:
        static int registerAllocator(CObjAllocator* pstAllocator, std::unordered_map<int , OBJECT_TYPE>* pstHashMap)
        {
            if (nullptr == pstAllocator || nullptr == pstHashMap)
            {
                return -1;
            }

            m_pstAllocator = pstAllocator;
            m_pstHashMap = pstHashMap;

            return 0;
        }

    private:
        static CObjAllocator* m_pstAllocator;
        static std::unordered_map<int , int>* m_pstHashMap;
    };

    template<typename OBJECT_TYPE>
    CObjAllocator* CObjHelper<OBJECT_TYPE>::m_pstAllocator = nullptr;

    template<typename OBJECT_TYPE>
    std::unordered_map<int , int>* CObjHelper<OBJECT_TYPE>::m_pstHashMap = nullptr;


    ////////////////////////////////////////////////////////////////////////////


    // 对象基类
    class CObj
    {
    public:
        CObj() {}
        virtual ~CObj() {}

    public:
        virtual int initialize() = 0;

        void setObjectID(int iObjectID) { m_iObjectID = iObjectID; }
        int getObjectID() { return m_iObjectID; }
    private:
        int m_iObjectID;    // 对象ID，用于一条链表上的索引
    };


    #define DECLARE_DYN                                                          \
        public:                                                                  \
            void* operator new(size_t uiSize, const void* pThis) throw();        \
            static CObj* CreateObject(void* pMem);


    #define IMPLEMENT_DYN(class_name)                                            \
        void* class_name::operator new(size_t uiSize, const void* pThis) throw() \
        {                                                                        \
            if(!pThis)                                                           \
            {                                                                    \
                return nullptr;                                                  \
            }                                                                    \
                                                                                 \
            return (void*)pThis;                                                 \
        }                                                                        \
                                                                                 \
        CObj* class_name::CreateObject( void *pMem )                             \
        {                                                                        \
            return (CObj*)new(pMem) class_name;                                  \
        }

}

#endif
