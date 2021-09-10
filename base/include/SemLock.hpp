
#ifndef __SEM_LOCK_HPP__
#define __SEM_LOCK_HPP__

/*
int semctl(int semid, int semnum, int cmd, union semun arg);

GETALL：获得 semid 所表示的信号量集中信号量的个数，并将该值存放在无符号短整型数组 array 中。
GETNCNT：获得 semid 所表示的信号量集中的等待给定信号量锁的进程数目，即 semid_ds 结构中 sem.semncnt 的值。
GETPID：获得 semid 所表示的信号量集中最后一个使用 semop 函数的进程 ID，即 semid_ds 结构中的 sem.sempid 的值。
GETVAL：获得 semid 所表示的信号量集中 semunm 所指定信号量的值。
GETZCNT：获得 semid 所表示的信号量集中的等待信号量成为 0 的进程数目，即 semid_ds 结构中的 sem.semncnt 的值。
IPC_RMID：删除该信号量。
IPC_SET：按参数 arg.buf 指向的结构中的值设置该信号量对应的 semid_ds 结构。只有有效用户 ID 和信号量的所有者 ID 或创建者 ID 相同的用户进程，以及超级用户进程可以执行这一操作。
IPC_STAT：获得该信号量的 semid_ds 结构，保存在 arg.buf 指向的缓冲区。
SETALL：以 arg.array 中的值设置 semid 所表示的信号量集中信号量的个数。
SETVAL：设置 semid 所表示的信号量集中 semnum 所指定信号量的值。
*/

/*
struct sembuf
{
    short sem_num;      // 要操作的信号量在信号量集里的编号
    short sem_op;       // 表示所要执行的操作
    short sem_flag;     // 操作标记 IPC_NOWAIT 和 SEM_UNDO
};

struct ipc_perm
{
    uid_t    uid;     // 拥有者的有效用户id
    gid_t    gid;     // 拥有者的有效组id
    uid_t    cuid;    // 创建者的有效用户id
    gid_t    cgid;    // 创建者的有效组id
    mode_t   mode;    // 访问模式
    ...
};

struct semid_ds
{
    struct ipc_perm sem_perm;   // 对应于该信号量集的 ipc_perm 结构
    struct sem *sem_base;       // sem 结构指针，指向信号量集中第一个信号量的 sem 结构
    ushort sem_nsems;           // 信号量集中信号量的个数
    time_t sem_otime;           // 最近一次调用 semop 函数的时间
    time_t sem_ctime;           // 最近一次改变该信号量集的时间
};

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;  // cmd == SETALL 或 cmd = GETALL
};
*/

namespace MyMessenger
{
    class CSemLock
    {
    public:
        CSemLock();
        ~CSemLock();

    public:
        int initialize(int iKey);
        int lock();
        int unlock();

    private:
        int m_iSemID;
        int m_iSemKey;
    };
}

#endif

