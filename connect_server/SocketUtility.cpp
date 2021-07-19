
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

int CBaseSocket::listenSocket(void)
{
    int iRet = listen(m_socket, MAX_LISTEN_SOCKET_COUNT);
    if (iRet < 0)
    {
        TRACELOG("Listen Failed", ...);
        return -1;
    }

    m_state = SOCKET_STATE_LISTENING;

    addSocket(this);

    return 0;
}

int CBaseSocket::connectSocket(const char* pszIP, uint16_t usPort)
{
    if (m_socket != ERROR_SOCKET)
    {
        return -1;
    }

    m_remote_ip = to_string(pszIP);
    m_remote_port = usPort;

    struct sockaddr_in stSockAddr;
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_addr.s_addr = inet_addr(pszIP);
    stSockAddr.sin_port = htons(usPort);

    int iRet = connect(m_socket, (sockaddr*)&stSockAddr, sizeof(stSockAddr));
    if (iRet < 0)
    {
        TRACELOG("Listen Failed", ...);
        return -1;
    }

    m_state = SOCKET_STATE_LISTENING;

    addSocket(this);

    return 0;
}

// 接收消息
int CBaseSocket::recvMsg(void* buffer, int length)
{
    return recv(m_socket, (char*)buffer, length, 0);
}

// 发送消息
int CBaseSocket::sendMsg(void* buffer, int length)
{
    if (m_state != SOCKET_STATE_LISTENING)
    {
        return -1;
    }

    return send(m_socket, (char*)buffer, length, 0);
}

// 关闭
void CBaseSocket::closeSocket(void)
{
    close(m_socket);
    removeSocket(this);
}

void CBaseSocket::OnRead()
{
    if (m_state != SOCKET_STATE_LISTENING)
    {
        return;
    }

    net_handle_t fd = 0;
    sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(sockaddr_in);
    char ip_str[64];
    while (fd = accept(m_socket, (sockaddr*)&peer_addr, &addr_len)) > 0)
    {
        CBaseSocket* pSocket = new CBaseSocket;
        uint32_t ip = ntohl(peer_addr.sin_addr.s_addr);
        uint16_t port = ntohs(peer_addr.sin_port);

        snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

        TRACELOG("accept socket fd %d, address %s:%u", fd, ip_str, port);

        pSocket->setSocket(fd);
        pSocket->setState(SOCKET_STATE_CONNECTED);
        pSocket->SetRemoteIP(ip_str);
        pSocket->SetRemotePort(port);

        addSocket(pSocket);

        ADD_EVENT(fd, SOCKET_READ | SOCKET_EXCEP);
    }
}

void CBaseSocket::OnWrite()
{}

void CBaseSocket::OnClose()
{}

