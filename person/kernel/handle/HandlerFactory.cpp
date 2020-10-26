
#include "HandlerFactory.hpp"

CHandler* CHandlerFactory::m_apHandler[MAX_HANDLER_COUNT];

CHandlerFactory::CHandlerFactory()
{}

CHandlerFactory::~CHandlerFactory()
{}

void CHandlerFactory::registerHandler(const unsigned int uiMsgID, const CHandler* pHandler)
{
    if (uiMsgID > MAX_HANDLER_COUNT)
    {
        TRACELOG("Error MsgID : %u\n", uiMsgID);
        return;
    }

    if (NULL == pHandler)
    {
        TRACELOG("Error pHandler NULL\n");
        return;
    }

    // 不能重复注册
    if (m_apHandler[uiMsgID - 1])
    {
        TRACELOG("Error repeat register MsgID = %u\n", uiMsgID);
        return;
    }

    m_apHandler[uiMsgID - 1] = (CHandler*)pHandler;
}

CHandler* CHandlerFactory::getHandler(const unsigned int uiMsgID)
{
    if (uiMsgID > MAX_HANDLER_COUNT)
    {
        TRACELOG("Error MsgID : %u\n", uiMsgID);
        return;
    }

    // 未注册的话，就是 NULL
    return m_apHandler[uiMsgID - 1];
}
