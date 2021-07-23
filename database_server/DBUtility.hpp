
#ifndef __DB_UTILITY_HPP__
#define __DB_UTILITY_HPP__

#include <string>

#include "Config.h"
#include "SectionConfig.hpp"
#include "LogDeal.hpp"

using namespace MyMessenger;

class CDBUtility
{
public:
    CDBUtility();
    ~CDBUtility();

public:
    int loadConfig(std::string strFileName);

private:

private:
    std::string m_strHost;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDBName;
    std::string m_strDBSvrIP;
    std::string m_strDBSvrPort;
};

typedef CSingleton<CDBUtility> DBUtilitySingleton;

#endif