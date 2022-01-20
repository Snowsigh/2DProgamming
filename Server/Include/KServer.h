#pragma once
#include "KPacketPool.h"
#include "KAcceptor.h"
#include "KPacket.h"
#include "KNetUser.h"

class KServer : public KSingleton<KServer>, public KThread
{
public:
	std::list<KNetUser*> m_UserList;
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
	int SendMsg(SOCKET sock, UPACKET& packet);
	bool SendMsg(KUser* pUser, WORD type, char* data, int iSize);
	bool SendMsg(KUser* pUser, UPACKET& packet);
	void Broadcast(K_PACKET& tPacket);
	void Broadcast(KPacket& t);
public:
	KServer();
	virtual ~KServer();
};

#define I_SERVER KServer::Get()