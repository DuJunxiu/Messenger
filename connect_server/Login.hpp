
#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__

#include "Handler.hpp"
#include "RoleObj.hpp"

class CLoginHandler : public CHandler
{
public:
    virtual void onClientMsg();

public:
    int onLoginRole();

private:
    CRoleObj* m_pRoleObj;
};

#endif
