
#include "Handler.hpp"

CHandler::CHandler()
{
    m_pstRoleObj = NULL;
    m_pstReqMsg = NULL;
    m_iMsgID = -1;
}

// void CHandler::setMsgID(int iMsgID)
// {
    // m_iMsgID = iMsgID;
// }

int CHandler::getMsgID()
{
    // return m_iMsgID;
    if (NULL == m_pstReqMsg)
    {
        return -1;
    }

    return m_pstReqMsg->stMsgHead.m_iMsgID;
}

void CHandler::setReqMsgInfo(MainMsg* stReqMsg)
{
    m_pstReqMsg = stReqMsg;

    return;
}
