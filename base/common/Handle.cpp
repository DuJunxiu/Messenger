
#include "Handle.hpp"

CHandle::CHandle()
{
    m_pstReqMsg = nullptr;
    // m_iMsgID = -1;
}

// void CHandle::setMsgID(int iMsgID)
// {
    // m_iMsgID = iMsgID;
// }

int CHandle::getMsgID()
{
    // return m_iMsgID;
    if (nullptr == m_pstReqMsg)
    {
        return -1;
    }

    return m_pstReqMsg->stMsgHead.m_iMsgID;
}

void CHandle::setReqMsgInfo(MainMsg* stReqMsg)
{
    m_pstReqMsg = stReqMsg;

    return;
}
