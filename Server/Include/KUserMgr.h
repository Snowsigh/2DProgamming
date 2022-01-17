#pragma once
#include "KUser.h"
class KUserMgr : public KSingleton<KUserMgr>
{
public:
	std::vector<KUser*> m_pUserList;
	HANDLE m_hMutex;
public:
	void AddUser(KUser* pUser);
	void AddUser(SOCKET sock, SOCKADDR_IN clientaddr);
	void DelUser(KUser* pUser);
	void DelUser(SOCKET sock);
	void Run();
public:
	KUserMgr();
	virtual ~KUserMgr();
};

#define I_USERMGR KUserMgr::Get()
