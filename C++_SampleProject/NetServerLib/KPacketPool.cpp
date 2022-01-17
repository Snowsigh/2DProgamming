#include "KPacketPool.h"
//#include "KUserMgr.h"
std::list<K_PACKET>& KPacketPool::Get()
{

    return m_PacketPool;
}

void KPacketPool::Push(K_PACKET& pack)
{
    Lock();
    Get().push_back(pack); // m_PacketPool.push_back(pack);
    UnLock();
}

void KPacketPool::Lock()
{
    WaitForSingleObject(m_hMutex, INFINITE);
}

void KPacketPool::UnLock()
{
    ReleaseMutex(m_hMutex);
}

KPacketPool::KPacketPool()
{
    m_hMutex = CreateMutex(NULL, FALSE, NULL);
}

KPacketPool::~KPacketPool()
{
    CloseHandle(m_hMutex);
}
