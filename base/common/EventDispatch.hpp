
#ifndef __EVENT_DISPATCH_HPP__
#define __EVENT_DISPATCH_HPP__

#ifdef _WIN32
#include <WinSock2.h>
#elif
// #include <sys/select.h>
// #include <poll.h>
#include <sys/epoll.h>
#endif

#include <string.h>

#include "Utility.hpp"
#include "Config.h"
#include "Singleton.h"

using namespace MyMessenger;

#define MAX_EVENT_NUMBER 1024

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

public:
    void dispatchLoop();

private:
    CLock m_lock;

// // select
//     fd_set  m_read_set;
//     fd_set  m_write_set;
//     fd_set  m_excep_set;

// // poll
//     int     m_pollfd;

// epoll
    int     m_epollfd;
#endif
};

// 一个事件调度类的实例
typedef CSingleton<CEventDispatch> EventDispatchSingleton;

#define ADD_EVENT(fd, event) EventDispatchSingleton::GetInstance()->AddEvent(fd, event)
#define REMOVE_EVENT(fd, event) EventDispatchSingleton::GetInstance()->RemoveEvent(fd, event)

#endif

