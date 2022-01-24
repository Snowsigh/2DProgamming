#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "KAcceptor.h"
#include "KServer.h"

bool KAcceptor::Set(int iPort, const char* address)
{
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	if (address == nullptr)
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		sa.sin_addr.s_addr = inet_addr(address);

	int ret = bind(m_ListenSock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		ERROR_MSG("Server::bind");
		return false;
	}
	ret = listen(m_ListenSock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		ERROR_MSG("Server::listen");
		return false;
	}
	std::cout << "서버 시작!!!" << std::endl;

	int socketType;
	int typeLen = sizeof(socketType);
	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType,
		&typeLen) == SOCKET_ERROR)
	{
		ERROR_MSG("Server::listen");
	}
	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType,
		&typeLen) == SOCKET_ERROR)
	{
		ERROR_MSG("Server::listen");
	}

	CreateThread();
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
