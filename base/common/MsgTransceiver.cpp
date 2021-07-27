
#include "MsgTransceiver.hpp"
#include "Connector.hpp"

CMsgTransceiver::CMsgTransceiver()
{}

CMsgTransceiver::~CMsgTransceiver()
{}

int CMsgTransceiver::unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, char& type, short& command, int& length)
{
    ASSERT_AND_LOG_RTN_INT(pConn);
    ASSERT_AND_LOG_RTN_INT(pBuffer);

    // 上一次的还没接收完
    if (pConn->getLastBytes() > 0)
    {
        length = pBuffer->getSize() >= pConn->getLastBytes() ? pConn->getLastBytes() : pBuffer->getSize();
        return 0;
    }

    // 不够一个包先不管
    if (pBuffer->getSize() <= sizeof(MsgHead))
    {
        return -1;
    }

    int offset = 0;
    type = *(pBuffer->getBuffer() + offset);
    offset += sizeof(type);
    command = *(short*)(pBuffer->getBuffer() + offset);
    offset += sizeof(command);
    length = *(int*)(pBuffer->getBuffer() + offset);
    offset += sizeof(length);

    // 包不完整先不管
    if (pBuffer->getSize() - offset < length)
    {
        return -1;
    }

    return 0;
}

int CMsgTransceiver::packageMsg()
{
    return 0;
}
