#include "KLobbyServer.h"
DWORD WINAPI WorkerThread(LPVOID param)
{
	KLobbyServer* pServer = (KLobbyServer*)param;
	DWORD dwTransfer;
	ULONG_PTR KeyValue;
	OVERLAPPED* pOverlapped;
	while (1)
	{
		if (WaitForSingleObject(pServer->m_hKillEvent, 1) == WAIT_OBJECT_0)
		{
			break;
		}
		// 완료 큐에 데이터가 있으면 작업시작
		BOOL bReturn = ::GetQueuedCompletionStatus(
			pServer->g_hIOCP,
			&dwTransfer,
			&KeyValue,
			&pOverlapped, 1);

		KChatUser* pUser = (KChatUser*)KeyValue;
		KOV* pOV = (KOV*)pOverlapped;
		if (bReturn == TRUE && pUser && pOV)
		{
			if (dwTransfer == 0)
			{
				pOV->type == KOV::MODE_EXIT;
				pUser->m_bConnect = false;
				//PostQueuedCompletionStatus();
			}
			else
			{
				pUser->Dispatch(dwTransfer, pOV);
			}
		}
		else
		{
			if (GetLastError() != WAIT_TIMEOUT)
			{
				::SetEvent(pServer->m_hKillEvent);
				break;
			}
		}
	}
	return 1;
}

void KLobbyServer::LoginReq(KPacket& t, KNetUser* user)
{
	KLoginReq login;
	memcpy(&login, t.m_uPacket.msg, sizeof(KLoginReq));
	// DB 승인받고 반환
	KLoginAck ack;
	ack.iResult = 1;
	SendMsg(user,
		PACKET_LOGIN_ACK,
		(char*)&ack,
		sizeof(KLoginAck));
}

void KLobbyServer::ChatMsg(KPacket& t, KNetUser* user)
{
	Broadcast(t);
}

bool KLobbyServer::Init(int iPort)
{
	KServer::Init(iPort);
	g_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
	{
		DWORD id;
		g_hWorkThread[iThread] = ::CreateThread(0, 0,
			WorkerThread,
			this, 0, &id);
	}

	m_fnExecutePacket.insert(std::make_pair(
		PACKET_CHAT_MSG,
		std::bind(&KLobbyServer::ChatMsg, this,
			std::placeholders::_1,
			std::placeholders::_2)));
	return false;
}

bool KLobbyServer::Run()
{

	while (1)
	{
		EnterCriticalSection(&m_cs);
		std::list<XPacket>::iterator iter;
		for (iter = m_packetPool.begin();
			iter != m_packetPool.end();
			iter++)
		{
			XPacket* xp = (XPacket*)&(*iter);
			FuncionIterator iter =
				m_fnExecutePacket.find(xp->packet.m_uPacket.ph.type);
			if (iter != m_fnExecutePacket.end())
			{
				CallFunction call = iter->second;
				call(xp->packet, xp->pUser);
			}
		}
		m_packetPool.clear();

		for (m_UserIter iter = m_UserList.begin();
			iter != m_UserList.end();)
		{
			if ((*iter)->m_bConnect == false)
			{
				DelUser((*iter));
				delete (*iter);
				iter = m_UserList.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		LeaveCriticalSection(&m_cs);
		Sleep(1);
	}
	return true;
}

bool KLobbyServer::Release()
{
	CloseHandle(g_hIOCP);
	KServer::Release();
	return false;
}

bool KLobbyServer::AddUser(SOCKET sock, SOCKADDR_IN clientAddr)
{
	KChatUser* user = new KChatUser;
	user->set(sock, clientAddr, this);
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	EnterCriticalSection(&m_cs);
	m_UserList.push_back(user);
	LeaveCriticalSection(&m_cs);

	::CreateIoCompletionPort((HANDLE)sock, g_hIOCP, (ULONG_PTR)user, 0);
	user->Recv();

	char ip[INET_ADDRSTRLEN];
	std::cout
		<< "ip =" <<
		inet_ntop(AF_INET, &(clientAddr.sin_addr),
			ip, INET_ADDRSTRLEN)
		<< "port =" << ntohs(clientAddr.sin_port)
		<< "  " << std::endl;
	return true;
}
