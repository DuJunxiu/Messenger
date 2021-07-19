
#ifndef __EVENTLOOP_HPP__
#define __EVENTLOOP_HPP__

#include "Utility.hpp"

using namespace MyMessenger;

enum
{
    SERVER_NOTHING  = 0,
    SERVER_START    = 1,
    SERVER_STOP     = 2;
};

class CEventLoop
{
public:
    CEventLoop() {}
    ~CEventLoop() {}

public:
    // 初始化
    int initialize();

    // 释放
    int release();

    // 
    int routine();

    // 定时器
    void OnTick();

private:
    static int m_iCommand;

};

#endif