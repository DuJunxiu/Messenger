
#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__

#include "Handler.hpp"
#include "RoleObj.hpp"

class CLoginHandler : public CHandler
{
public:
    virtual int onClientMsg();

public:
    int onLoginRole(int iUserID);

private:
    CRoleObj* m_pRoleObj;
};

#endif
