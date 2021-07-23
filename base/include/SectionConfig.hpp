
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
    void initMapByFile(std::string strFileName);

    std::string getValueByKey(std::string strKey);

private:
    std::unordered_map<std::string, std::string> m_SectionMap;
};

#endif