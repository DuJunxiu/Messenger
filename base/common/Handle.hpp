
#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include "Protocol.hpp"
#include "LogDeal.hpp"

typedef struct
{
    int iSocketID;
    uint32_t uiSrcIP;
} NetHead;

class CHandle
{
public:
    CHandle();
    virtual ~CHandle() {}

public:
    void setReqMsgInfo(MainMsg* stReqMsg);

    // void setMsgID(int iMsgID);

    int getMsgID();

public:
    // 消息转发
    virtual int onMsgTransmit(const MainMsg& stMsg);

private:
    // int m_iMsgID;
    MainMsg* m_pstReqMsg;
};

#endif
