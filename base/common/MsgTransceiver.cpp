
#include "MsgTransceiver.hpp"
#include "Connector.hpp"

CMsgTransceiver::CMsgTransceiver()
{}

CMsgTransceiver::~CMsgTransceiver()
{}

int CMsgTransceiver::unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, char& protocal, short& command, int& length)
{
    ASSERT_AND_LOG_RTN_INT(pConn);
    ASSERT_AND_LOG_RTN_INT(pBuffer);

    // 先检查能否解包
    if (!checkCanUnpack(pConn, pBuffer))
    {
        return -1;
    }
}

bool CMsgTransceiver::checkCanUnpack(const CConnector* pConn, const CBuffer* pBuffer)
{
    ASSERT_AND_LOG_RTN_BOOL(pConn);
    ASSERT_AND_LOG_RTN_BOOL(pBuffer);

    // 上一次的还没接收完
    if (pConn->getLastBytes() > 0)
    {
    }

    // 不够一个包先不管
    if (pBuffer->getSize() < sizeof(MsgHead))
    {
        return false;
    }
}
