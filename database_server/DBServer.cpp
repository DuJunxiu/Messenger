
#include "DBUtility.hpp"

const std::string DB_CONFIG_FILE(".conf");

int main(int argc, char* argv[])
{
    DBUtilitySingleton::GetInstance()->loadConfig(DB_CONFIG_FILE);

    return 0;
}
