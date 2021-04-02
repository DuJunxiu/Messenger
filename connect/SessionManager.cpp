
#include <arpa/inet.h>
#include "SessionManager.hpp"

CSessionObj* CSessionManager::onCreateSession(const int iSocketFD, const int iUserID)
{
    // 对象数不能超
    if (CObjHelper<CSessionObj>::getUsedCount() >= MAX_SESSION_COUNT)
    {
        return nullptr;
    }

    int iSessionID = ntohl(iSocketFD);

    // 先看一下是否已存在session
    CSessionObj* pSessionObj = findSessionByID(iSessionID);
    if (pSessionObj)
    {
        // return pSessionObj;
        return nullptr;
    }

    // 创建新的session对象
    CSessionObj* pNewSession = CObjHelper<CSessionObj>::createObjByKey(iSessionID);
    if (nullptr == pNewSession)
    {
        return nullptr;
    }

    TRACELOG("create session : %d\n", iSessionID);
}

int CSessionManager::onDeleteSession(const int iSessionID)
{}

CSessionObj* CSessionManager::findSessionByID(const int iSessionID)
{}