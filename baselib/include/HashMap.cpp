
#include <new>
#include "HashMap.hpp"

CHashMap* CHashMap::onCreateHashMap(char* pShmAdress, int iCount)
{
    return new(pShmAdress) CHashMap(iCount);
}

CHashMap::CHashMap(int iCount)
{
    m_iCapacity = iCount;
}