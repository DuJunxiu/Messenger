
#ifndef __TICK_HPP__
#define __TICK_HPP__

#include <time.h>

using namespace MyMessenger;

class CTick
{
public:
    CTick() {}
    ~CTick() {}

public:
    void OnTick();

private:
    unsigned int m_uiLastTickTime;

};

#endif