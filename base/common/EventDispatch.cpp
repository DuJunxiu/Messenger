
#include "EventDispatch.hpp"

CEventDispatch::CEventDispatch()
{}

CEventDispatch::~CEventDispatch()
{}

#ifdef EVENT_MODE_SELECT

void CEventDispatch::AddEvent(net_handle_t fd, uint8_t socket_event)
{
    if (0 != (socket_event | SOCKET_READ))
    {
        FD_SET(fd, m_read_set);
    }

    if (0 != (socket_event | SOCKET_WRITE))
    {
        FD_SET(fd, m_write_set);
    }

    if (0 != (socket_event | SOCKET_EXCEP))
    {
        FD_SET(fd, m_excep_set);
    }
}

void CEventDispatch::RemoveEvent(net_handle_t fd, uint8_t socket_event)
{
    if (0 != (socket_event & SOCKET_READ))
    {
        FD_CLR(fd, &m_read_set);
    }

    if (0 != (socket_event & SOCKET_WRITE))
    {
        FD_CLR(fd, &m_write_set);
    }

    if (0 != (socket_event & SOCKET_EXCEP))
    {
        FD_CLR(fd, &m_excep_set);
    }
}

#elif EVENT_MODE_POLL

void CEventDispatch::AddEvent(net_handle_t fd, uint8_t socket_event)
{}

void CEventDispatch::RemoveEvent(net_handle_t fd, uint8_t socket_event)
{}

#else

void CEventDispatch::AddEvent(net_handle_t fd, uint8_t socket_event)
{
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLPRI | EPOLLERR | EPOLLHUP;
    event.data.fd = fd;
    if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &event) != 0)
    {
        TRACELOG("epoll_ctl() failed, errno = %d", errno);
    }
}

void CEventDispatch::RemoveEvent(net_handle_t fd, uint8_t socket_event)
{
    if (epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL) != 0)
    {
        TRACELOG("epoll_ctl failed, errno = %d", errno);
    }
}

#endif



