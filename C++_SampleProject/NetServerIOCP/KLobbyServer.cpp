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
void KLobbyServer::LoginReq(KPacket& t, KUser* user)
{
	KLoginReq login;
	memcpy(&login, t.m_uPacket.msg, sizeof(KLoginReq));
	KLoginAck ack;
	ack.iResult = 1;
	SendMsg(user, KPACKET_TYPE::PACKET_LOGIN_ACK ,(char*)&ack, sizeof(KLoginAck));
}

void KLobbyServer::ChatMsg(KPacket& t, KUser* user)
{
	Broadcast(t);
}

bool KLobbyServer::InitServer(int iPort)
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

	/*m_fnExecutePacket.insert(std::make_pair(
		PACKET_CHAT_MSG,
		std::bind(&KLobbyServer::ChatMsg, this,
			std::placeholders::_1,
			std::placeholders::_2)));*/
}

bool KLobbyServer::Run()
{
	return false;
}

bool KLobbyServer::Release()
{
	return false;
}

bool KLobbyServer::AddUser(SOCKET socr, SOCKADDR_IN clientAddr)
{
	return false;
}
