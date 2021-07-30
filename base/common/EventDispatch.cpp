
#include "EventDispatch.hpp"
#include "SocketUtility.hpp"

CEventDispatch::CEventDispatch()
{}

CEventDispatch::~CEventDispatch()
{}

#ifdef 0

void CEventDispatch::AddEvent(net_handle_t fd, uint8_t socket_event)
{
    if (0 != (socket_event | SOCKET_READ))
    {
        FD_SET(fd, &m_read_set);
    }

    if (0 != (socket_event | SOCKET_WRITE))
    {
        FD_SET(fd, &m_write_set);
    }

    if (0 != (socket_event | SOCKET_EXCEP))
    {
        FD_SET(fd, &m_excep_set);
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

// #ifdef _WIN32
//         for (u_int i = 0; i < read_set.fd_count; i++)
//         {
//             SOCKET fd = read_set.fd_array[i];
//             CBaseSocket* pSocket = findBaseSocket((net_handle_t)fd);
//             if (pSocket)
//             {
//                 pSocket->OnRead();
//             }
//         }
// #elif
// #endif
    }
}

#elif 0

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

void CEventDispatch::dispatchLoop()
{
    struct epoll_event events[MAX_EVENT_NUMBER];
    while (true)
    {
        int nfds =  epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        for (int i = 0; i < nfds; i++)
        {
            int sockfd = events[i].data.fd;
            CBaseSocket* pSocket = findBaseSocket((net_handle_t)sockfd);
            if (nullptr == pSocket)
            {
                continue;
            }

            if (events[i].events & EPOLLIN)
            {
                pSocket->OnRead();
            }

            if (events[i].events & EPOLLOUT)
            {
                pSocket->OnWrite();
            }

            if (events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP))
            {
                pSocket->OnClose();
            }
        }
    }
}

#endif

