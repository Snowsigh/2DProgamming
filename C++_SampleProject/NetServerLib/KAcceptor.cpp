#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "KAcceptor.h"
#include "KServer.h"

bool KAcceptor::Set(int iPort, const char* address)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int iRet = ::bind(m_ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	iRet = listen(m_ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	std::cout << "서버 가동중......." << std::endl;
	u_long on = 1;
	ioctlsocket(m_ListenSock, FIONBIO, &on);

	return true;
}

bool KAcceptor::Run()
{
	KServer* pServer = (KServer*)m_pObject;
	SOCKET sock = m_ListenSock;
	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);
	while (1)
	{
		//DWORD dwID = GetCurrentThreadId();
		//std::cout << dwID << " MainThread" << std::endl;
		SOCKET clientSock = accept(sock,
			(sockaddr*)&clientAddr, &iLen);
		if (clientSock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				std::cout << "ErrorCode=" << iError << std::endl;
				break;
			}
		}
		else
		{
			pServer->AddUser(clientSock, clientAddr);
			std::cout << pServer->m_UserList.size() << " 명 접속중.." << std::endl;
		}
		Sleep(1);
	}
	return 1;
}

KAcceptor::KAcceptor()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
}

KAcceptor::~KAcceptor()
{
	WSACleanup();
}
