
#include "PackageDeal.hpp"
#include "Connector.hpp"
#include "Protocol.hpp"

CPackageDeal::CPackageDeal()
{}

CPackageDeal::~CPackageDeal()
{}

int CPackageDeal::unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, MainMsg& stMsg)
{
    ASSERT_AND_LOG_RTN_INT(pConn);
    ASSERT_AND_LOG_RTN_INT(pBuffer);

    // 不够一个包先不管
    if (pBuffer->getSize() <= sizeof(MsgHead))
    {
        return -1;
    }

    stMsg.stMsgHead.m_ucMsgType = *(pBuffer->getBuffer() + offsetof(MainMsg, m_ucMsgType));
    stMsg.stMsgHead.m_usVersion = ntohs(*(uint16_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_usVersion)));
    stMsg.stMsgHead.m_usMsgID = ntohs(*(uint16_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_usMsgID)));
    stMsg.stMsgHead.m_uiMsgLength = ntohl(*(uint32_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_uiMsgLength)));

    // 包不完整先不管
    if (pBuffer->getSize() - sizeof(MainMsg) < stMsg.stMsgHead.m_uiMsgLength)
    {
        return -1;
    }

    // 解包体

    return 0;
}

int CPackageDeal::packageMsg()
{
    return 0;
}
