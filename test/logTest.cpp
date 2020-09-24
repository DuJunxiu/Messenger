
#include <unistd.h>
#include "TimeUtility.h"
#include "LogDeal.hpp"

using namespace MyMessenger;

int main()
{
    CTimeUtility::m_uiTime = time(NULL);
    
    int iTest = 0;
    while (iTest < 10)
    {
        CTimeUtility::m_uiTime = time(NULL);

        TRACELOG("TRACELOG %d test OK !\n", ++iTest);

        sleep(1000);
    }
}
