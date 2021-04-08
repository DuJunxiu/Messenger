
#ifndef __HANDLER_FACTORY_HPP__
#define __HANDLER_FACTORY_HPP__

#include "Handler.hpp"
using namespace MyMessenger;

class CHandlerFactory
{
public:
    CHandlerFactory();
    ~CHandlerFactory();

public:
    // 为了调用对应的消息处理函数，每一个主协议都需要注册
    void registerHandler(const unsigned int uiMsgID, const CHandler* pHandler);

    // 接收消息时调用，返回对应 MsgID 的 消息处理对象指针
    CHandler* getHandler(const unsigned int uiMsgID);

private:
    // 类对象指针数组，便于调用对应主协议的消息处理对象
    static CHandler* m_apHandler[MAX_MSGID_COUNT];

};

#endif
