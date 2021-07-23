
#ifndef __SECTION_CONFIG_HPP__
#define __SECTION_CONFIG_HPP__

#include <cstdio>
#include <string>
#include <regex>
#include <unordered_map>

class CSectionConfig
{
public:
    CSectionConfig();
    ~CSectionConfig();

public:
    void initMapByFile(const std::string& strFileName);

    int getValueByKey(const std::string& strKey, std::string& strPara);

private:
    std::unordered_map<std::string, std::string> m_SectionMap;
};

#endif