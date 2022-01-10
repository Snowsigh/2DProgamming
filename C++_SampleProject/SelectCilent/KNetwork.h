#pragma once
#include "KNetUser.h"
class KNetwork
{
public:
	SOCKET m_Sock;
	std::list<KNetUser>userlist;
	KNetUser m_PlayerUser;
public:
	bool InitNetwork();
	bool CloseNetwork();
	bool InitServer(int iporotocol, int iport, const char* ip = nullptr);
	
public:
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendMsg(SOCKET sock, UPACKET& packet);
	int AddUser(SOCKET sock);
	int RecvUser(KNetUser& user);
};

