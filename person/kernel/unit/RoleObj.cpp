
#include "RoleObj.hpp"

IMPLEMENT_DYN(CRoleObj)

int CRoleObj::initialize()
{
    m_ucStatus = LOGIN_STATUS_ONLINE;
    return 0;
}
