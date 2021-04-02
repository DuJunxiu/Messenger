
#ifndef __SESSION_MANAGER_HPP__
#define __SESSION_MANAGER_HPP__

#include "ObjHelper.hpp"
#include "SessionObj.hpp"

using namespace MyMessenger;

const int MAX_SESSION_COUNT = 1000;

class CSessionManager
{
public:
    CSessionManager() {}
    ~CSessionManager() {}
public:
    // 通过socket创建sessionID
    CSessionObj* onCreateSession(const int iSocketFD, const int iUserID);

    int onDeleteSession(const int iSessionID);

    CSessionObj* findSessionByID(const int iSessionID);
};

#endif