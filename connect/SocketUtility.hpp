
#ifndef __SOCKET_UTILITYHPP__
#define __SOCKET_UTILITYHPP__

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "LogDeal.hpp"

namespace MyMessenger
{
    const int MAX_LISTEN_SOCKET_COUNT = 5;
    
    class CSocketUtility
    {
    public:
        CSocketUtility()    {}
        ~CSocketUtility()    {}

    public:
        // 初始化
        int initialize(void);

        // 创建socket
        int createSocket(void);

        // 绑定地址
        int bindAddress(int iSockFD, const char* pszIP, uint16_t usPort = 0);

        // 监听socket
        void listenSocket(void);

        // 接收消息
        int acceptRequest();

    };
}

#endif
