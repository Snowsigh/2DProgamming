#pragma once
#include "KUserMgr.h"
#define MAX_WORKER_THREAD 3
class KIOCP : public KSingleton<KIOCP>
{
public:
	HANDLE m_hIOCP;
	HANDLE m_hWorkThread[MAX_WORKER_THREAD];
public:
	bool Init();
	bool Run();
	void SetSocketBind(SOCKET sock, ULONG_PTR key);
public:
	KIOCP();
	virtual ~KIOCP();
	
};

#define I_IOCP KIOCP::Get()

