
#ifndef __HASH_MAP__
#define __HASH_MAP__

// 服务器起来的时候就在共享内存上分配好所有节点的空间
// 恢复模式下，根据空间大小寻址
// 如果总节点数改变，只能停机，删共享内存重新分配

const int MAX_HASH_MAP_ARRAY_SIZE = 8;      // 数组的长度
const int MAX_NODE_IN_ONE_LIST_COUNT = 64;  // 链表的长度

template <class T>
struct NodeInfo
{
    T m_stObj;      // 存放的对象
    char m_cStatus; // 是否被使用 0未使用 1已使用
};

// 哈希管理器，主要用来管理存放的对象
class CHashMap
{
public:
    CHashMap();
    ~CHashMap();

    CHashMap(int iCount);

public:
    static CHashMap* onCreateHashMap(char* pShmAdress, int iCount);

public:
    int getHashMapBitSize();

private:
    int m_iCapacity;    // 最大节点数
    int m_iUsedCount;   // 已用节点数
};

#endif
