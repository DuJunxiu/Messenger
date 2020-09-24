
#include "Tick.hpp"
#include "TimeUtility.h"

void CTick::OnTick()
{
    // 1s一次的定时器
    if (CTimeUtility::m_uiTime - m_uiLastTickTime >= 1)
    {
        m_uiLastTickTime = CTimeUtility::m_uiTime;
        // TODO...
    }

    return;
}
