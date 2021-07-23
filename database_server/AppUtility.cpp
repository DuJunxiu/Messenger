
#include "AppUtility.hpp"

CAppUtility::CAppUtility()
{}

CAppUtility::~CAppUtility()
{}

int CAppUtility::loadConfig(std::string strFileName)
{
    CSectionConfig section;
    section.initMapByFile(strFileName);
}
