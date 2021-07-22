
#include "TCPConnector.hpp"

CTCPConnector::CTCPConnector()
{}

CTCPConnector::~CTCPConnector()
{}

int CTCPConnector::onRecvData()
{
    pthread_mutex_lock(m_stMutex);

    CBaseSocket* pSocket = findBaseSocket(m_socket);
    ASSERT_AND_LOG_RTN_INT(pSocket);

    char* pcReadData = nullptr;

    // 先尝试接收一下
    int iFreeByte = m_stRecvBuffer.getFreeSize();
    int iRecvByte = pSocket->recvMsg((void*)pcReadData, m_stRecvBuffer.getMaxSize());
    if (iFreeByte < iRecvByte)
    {
        pthread_mutex_unlock(m_stMutex);
        return -1;
    }

    // 接收到的数据放入缓存
    int iRet = m_stRecvBuffer.onWrite((const char*)pcReadData, iRecvByte);

    pthread_mutex_unlock(m_stMutex);

    return iRet;
}

int CTCPConnector::onSendData(const char* pcSendData, int iLength)
{
    pthread_mutex_lock(m_stMutex);

    CBaseSocket* pSocket = findBaseSocket(m_socket);
    ASSERT_AND_LOG_RTN_INT(pSocket);

    int iRet = 0;

    // 先尝试发送滞留数据
    if (!m_stSendBuffer.isEmpty())
    {
        do
        {
            char* pcLastData = nullptr;
            int iLastSize = 0;
            iRet = m_stSendBuffer.onRead(pcLastData, iLastSize);
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
    m_stSendBuffer.onTidy();

    // 没发完，直接放在后面
    if (!m_stSendBuffer.isEmpty())
    {
        iRet = m_stRecvBuffer.onWrite(pcSendData, iLength);
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
                iRet = m_stRecvBuffer.onWrite(pTempData, iTempLen);
            }

            break;
        }

        pTempData += iTempLen；
        iTempLen -= iSendByte;
    } while (iRet >= 0);

    pthread_mutex_unlock(m_stMutex);

    return iRet;
}
