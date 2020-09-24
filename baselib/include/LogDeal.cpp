
#include <string.h>
#include <stdarg.h>

#include "LogDeal.hpp"
#include "TimeUtility.h"

using namespace MyMessenger;

// 日志命名示例：log_2020_01_01.log

int CLogFileManager::initLogFile()
{
    m_uiLastTickTime = 0;
    m_pFile = NULL;
    memset(m_szFileName, 0, sizeof(char) * MAX_FILE_NAME_LENGTH);

    checkLogFile();

    return 0;
}

void CLogFileManager::checkLogFile()
{
    if (NULL == m_pFile)
    {
        int iYear, iMonth, iDay;
        CTimeUtility::makeTime_ymd(CTimeUtility::m_uiTime, iYear, iMonth, iDay);

        // 正确的文件名
        snprintf(m_szFileName, MAX_FILE_NAME_LENGTH - 1, "log_%04d_%02d_%02d.log", iYear, iMonth, iDay);
        m_szFileName[MAX_FILE_NAME_LENGTH - 1] = '\0';

        m_pFile = fopen(m_szFileName, "a+");
    }

    return;
}

void CLogFileManager::OnTick()
{
    // 跨天换日志文件
    if (CTimeUtility::isSameDay(m_uiLastTickTime, CTimeUtility::m_uiTime))
    {
        if (m_pFile)
        {
            fclose(m_pFile);
            m_pFile = NULL;
        }

        checkLogFile();
    }

    m_uiLastTickTime = CTimeUtility::m_uiTime;
}

int CLogFileManager::tryWriteLog(const char *pcContent, ...)
{
    va_list ap;
    va_start(ap, pcContent);
    writeLog(pcContent, ap);
    va_end(ap);

    return 0;
}

int CLogFileManager::writeLog(const char *pcContent, va_list& ap)
{
    checkLogFile();

    char szDateString[MAX_DATETIME_LENGTH];
    CTimeUtility::convertUnixTimeToString(CTimeUtility::m_uiTime, szDateString);

    fprintf(m_pFile, "[%s] ", szDateString);
    
    vfprintf(m_pFile, pcContent, ap);
    
    fflush(m_pFile);

    return 0;
}
