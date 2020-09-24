
#include "Socket.hpp"

using namespace MyMessenger;

int CSocket::initialize(void)
{
    m_iServerSockFD = 0;
    
    int iRet = createSocket();
    if (iRet <= 0)
    {
        return iRet;
    }

    return 0;
}

int CSocket::createSocket(void)
{
    int m_iServerSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_iServerSockFD <= 0)
    {
        // ERRLOG("Create Socket Failed !\n");
        return -1;
    }

    return m_iServerSockFD;
}

int CSocket::bindAddress(std::string strIP, uint16_t usPort)
{
    struct sockaddr_in stSockAddr;
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_addr.s_addr = inet_addr(strIP.c_str());
    stSockAddr.sin_port = ntohs(usPort);
    
    int iRet = bind(m_iServerSockFD, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));
    if (iRet < 0)
    {
        // ERRLOG("Bind Address Failed IP = %s, Port = %u\n", strIP, usPort);
    }

    return iRet;
}

void CSocket::listenSocket(void)
{
    listen(m_iServerSockFD, MAX_LISTEN_SOCKET_COUNT);
    return;
}

int CSocket::acceptRequest()
{
    return 0;
}
