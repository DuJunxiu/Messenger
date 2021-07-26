
#include "MsgTransceiver.hpp"

CMsgTransceiver::CMsgTransceiver()
{}

CMsgTransceiver::~CMsgTransceiver()
{}

int CMsgTransceiver::unpackMsg(const CBuffer* pBuffer, char& protocal, short& command, int& length)
{
    ASSERT_AND_LOG_RTN_INT(pBuffer);
}
