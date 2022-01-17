#pragma once
#include "KPacketPool.h"
#include "KAcceptor.h"

class KServer : public KSingleton<KServer>, public KThread
{
public:
	KPacketPool m_RecvPool;
	KPacketPool m_SendPool;
	KAcceptor m_Accepter;
public:
	bool Init();
	bool Start();
	bool Run();
	bool SendPool(KUser* pUser, int type, char* data, int iSize);
	bool SendPool(K_PACKET& packet);
	bool SendPool(KUser* pUser, UPACKET& packet);
public:
	bool SendMsg(KUser* pUser, int type, char* data, int iSize);
	bool SendMsg(KUser* pUser, UPACKET& packet);
	void Broadcast(K_PACKET& tPacket);
public:
	KServer();
	virtual ~KServer();
};

#define I_SERVER KServer::Get()