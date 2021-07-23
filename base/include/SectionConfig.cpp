
#include "SectionConfig.hpp"

CSectionConfig::CSectionConfig()
{}

CSectionConfig::~CSectionConfig()
{}

// 参考自 https://www.cnblogs.com/coolcpp/p/cpp-regex.html
void CSectionConfig::initMapByFile(std::string strFileName)
{
    FILE* fp = fopen(strFileName.c_str(), "r");
    if (NULL == fp)
    {
        return;
    }

    char temp[64] = {0};
    while (fscanf(fp, "%[^\n]", temp) != EOF)
    {
        std::string str(temp);
        std::regex reg("=");
        std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
        decltype(pos) end;
        if (end->length() == 2)
        {
            m_SectionMap.insert(std::make_pair(end->str(), (++end)->str()));
        }

        fgetc(fp);
    }
}

std::string CSectionConfig::getValueByKey(std::string strKey)
{
    auto it = m_SectionMap.find(strKey);
    if (it != m_SectionMap.end())
    {
        return it->second;
    }

    return {};
}