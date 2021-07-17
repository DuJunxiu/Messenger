
#ifndef __EVENT_DISPATCH_HPP__
#define __EVENT_DISPATCH_HPP__

#include "Config.h"

#define EVENT_MODE_SELECT   1
#define EVENT_MODE_POLL     0
#define EVENT_MODE_EPOLL    0

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

#endif

