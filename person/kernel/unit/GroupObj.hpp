
#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "Protocol.hpp"
#include "ObjHelper.hpp"
#include "LogDeal.hpp"

using namespace MyMessenger;

class CGroupObj : public CObj
{
public:
    virtual int initialize();

public:
    int onGetGroupID() { return m_stGroupInfo.m_iGroupID; }
    int onGetGroupManagerUID() { return m_stGroupInfo.m_iManagerUID; }
    const DBGroupInfo& onGetGroupInfo() { return m_stGroupInfo; }

private:
    DBGroupInfo m_stGroupInfo;

};

#endif
