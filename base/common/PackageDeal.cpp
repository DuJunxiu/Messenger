
#include "PackageDeal.hpp"
#include "Connector.hpp"
#include "Protocol.hpp"

CPackageDeal::CPackageDeal()
{}

CPackageDeal::~CPackageDeal()
{}

int CPackageDeal::unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, MsgHead& stHead)
{
    ASSERT_AND_LOG_RTN_INT(pConn);
    ASSERT_AND_LOG_RTN_INT(pBuffer);

    // 不够一个包先不管
    if (pBuffer->getSize() <= sizeof(MsgHead))
    {
        return -1;
    }

    stHead.m_ucMsgType = *(pBuffer->getBuffer() + offsetof(MainMsg, m_ucMsgType));
    stHead.m_usVersion = ntohs(*(uint16_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_usVersion)));
    stHead.m_usMsgID = ntohs(*(uint16_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_usMsgID)));
    stHead.m_uiMsgLength = ntohl(*(uint32_t*)(pBuffer->getBuffer() + offsetof(MainMsg, m_uiMsgLength)));

    // 包不完整先不管
    if (pBuffer->getSize() - offset < stHead.m_uiMsgLength)
    {
        return -1;
    }

    return 0;
}

int CPackageDeal::packageMsg()
{
    return 0;
}
