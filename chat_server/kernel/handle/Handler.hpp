
#ifndef __HANDLER_HPP__
#define __HANDLER_HPP__

#include "Protocol.hpp"
#include "RoleObj.hpp"

class CHandler
{
public:
    CHandler();
    virtual ~CHandler() {}

public:
    void setReqMsgInfo(MainMsg* stReqMsg);

    // void setMsgID(int iMsgID);

    int getMsgID();

public:
    // 子协议处理函数
    virtual void onClientMsg();

private:
    // int m_iMsgID;
    CRoleObj* m_pstRoleObj;
    MainMsg* m_pstReqMsg;

};

#endif
