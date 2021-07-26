
#include "TCPConnector.hpp"

typedef std::unorder_map<net_handle_t, CConnector*> ConnectMap;
ConnectMap* g_pConnMap = nullptr;

void initConnectMap()
{
    if (nullptr != g_pConnMap)
    {
        return;
    }

    // 在共享内存上创建
}

int addConnect(CConnector* pConn)
{
    g_pConnMap.insert(std::make_pair(pConn->getSocket(), pConn));
}

int removeConnect(CConnector* pConn)
{
    g_pConnMap.erase(pConn->getSocket());
}

CConnector* findConnect(net_handle_t fd)
{
    CConnector* pConn = nullptr;
    ConnectMap::iterator iter = g_pConnMap.find(fd);
    if (iter != g_pConnMap.end())
    {
        pConn = iter->second;
    }

    return pConn;
}
///////////////////////////////////////////////////////////////////

CConnector::CConnector()
{
    m_socket = 0;
    m_pRecvBuffer = new CBuffer;
    m_pSendBuffer = new CBuffer;
}

CConnector::~CConnector()
{
    delete m_pRecvBuffer;
    delete m_pSendBuffer;
}

int CConnector::onRecvData()
{
    pthread_mutex_lock(m_stMutex);

    CBaseSocket* pSocket = findBaseSocket(m_socket);
    ASSERT_AND_LOG_RTN_INT(pSocket);

    char* pcReadData = nullptr;

    // 先尝试接收一下
    int iFreeByte = m_pRecvBuffer->getFreeSize();
    int iRecvByte = pSocket->recvMsg((void*)pcReadData, m_pRecvBuffer->getMaxSize());
    if (iFreeByte < iRecvByte)
    {
        pthread_mutex_unlock(m_stMutex);
        return -1;
    }

    // 接收到的数据放入缓存
    int iRet = m_pRecvBuffer->onWrite((const char*)pcReadData, iRecvByte);

    pthread_mutex_unlock(m_stMutex);

    return iRet;
}

int CConnector::onSendData(const char* pcSendData, int iLength)
{
    pthread_mutex_lock(m_stMutex);

    CBaseSocket* pSocket = findBaseSocket(m_socket);
    ASSERT_AND_LOG_RTN_INT(pSocket);

    int iRet = 0;

    // 先尝试发送滞留数据
    if (!m_pSendBuffer->isEmpty())
    {
        do
        {
            char* pcLastData = nullptr;
            int iLastSize = 0;
            iRet = m_pSendBuffer->onRead(pcLastData, iLastSize);
            if (iRet < 0)
            {
                break;
            }

            int iSendByte = pSocket->sendMsg((void*)pcLastData, iLastSize);
            if (0 == iSendByte)
            {
                break;
            }

        } while (iRet >= 0);
    }

    // 不管怎样，整理一下
    m_pSendBuffer->onTidy();

    // 没发完，直接放在后面
    if (!m_pSendBuffer->isEmpty())
    {
        iRet = m_pRecvBuffer->onWrite(pcSendData, iLength);
        pthread_mutex_unlock(m_stMutex);
        return iRet;
    }

    // 发完了，就发新的
    char* pTempData = (char*)pcSendData;
    int iTempLen = iLength;
    do
    {
        int iSendByte = pSocket->sendMsg((void*)pTempData, iTempLen, );
        if (iSendByte <= 0)
        {
            // 没发完的数据存入缓存
            if (iTempLen > 0)
            {
                iRet = m_pRecvBuffer->onWrite(pTempData, iTempLen);
            }

            break;
        }

        pTempData += iTempLen；
        iTempLen -= iSendByte;
    } while (iRet >= 0);

    pthread_mutex_unlock(m_stMutex);

    return iRet;
}
