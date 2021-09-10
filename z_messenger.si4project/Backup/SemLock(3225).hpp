
#ifndef __SEM_LOCK_HPP__
#define __SEM_LOCK_HPP__

namespace MyMessenger
{
    class CSemLock
    {
    public:
        CSemLock();
        ~CSemLock();

    public:

    private:
        int m_iSemID;
        int m_iSemKey;
    };
}

#endif

