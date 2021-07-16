
#include <unistd.h>

#include "LogDeal.hpp"

using namespace MyMessenger;

int main()
{
    unsigned int uiTime = time(nullptr);

    while (uiTime + 60 > time(nullptr))
    {
        TRACELOG("now timestamp is %u\n", time(nullptr));
        sleep(2);
    }
}