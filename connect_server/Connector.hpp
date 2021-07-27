
#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

// TCP连接类，管理TCP连接，负责TCP收发包

#include "Buffer.hpp"

class CConnector
{
public:
    CConnector();
    ~CConnector();

public:
    int getSocket() { return m_socket; }
    void setSocket(net_handle_t sock) { m_socket = sock; }

    int getLastBytes() { return m_recvBytes; }
    void setLastBytes(int size) { m_recvBytes = size; }

public:
    int onRecvData();
    int onSendData(const char* pcSendData, int iLength);

    int onRead();
    int onWrite();

private:
    net_handle_t m_socket;          // 连接的socket
    CBuffer* m_pRecvBuffer;         // 接收缓冲区
    CBuffer* m_pSendBuffer;         // 发送缓冲区
    bool m_busy;                    // 操作的互斥变量
    int m_recvBytes;                // 接收到的剩余字节
};

#endif

