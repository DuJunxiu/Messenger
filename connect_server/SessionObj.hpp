
#ifndef __SESSION_OBJ_HPP__
#define __SESSION_OBJ_HPP__

#include "RoleObj.hpp"
#include "ObjHelper.hpp"

using namespace MyMessenger;

class CSessionObj : public CObj
{
public:
    void setUserID(int iUserID) { m_iUsrerID = iUserID; }

    void bindRoleObject(int iObjectID) { m_iRoleIndex = iObjectID; }

private:
    int m_iSessionID;
    int m_iUsrerID;
    int m_iRoleIndex;
};

#endif