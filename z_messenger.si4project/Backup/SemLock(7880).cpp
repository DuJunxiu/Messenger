
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include "LogDeal.h"
#include "SemLock.hpp"

using namespace MyMessenger;

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

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
    if (m_iSemID < 0)
    {
        TRACELOG("sem init error, semget failed\n");
        return -1;
    }

    semun unsem;

    return 0;
}

int CSemLock::lock()
{}

int CSemLock::unlock()
{}


