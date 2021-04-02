
#ifndef __PROTOCOL_DEAL_HPP__
#define __PROTOCOL_DEAL_HPP__

class CProtocolDeal
{
public:
    CProtocolDeal();
    ~CProtocolDeal();

public:
    void onRecvRequest();

private:
    // 协议解码
    void decodeProtocol();

private:

};

#endif
