
#include <sys/ipc.h>
#include <sys/sem.h>

#include "SemLock.hpp"

using namespace MyMessenger;

CSemLock::CSemLock()
{
    m_iSemID = 0;
    m_iSemKey = 0;
}

CSemLock::~CSemLock()
{}

int CSemLock::initialize(int iKey)
{
    m_iSemKey = iKey;

    m_iSemID = semget(m_iSemKey, 1, IPC_CREAT | 0666);
}

int CSemLock::lock()
{}

int CSemLock::unlock()
{}


