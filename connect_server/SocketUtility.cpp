
#include "SocketUtility.hpp"

using namespace MyMessenger;

int CSocketUtility::createSocket(void)
{
    int iSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (iSockFD <= 0)
    {
        TRACELOG("Create Socket Failed !\n");
        return -1;
    }

    return iSockFD;
}

int CSocketUtility::bindAddress(int iSockFD, const char* pszIP, uint16_t usPort)
{
    struct sockaddr_in stSockAddr;
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_addr.s_addr = inet_addr(pszIP);
    stSockAddr.sin_port = ntohs(usPort);

    int iRet = bind(iSockFD, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));
    if (iRet < 0)
    {
        TRACELOG("Bind Address Failed IP = %s, Port = %u\n", pszIP, usPort);
    }

    return iRet;
}

void CSocketUtility::listenSocket(int iSockFD)
{
    listen(iSockFD, MAX_LISTEN_SOCKET_COUNT);
    return;
}

int CSocketUtility::acceptRequest()
{
    return 0;
}
