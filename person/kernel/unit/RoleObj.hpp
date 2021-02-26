
#ifndef __ROLE_OBJ_HPP__
#define __ROLE_OBJ_HPP__

#include "Protocol.hpp"
#include "ObjHelper.hpp"
#include "LogDeal.hpp"

using namespace MyMessenger;

class CRoleObj : public CObj
{
public:
    virtual int initialize();

private:
    DBRoleInfo m_stRoleInfo;

// 角色登录状态 默认在线
public:
    void onSetStatus(unsigned char ucStatus) { m_ucStatus = ucStatus; }
    unsigned char onGetStatus() { return m_ucStatus; }
private:
    unsigned char m_ucStatus;

};

#endif
