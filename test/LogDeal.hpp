
#ifndef __LOG_DEAL_HPP__
#define __LOG_DEAL_HPP__

#include <stdio.h>
#include <string.h>

#include "LogDeal.hpp"
#include "TimeUtility.hpp"
#include "Singleton.h"

namespace MyMessenger
{
    const int MAX_DATE_TIME_LENGTH = 32;
    const int MAX_FILE_NAME_LENGTH = 64;
    const char* LOG_PATH = "../../log/";

    class CLogFileManager
    {
    public:
        CLogFileManager() {}
        ~CLogFileManager() {}

    public:
        // 初始化日志文件：创建、命名之类的
        int initLogFile()
        {
            m_uiLastTickTime = 0;
            m_pFile = NULL;
            memset(m_szFileName, 0, sizeof(char) * MAX_FILE_NAME_LENGTH);

            checkLogFile();

            return 0;
        }

        void OnTick()
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
        
        int tryWriteLog(const char *pcContent, ...)
        {
            va_list ap;
            va_start(ap, pcContent);
            writeLog(pcContent, ap);
            va_end(ap);

            return 0;
        }

        int writeLog(const char *pcContent, va_list& ap)
        {
            checkLogFile();

            char szDateString[MAX_DATETIME_LENGTH];
            CTimeUtility::convertUnixTimeToString(CTimeUtility::m_uiTime, szDateString);
            
            fprintf(m_pFile, "[%s] ", szDateString);
            
            vfprintf(m_pFile, pcContent, ap);
            
            fflush(m_pFile);

            return 0;
        }

    private:
        // 日志文件是否打开
        void checkLogFile()
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

    private:
        FILE* m_pFile;                              // 文件指针
        char m_szFileName[MAX_FILE_NAME_LENGTH];    // 文件名

        unsigned int m_uiLastTickTime;              // 上次tick的时间戳
    };

    // 一个日志玩家管理类的单例
    typedef CSingleton<CLogFileManager> logManagerSingleton;

    // 无条件强制打印日志
    #define TRACELOG(format, ...) logManagerSingleton::GetInstance()->tryWriteLog(format, ##__VA_ARGS__)

}

#endif
