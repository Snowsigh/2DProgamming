#pragma once
#include <KServer.h>
#include <WS2tcpip.h>
#include "KChatUser.h"
#define MAX_WORKER_THREAD 3
class KLobbyServer : public KServer
{
public:
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	HANDLE g_hIOCP;
public:
	virtual void LoginReq(KPacket& t, KNetUser* user) override;
	virtual void ChatMsg(KPacket& t, KNetUser* user);
public:
	virtual bool Init(int iPort);
	virtual bool Run();
	virtual bool Release();
	virtual bool AddUser(SOCKET sock, SOCKADDR_IN clientAddr);

};

