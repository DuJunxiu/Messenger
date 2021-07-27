
#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <string.h>
#include <stdlib.h>

static const int MAX_BUFFER_SIZE = 4096;

// TODO: 缓冲区在共享内存上申请

// 改用malloc 方便扩展
class CBuffer
{
public:
    // 默认构造
    CBuffer()
    {
        m_size = 0;
        m_offset = 0;
        m_pBuffer = nullptr;
    }

    // 构造
    CBuffer(int iMaxBufferSize)
    {
        m_offset = 0;
        m_size = iMaxBufferSize;
        m_pBuffer = (char*)malloc(iMaxBufferSize);
    }

    // 析构
    ~CBuffer()
    {
        m_size = 0;
        m_offset = 0;
        m_pBuffer = nullptr;
    }

    // 写数据
    int onWrite(const char* pReadData, int iLength)
    {
        if (nullptr == m_pBuffer)
        {
            return -1;
        }

        // 先尝试整理下
        onTidy();

        // 超了扩一下
        if (iLength + m_offset > m_size)
        {
            if (m_size >= MAX_BUFFER_SIZE)
            {
                return -1;
            }

            int alloc_size = m_size - m_offset + iLength;
            alloc_size += alloc_size >> 2;  // 额外预留 1/4
            char* pTemp = realloc(m_pBuffer, alloc_size);
            m_size = alloc_size;
            m_pBuffer = pTemp;
        }

        // 缓存进去
        memcpy(&m_pBuffer[m_offset], pReadData, iLength);

        return 0;
    }

    // 读数据
    int onRead(char* pReadData, int& iLength)
    {
        if (nullptr == m_pBuffer)
        {
            return -1;
        }

        onTidy();

        if (m_offset == m_size || 0 == m_offset)
        {
            return -1;
        }

        pReadData = &m_pBuffer[m_offset];
        iLength = m_size - m_offset;

        return 0;
    }

    // 整理
    void onTidy()
    {
        if (0 == m_offset)
        {
            return;
        }

        if (!isEmpty() && m_size > m_offset)
        {
            memmove(&m_pBuffer[0], &m_pBuffer[m_offset], m_size - m_offset);
            m_offset = 0;
        }
        else
        {
            m_offset = 0;
        }
    }

    // 缓冲区是否为空
    bool isEmpty()
    {
        return m_offset == 0;
    }

    int getFreeSize()
    {
        onTidy();
        return m_size - m_offset;
    }

    int getMaxSize()
    {
        return m_size;
    }

    // 缓冲区字节数
    int getSize()
    {
        return m_offset;
    }

    const char* getBuffer()
    {
        return m_pBuffer;
    }

private:
    char* m_pBuffer;        // 指向该缓冲区的指针
    int m_size;             // 缓冲区大小
    int m_offset;           // 偏移量
};

#ifdef 0
class CBuffer
{
public:
    // 默认构造
    CBuffer()
    {
        m_iEndIndex = 0;
        m_iStartIndex = 0;
        m_iMaxBufferSize = MAX_BUFFER_SIZE;
        m_pBuffer = new char[m_iMaxBufferSize];
    }

    // 构造
    CBuffer(int iMaxBufferSize)
    {
        m_iEndIndex = 0;
        m_iStartIndex = 0;
        m_iMaxBufferSize = iMaxBufferSize;
        m_pBuffer = new char[m_iMaxBufferSize];
    }

    // 析构
    ~CBuffer()
    {
        m_iEndIndex = 0;
        m_iStartIndex = 0;
        m_iMaxBufferSize = 0;
        delete[] m_pBuffer;
        m_pBuffer = NULL;
    }

    // 写数据
    int onWrite(const char* pReadData, int iLength)
    {
        if (NULL == m_pBuffer)
        {
            return -1;
        }

        // 先尝试整理下
        onTidy();

        if (iLength + m_iEndIndex > m_iMaxBufferSize)
        {
            return -2;
        }

        // 缓存进去
        memcpy(&m_pBuffer[m_iEndIndex], pReadData, iLength);

        return 0;
    }

    // 读数据
    int onRead(char* pReadData, int& iLength)
    {
        if (NULL == m_pBuffer)
        {
            return -1;
        }

        if (m_iStartIndex == m_iEndIndex || 0 == m_iEndIndex)
        {
            return -1;
        }

        pReadData = &m_pBuffer[m_iStartIndex];
        iLength = m_iEndIndex - m_iStartIndex;

        return 0;
    }

    // 缓冲区是否为空
    bool isEmpty()
    {
        return m_iEndIndex > m_iStartIndex;
    }

    int getFreeSize()
    {
        onTidy();
        return m_iEndIndex - m_iStartIndex;
    }

    int getMaxSize()
    {
        return m_iMaxBufferSize;
    }

    // 整理
    void onTidy()
    {
        if (0 == m_iStartIndex)
        {
            return;
        }

        if (!isEmpty())
        {
            memmove(&m_pBuffer[0], &m_pBuffer[m_iStartIndex], m_iEndIndex - m_iStartIndex);
            m_iEndIndex -= m_iStartIndex;
            m_iStartIndex = 0;
        }
        else
        {
            m_iStartIndex = m_iEndIndex = 0;
        }
    }

private:
    char* m_pBuffer;                    // 指向该缓冲区的指针
    int m_iMaxBufferSize;               // 缓冲区最大大小
    int m_iEndIndex;                    // 末尾元素索引
    int m_iStartIndex;                  // 起始元素索引
};
#endif

#endif
