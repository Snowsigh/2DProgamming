#pragma once
#include "KAcceptor.h"
#include "KNetUser.h"


struct XPacket
{
	KNetUser* pUser;
	KPacket   packet;
};

class KServer : public KThread
{
	KAcceptor m_Accept;
public:
	std::list<KNetUser*> m_UserList;
	std::list<XPacket> m_packetPool;
	typedef std::list<KNetUser*>::iterator m_UserIter;
public:
	using CallFunction = std::function<void(KPacket& t, KNetUser* user)>;
	typedef std::map<int, CallFunction>::iterator FuncionIterator;
	std::map<int, CallFunction> m_fnExecutePacket;
public:
	bool Init(int iPort);

	bool Run();
	bool Release();
public:
	int SendMsg(SOCKET sock, UPACKET& packet);
	bool SendMsg(KNetUser* pUser, WORD type, char* data, int iSize);
	bool SendMsg(KNetUser* pUser, UPACKET& packet);
	int Broadcast(KPacket& t);
	virtual void LoginReq(KPacket& t, KNetUser* user);
public:
	virtual bool AddUser(SOCKET sock, SOCKADDR_IN clientAddr);
	virtual bool DelUser(SOCKET sock);
	virtual bool DelUser(KNetUser* pUser);
	virtual bool DelUser(m_UserIter& iter);
public:
	KServer();
	virtual ~KServer();
};

#define I_SERVER KServer::Get()