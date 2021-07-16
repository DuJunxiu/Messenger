
#include "SocketUtility.hpp"

using namespace MyMessenger;

typedef std::unorder_map<net_handle_t, CBaseSocket*> SocketMap;
SocketMap* g_pSocketMap = nullptr;
//SocketMap g_pSocketMap;

void initSocketMap()
{
    if (nullptr != g_pSocketMap)
    {
        return;
    }

    // 在共享内存上创建
}

int addSocket(CBaseSocket* pSocket)
{
    g_pSocketMap.insert(std::make_pair(pSocket->getSocket(), pSocket));
}

int removeSocket(CBaseSocket* pSocket)
{
    g_pSocketMap.erase(pSocket->getSocket());
}

CBaseSocket* findBaseSocket(net_handle_t fd)
{}

/////////////////////////////////////////////////////////////////////

CBaseSocket::CBaseSocket()
{}

~CBaseSocket::CBaseSocket()
{}

int CBaseSocket::createSocket(void)
{
    int iSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (iSockFD <= 0)
    {
        TRACELOG("Create Socket Failed !\n");
        return -1;
    }

    return iSockFD;
}

int CBaseSocket::bindAddress(int iSockFD, const char* pszIP, uint16_t usPort)
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

void CBaseSocket::listenSocket(int iSockFD)
{
    listen(iSockFD, MAX_LISTEN_SOCKET_COUNT);
    return;
}

int CBaseSocket::acceptRequest()
{
    return 0;
}
