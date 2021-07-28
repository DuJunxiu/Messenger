
#include "EventDispatch.hpp"
#include "SocketUtility.hpp"

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

void CEventDispatch::dispatchLoop()
{
    fd_set read_set, write_set, excep_set;

    while (true)
    {
        if (0 == m_read_set.fd_count || 0 == m_write_set.fd_count || 0 == m_excep_set.fd_count)
        {
            continue;
        }

        m_lock.lock();
        memcpy(&read_set, &m_read_set, sizeof(fd_set));
        memcpy(&write_set, &m_write_set, sizeof(fd_set));
        memcpy(&excep_set, &m_excep_set, sizeof(fd_set));
        m_lock.unlock();

        int nfds = select(0, &read_set, &write_set, &excep_set, &timeout);
        if (nfds <= 0)
        {
            continue;
        }

        for (uint32_t i = 0; i < read_set.fd_count; i++)
        {
            SOCKET fd = read_set.fd_array[i];
            CBaseSocket* pSocket = FindBaseSocket((net_handle_t)fd);
            if (nullptr != pSocket)
            {
                pSocket->OnRead();
            }
        }
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



