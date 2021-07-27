
#include <cstring>

#include "EventLoop.hpp"
#include "EventDispatch.hpp"

const std::string DB_CONFIG_FILE(".conf");

int main(int argc, char* argv[])
{
    DBUtilitySingleton::GetInstance()->loadConfig(DB_CONFIG_FILE);

    int cmd = NOTHING;
    if (argc >= 1)
    {
        if (0 == strcmp(argv[0], "reload"))
            cmd = RELOAD;
        else if (0 == strcmp(argv[0], "start"))
            cmd = START;
        else if (0 == strcmp(argv[0], "stop"))
            cmd = STOP;
        else if (0 == strcmp(argv[0], "resume"))
            cmd = RESUME;
    }

    EventDispatchSingleton::GetInstance()->dispatchLoop();

    return 0;
}
