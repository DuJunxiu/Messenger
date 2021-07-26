
#ifndef __EVENT_LOOP_HPP__
#define __EVENT_LOOP_HPP__

#include "Singleton.hpp"
#include "Config.h"
#include "DBUtility.hpp"

using namespace MyMessenger;

class CEventLoop
{
public:
    CEventLoop();
    ~CEventLoop();

public:
    void run(int cmd, const std::string& strFileName);

private:
};

typedef CSingleton<CEventLoop> EventLoopSingleton;

#endif
