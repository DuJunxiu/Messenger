
#ifndef __LOG_DEAL_HPP__
#define __LOG_DEAL_HPP__

#include <stdio.h>

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
        int initLogFile();

        void OnTick();
        
        int tryWriteLog(const char *pcContent, ...);

        int writeLog(const char *pcContent, va_list& ap);
		
		int writeLogByLevel(int iLevel, const char *pcContent, va_list& ap);

    private:
        // 日志文件是否打开
        void checkLogFile();

    private:
        FILE* m_pFile;                              // 文件指针
        char m_szFileName[MAX_FILE_NAME_LENGTH];    // 文件名

        unsigned int m_uiLastTickTime;              // 上次tick的时间戳
    };

    // 一个日志文件管理类的实例
    typedef CSingleton<CLogFileManager> logManagerSingleton;

    // 无条件强制打印日志
    #define TRACELOG(format, ...) logManagerSingleton::GetInstance()->tryWriteLog(format, ##__VA_ARGS__)

}

#endif