#pragma once
#include <KThread.h>
#include <WS2tcpip.h>
class KUdpSocket : public KThread
{
public:
	SOCKET m_Socket;
	SOCKET m_SendSocket;
	SOCKADDR_IN m_RecvAddr;
	SOCKADDR_IN m_SendAddr;
public:
	bool Init();
	bool Run();
	bool Release();
public:
	KUdpSocket();
	virtual ~KUdpSocket();
};

