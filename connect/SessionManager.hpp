
#ifndef __SESSION_MANAGER_HPP__
#define __SESSION_MANAGER_HPP__

#include "SessionObj.hpp"

class CSessionManager
{
public:
    CSessionManager() {}
    ~CSessionManager() {}
public:
    // 通过socket创建sessionID
    CSessionObj* onCreateSession(const int iSocketFD, const int iUserID);
    int onDeleteSession();
};

#endif