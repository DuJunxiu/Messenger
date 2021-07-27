
#ifndef __EVENT_DISPATCH_HPP__
#define __EVENT_DISPATCH_HPP__

#include <sys/select.h>
#include <sys/epoll.h>

#include "Config.h"
#include "Singleton.h"

using namespace MyMessenger;

#define EVENT_MODE_SELECT   1
#define EVENT_MODE_POLL     0
#define EVENT_MODE_EPOLL    0

enum
{
    SOCKET_READ     =   0x1,
    SOCKET_WRITE    =   0x1 << 1,
    SOCKET_EXCEP    =   0x1 << 2,
    SOCKET_ALL      =   0x1 << 3
};

class CEventDispatch
{
public:
    CEventDispatch();
    ~CEventDispatch();

public:
    void AddEvent(net_handle_t fd, uint8_t socket_event);
    void RemoveEvent(net_handle_t fd, uint8_t socket_event);

private:
#ifdef EVENT_MODE_SELECT
    fd_set  m_read_set;
    fd_set  m_write_set;
    fd_set  m_excep_set;
#elif EVENT_MODE_POLL
    int     m_pollfd;
#else
    int     m_epollfd;
#endif
};

// 一个事件调度类的实例
typedef CSingleton<CEventDispatch> EventDispatchSingleton;

#define ADD_EVENT(fd, event) EventDispatchSingleton::GetInstance()->AddEvent(fd, event)
#define REMOVE_EVENT(fd, event) EventDispatchSingleton::GetInstance()->RemoveEvent(fd, event)

#endif

