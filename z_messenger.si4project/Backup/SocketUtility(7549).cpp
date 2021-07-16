
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
{
    m_socket = ERROR_SOCKET;
    m_state = SOCKET_STATE_IDLE;
}

~CBaseSocket::CBaseSocket()
{}

int CBaseSocket::createSocket(void)
{
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket <= 0)
    {
        TRACELOG("Create Socket Failed !\n");
        return -1;
    }

    return m_socket;
}

int CBaseSocket::bindAddress(const char* pszIP, uint16_t usPort)
{
    struct sockaddr_in stSockAddr;
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_addr.s_addr = inet_addr(pszIP);
    stSockAddr.sin_port = ntohs(usPort);

    int iRet = bind(m_socket, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));
    if (iRet < 0)
    {
        TRACELOG("Bind Address Failed IP = %s, Port = %u\n", pszIP, usPort);
    }

    return iRet;
}

int CBaseSocket::listenSocket()
{
    int iRet = listen(m_socket, MAX_LISTEN_SOCKET_COUNT);
    if (iRet < 0)
    {
        TRACELOG("Listen Failed", ...);
        return -1;
    }

    m_state = SOCKET_STATE_LISTENING;

    return 0;
}

int CBaseSocket::acceptRequest()
{
    return 0;
}

