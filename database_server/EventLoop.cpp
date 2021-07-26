
#include "EventLoop.hpp"

CEventLoop::CEventLoop()
{}

CEventLoop::~CEventLoop()
{}

void CEventLoop::run(int cmd, const std::string& strFileName)
{
    while (true)
    {
        if (RELOAD == cmd)
        {
            DBUtilitySingleton::GetInstance()->loadConfig(strFileName);
            cmd = NOTHING;
        }
        else if (STOP == cmd)
        {
            break;
        }
    }
}
