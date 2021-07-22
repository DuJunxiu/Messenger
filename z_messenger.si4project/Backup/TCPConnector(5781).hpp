
#ifndef __TCP_CONNECTOR_HPP__
#define __TCP_CONNECTOR_HPP__

// TCP连接类，管理TCP连接，负责TCP收发包

#include <mutex>
#include "Buffer.hpp"

class CTCPConnector
{
public:
    CTCPConnector();
    ~CTCPConnector();

public:
    int getSocket() { return m_pSocket->getSocket(); }
    void setSocket(net_handle_t sock) { m_pSocket->setSocket(sock); }

public:
    int onRecvData(int iSocket);

    int onSendData(const char* pcSendData, int iLength);

private:
    CBaseSocket* m_pSocket;         // 连接的socket
    CBuffer m_stRecvBuffer;         // 接收缓冲区
    CBuffer m_stSendBuffer;         // 发送缓冲区
    pthread_mutex_t m_stMutex;      // 操作的互斥变量
};

#endif

