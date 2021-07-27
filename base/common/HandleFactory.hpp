
#ifndef __HANDLE_FACTORY_HPP__
#define __HANDLE_FACTORY_HPP__

#include "Handle.hpp"
using namespace MyMessenger;

class CHandleFactory
{
public:
    CHandleFactory();
    ~CHandleFactory();

public:
    // 为了调用对应的消息处理函数，每一个主协议都需要注册
    static void registerHandle(const unsigned int uiMsgID, const CHandle* pHandle);

    // 接收消息时调用，返回对应 MsgID 的 消息处理对象指针
    static CHandle* getHandle(const unsigned int uiMsgID);

private:
    // 类对象指针数组，便于调用对应主协议的消息处理对象
    static CHandle* m_apHandle[MAX_MSGID_COUNT];

};

#endif
