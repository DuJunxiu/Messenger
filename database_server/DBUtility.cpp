
#include "DBUtility.hpp"

CDBUtility::CDBUtility()
{}

CDBUtility::~CDBUtility()
{}

int CDBUtility::loadConfig(const std::string& strFileName)
{
    CSectionConfig section;
    section.initMapByFile(strFileName);

    int ret = 1;
    ret = section.getValueByKey("host", m_strHost);
    ret = section.getValueByKey("user", m_strUser);
    ret = section.getValueByKey("password", m_strPassword);
    ret = section.getValueByKey("database", m_strDBName);
    ret = section.getValueByKey("ip", m_strDBSvrIP);
    ret = section.getValueByKey("port", m_strDBSvrPort);

    return ret;
}
