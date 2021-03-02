
#ifndef __OBJ_HELPER_HPP__
#define __OBJ_HELPER_HPP__

#include <list>
#include <hash_map>
#include "SharedMemory.hpp"
// #include "HashMap.hpp"

namespace MyMessenger
{

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
        inline int IsUsed() const { return m_iUseFlag == EIUF_USED; }

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


    ////////////////////////////////////////////////////////////////////////////


    // typedef CObj* (*Function_CreateObject)(void*);

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

            ++m_iUsedCount;

            return iInsertIdx;
        }

        int onDestoryObject(int iObjectID)
        {
            return 0;
        }

        CObj* getObjByID(int iObjectID)
        {
            return nullptr;
        }

    private:
        CIdx* m_astIndex;               // 索引数组，用于管理对象链表
        int m_iUsedCount;               // 已用对象数
        int m_iMaxObjCount;             // 最大对象数
        size_t m_uiObjSize;             // 单个对象大小
        int m_iFreeHeadIndex;           // 空闲的头索引
        int m_iFreeTailIndex;           // 空闲的尾索引
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
