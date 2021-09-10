
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include "LogDeal.h"
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
    if (m_iSemID < 0)
    {
        TRACELOG("sem init error ! semget failed. key = %d\n", iKey);
        return -1;
    }

    struct semun unSem;
    struct semid_ds stSemDS;
    unSem.buf = &stSemDS;

    if (semctl(m_iSemID, 0, IPC_STAT, unSem) < 0)
    {
        TRACELOG("sem init error ! semctl failed. key = %d\n", iKey);
        return -2;
    }

    return 0;
}

int CSemLock::lock()
{
    if (m_iSemID == 0)
    {
        return -1;
    }

    struct sembuf stBuff;
    stBuff.sem_num = 0;
    stBuff.sem_op = -1;
    stBuff.sem_flg = SEM_UNDO;

}

int CSemLock::unlock()
{}


