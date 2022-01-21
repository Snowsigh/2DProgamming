#pragma once
#include <KServer.h>
#include "KChatUser.h"
#define MAX_WORKER_THREAD 3
struct KLoginReq
{
	char szID[20];
	char szPS[20];
};
struct KLoginAck
{
	int iResult; // 1 ½ÂÀÎ -1 id, -2 ps
};
class KLobbyServer : public KServer
{
public:
	HANDLE g_hWorkThread[MAX_WORKER_THREAD];
	HANDLE g_hIOCP;
public:
	virtual void LoginReq(KPacket& t, KUser* user);
	virtual void ChatMsg(KPacket& t, KUser* user);

	virtual bool InitServer(int iPort);
	virtual bool Run();
	virtual bool Release();
	virtual bool AddUser(SOCKET socr, SOCKADDR_IN clientAddr);
};

