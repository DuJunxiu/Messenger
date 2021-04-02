
#ifndef __HANDLER_HPP__
#define __HANDLER_HPP__

#include "Protocol.hpp"

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
    virtual int onClientMsg();

private:
    // int m_iMsgID;
    MainMsg* m_pstReqMsg;
};

#endif
