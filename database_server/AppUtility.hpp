
#ifndef __APP_UTILITY_HPP__
#define __APP_UTILITY_HPP__

#include <string>

#include "../base/include/Config.h"
#include "../base/include/SectionConfig.hpp"

class CAppUtility
{
public:
    CAppUtility();
    ~CAppUtility();

public:
    static int loadConfig(std::string strFileName);

private:

private:
    std::string m_strHost;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDBName;
    std::string m_strDBSvrIP;
    uint16_t    m_usDBSvrPort;
};

#endif