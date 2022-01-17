#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "KUserMgr.h"
#include "KServer.h"

void KUserMgr::AddUser(KUser* pUser)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	{
		pUser->isConnect = true;
		pUser->userEvent = WSACreateEvent();
		m_pUserList.push_back(pUser);

		USER_NAME_REQ nameReq;
		ZeroMemory(&nameReq, sizeof(USER_NAME_REQ));
		USER_BASE username;
		username.iIndex = 9;
		memcpy(username.szName, "SERVER", sizeof(char) * 7);
		memcpy(nameReq.msg, "환영합니다.", sizeof(char) * 12);
		memcpy(&nameReq.base, &username, sizeof(USER_BASE));

		UPACKET packet;
		packet.ph.len = sizeof(USER_NAME_REQ) + PACKET_HEADER_SIZE;
		packet.ph.type = PACKET_CHAR_NAME_SC_REQ;
		memcpy(packet.msg, &nameReq, sizeof(USER_NAME_REQ));
		I_SERVER.SendPool(pUser, packet);

		pUser->WaitForReceive();

		printf("\n접속[%s][%d]=%I64u",
			inet_ntoa(pUser->clientaddr.sin_addr),
			ntohs(pUser->clientaddr.sin_port),
			m_pUserList.size());
	}
	ReleaseMutex(m_hMutex);
}

void KUserMgr::AddUser(SOCKET sock, SOCKADDR_IN clientaddr)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	{
		KUser* client = new KUser;
		client->sock = sock;
		client->clientaddr = clientaddr;

		m_pUserList.push_back(client);

		printf("\n접속[%s][%d]=%I64u",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port),
			m_pUserList.size());
	}
	ReleaseMutex(m_hMutex);
}

void KUserMgr::DelUser(KUser* pUser)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	{
		std::vector<KUser*>::iterator iter;
		iter = find(m_pUserList.begin(), m_pUserList.end(), pUser);
		if (iter != m_pUserList.end())
		{
			closesocket(pUser->sock);
			printf("\n종료[%s][%d]=%I64u",
				inet_ntoa(pUser->clientaddr.sin_addr),
				ntohs(pUser->clientaddr.sin_port),
				m_pUserList.size());
			delete* iter;
			m_pUserList.erase(iter);
		}
	}
	ReleaseMutex(m_hMutex);
}

void KUserMgr::DelUser(SOCKET sock)
{
	WaitForSingleObject(m_hMutex, INFINITE);
	{
		TCheck<KUser*> check;
		check.m_iSock = sock;
		std::vector<KUser*>::iterator iter;
		iter = find_if(m_pUserList.begin(),
			m_pUserList.end(),
			check);
		if (iter != m_pUserList.end())
		{
			KUser* pUser = (KUser*)*iter;
			/*TUser::findSock = sock;
			iter = find_if( m_UserList.begin(),
							m_UserList.end(),
							TUser());*/
			closesocket(pUser->sock);
			printf("\n종료[%s][%d]=%I64u",
				inet_ntoa(pUser->clientaddr.sin_addr),
				ntohs(pUser->clientaddr.sin_port),
				m_pUserList.size());

			delete* iter;
			m_pUserList.erase(iter);
		}
	}
	ReleaseMutex(m_hMutex);
}

void KUserMgr::Run()
{
}

KUserMgr::KUserMgr()
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
}

KUserMgr::~KUserMgr()
{
	CloseHandle(m_hMutex);
}
