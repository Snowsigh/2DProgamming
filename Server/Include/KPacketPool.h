#pragma once
#include "KProtocol.h"

class KUser;
struct K_PACKET
{
	UPACKET packet;
	KUser* pUser;
};

class KPacketPool
{
	std::list<K_PACKET> m_PacketPool;
	HANDLE m_hMutex;
public:
	std::list<K_PACKET>& Get();
	void Push(K_PACKET& pack);
	void Lock();
	void UnLock();
public:
	KPacketPool();
	virtual ~KPacketPool();
};

