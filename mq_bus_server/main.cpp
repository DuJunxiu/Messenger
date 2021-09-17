
#include <stdio.h>
#include <unistd.h>

#include "mq_bus.hpp"
#include "SharedMemory.hpp"

using namespace MyMessenger;

int main(int argc, char* argv[])
{
    MQBusSingleton::GetInstance()->initialize();

    return 0;
}

