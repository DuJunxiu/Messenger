
#ifndef __TIME_UTILITY_H__
#define __TIME_UTILITY_H__

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

namespace MyMessenger
{
    class CTimeUtility
    {
    public:
        // 获取当前时间戳
        static time_t getNowTime() { return time(NULL); }

        // 时间戳转时间字符串
        static int convertUnixTimeToString(time_t uiTime, char* szString)
        {
            if(NULL == szString)
            {
                return -1;
            }

            szString[0] = '\0';

            struct tm stTempTm;
            struct tm *pTempTm = localtime_r(&uiTime, &stTempTm);

            if(NULL == pTempTm)
            {
                return -2;
            }

            sprintf(szString, "%04d-%02d-%02d %02d:%02d:%02d",
                pTempTm->tm_year + 1900, pTempTm->tm_mon + 1, pTempTm->tm_mday,
                pTempTm->tm_hour, pTempTm->tm_min, pTempTm->tm_sec);

            return 0;
        }

        // 时间戳转年月日
        static int makeTime_ymd(time_t uiTime, int& riYear, int& riMonth, int& riDay)
        {
            riYear = 0;
            riMonth = 0;
            riDay = 0;

            struct tm stTime;
            localtime_r(&uiTime, &stTime);

            riYear = stTime.tm_year + 1900;
            riMonth = stTime.tm_mon;
            riDay = stTime.tm_mday;

            return 0;
        }

        // 比较两个时间戳是否为同一天
        static bool isSameDay(time_t uiTime1, time_t uiTime2)
        {
            struct tm stTime1;
            localtime_r(&uiTime1, &stTime1);

            struct tm stTime2;
            localtime_r(&uiTime2, &stTime2);

            if (stTime1.tm_year != stTime2.tm_year)
            {
                return false;
            }

            if (stTime1.tm_mon != stTime2.tm_mon)
            {
                return false;
            }

            if (stTime1.tm_mday != stTime2.tm_mday)
            {
                return false;
            }

            return true;
        }

    public:
        static time_t m_uiTime;
    };

    time_t CTimeUtility::m_uiTime = 0;
}

#endif