
#ifndef __MSG_TRANSCEIVER_HPP
#define __MSG_TRANSCEIVER_HPP

class CMsgTransceiver
{
public:
    CMsgTransceiver();
    ~CMsgTransceiver();

public:
    static int unpackMsg(const CConnector* pConn, const CBuffer* pBuffer, char& type, short& command, int& length);
    static int packageMsg();

private:

};

#endif

