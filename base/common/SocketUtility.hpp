
#ifndef __SOCKET_UTILITYHPP__
#define __SOCKET_UTILITYHPP__

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unorder_map>

#include "LogDeal.hpp"
#include "Config.h"

namespace MyMessenger
{
    const int MAX_LISTEN_SOCKET_COUNT = 5;

    #define ERROR_SOCKET    (-1)

    class CBaseSocket
    {

    enum
    {
        SOCKET_STATE_IDLE       = 0,
        SOCKET_STATE_LISTENING  = 1,
        SOCKET_STATE_CONNECTING = 2,
        SOCKET_STATE_CONNECTED  = 3,
        SOCKET_STATE_CLOSING    = 4
    };

    public:
        CBaseSocket();
        ~CBaseSocket();

    public:
        // 初始化
        int initialize(void);

        // 创建socket
        int createSocket(void);

        // 绑定地址
        int bindAddress(int iSockFD, const char* pszIP, uint16_t usPort = 0);

        // 监听socket
        int listenSocket(void);

        // 连接socket
        int connectSocket(const char* pszIP, uint16_t usPort);

        // 接收消息
        int recvMsg(void);

        // 发送消息
        int sendMsg(void);

        // 关闭
        void closeSocket(void);

    public:
        void OnRead();

        void OnWrite();

        void OnClose();

    public:
        net_handle_t getSocket() { return m_socket; }
        void setSocket(net_handle_t fd) { m_socket = fd; }

        uint8_t getState() { return m_state; }
        void setState(uint8_t state) { m_state = state; }

        char* getRemoteIP() { return m_remote_ip.c_str(); }
        void setRemoteIP(char* pRemoteIP) { m_remote_ip = to_string(pRemoteIP); }
        uint16_t getRemotePort() { return m_remote_port; }
        void setRemotePort(uint16_t port) { m_remote_port = port; }

        char* getLocalIP() { return m_local_ip.c_str(); }
        void setLocalIP(char* pLocalIP) { m_local_ip = to_string(pLocalIP); }
        uint16_t getLocalPort() { return m_local_port; }
        void setLocalPort(uint16_t port) { m_local_port = port; }

    private:
        std::string     m_remote_ip;    // 远程ip
        uint16_t        m_remote_port;  // 远程端口
        std::string     m_local_ip;     // 本地ip
        uint16_t        m_local_port;   // 本地端口

        net_handle_t    m_socket;       // socket id
        uint8_t         m_state;        // socket状态

    };
}

#endif
