
#include <unistd.h>

#include "LogDeal.hpp"

using namespace MyMessenger;

int main()
{
    unsigned int uiTime = time(NULL);

    while (uiTime + 60 > time(NULL))
    {
        TRACELOG("now timestamp is %u\n", time(NULL));
        sleep(2);
    }
}