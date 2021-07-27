
#include "HandleFactory.hpp"

CHandle* CHandleFactory::m_apHandle[MAX_MSGID_COUNT];

CHandleFactory::CHandleFactory()
{}

CHandleFactory::~CHandleFactory()
{}

void CHandleFactory::registerHandle(const unsigned int uiMsgID, const CHandle* pHandle)
{
    if (uiMsgID > MAX_MSGID_COUNT)
    {
        TRACELOG("Error MsgID : %u\n", uiMsgID);
        return;
    }

    if (nullptr == pHandle)
    {
        TRACELOG("Error pHandle NULL\n");
        return;
    }

    // 不能重复注册
    if (m_apHandle[uiMsgID - 1])
    {
        TRACELOG("Error repeat register MsgID : %u\n", uiMsgID);
        return;
    }

    m_apHandle[uiMsgID - 1] = (CHandle*)pHandle;
}

CHandle* CHandleFactory::getHandle(const unsigned int uiMsgID)
{
    if (uiMsgID > MAX_MSGID_COUNT)
    {
        TRACELOG("Error MsgID : %u\n", uiMsgID);
        return;
    }

    // 未注册的话，就是 nullptr
    return m_apHandle[uiMsgID - 1];
}
