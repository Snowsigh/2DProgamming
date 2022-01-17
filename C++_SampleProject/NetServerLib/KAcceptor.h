#pragma once
#include "KThread.h"
class KAcceptor : public KThread
{
public:
	SOCKET m_ListenSock;
public:
	bool Set(int iPort = 10000, const char* address = nullptr);
	virtual bool Run() override;
public:
	KAcceptor();
	virtual ~KAcceptor();
};

