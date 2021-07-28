
#include <cstring>

#include "EventLoop.hpp"
#include "EventDispatch.hpp"

const std::string DB_CONFIG_FILE(".conf");

int main(int argc, char* argv[])
{
    DBUtilitySingleton::GetInstance()->loadConfig(DB_CONFIG_FILE);

    if (argc >= 1)
    {
        if (0 == strcmp(argv[0], "reload"))
            DBUtilitySingleton::GetInstance()->loadConfig(strFileName);
        else if (0 == strcmp(argv[0], "start"))
            ;
        else if (0 == strcmp(argv[0], "stop"))
            return 0;
        else if (0 == strcmp(argv[0], "resume"))
            ;
    }

    EventDispatchSingleton::GetInstance()->dispatchLoop();

    return 0;
}
