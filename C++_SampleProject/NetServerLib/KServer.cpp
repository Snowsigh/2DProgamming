#include "KServer.h"
#include "KIOCP.h"
#include "KUserMgr.h"

bool KServer::Init(int iPort )
{
    CreateThread();
    I_IOCP.Init();
    return m_Accepter.Set(iPort);
}

bool KServer::Start()
{
    I_IOCP.Run();
    return false;
}

bool KServer::Run()
{
	while (m_bStarted)
	{
		m_RecvPool.Lock();
		std::list<K_PACKET>& redvlist = m_RecvPool.Get();
		for (K_PACKET& tPacket : m_RecvPool.Get())
		{
			switch (tPacket.packet.ph.type)
			{
			case  PACKET_DRUP_CS_REQ:
			{
				tPacket.pUser->isCatting = false;
				USER_BASE info;
				info.iIndex = 9;
				memcpy(info.szName, tPacket.pUser->name.c_str(), tPacket.pUser->name.size());
				for (KUser* user : I_USERMGR.m_pUserList)
				{
					if (user->isCatting != true) continue;
					if (user->isConnect != true) continue;
					SendPool(user, PACKET_DRUP_USERS_SC, (char*)&info, sizeof(USER_BASE));
				}
				SendPool(tPacket.pUser, PACKET_DRUP_SC_ACK, nullptr, 0);
			}break;
			case  PACKET_CHAR_MSG:
			{
				USER_CHAT_MSG msg;
				ZeroMemory(&msg, sizeof(USER_CHAT_MSG));
				memcpy(msg.szName, tPacket.pUser->name.c_str(), tPacket.pUser->name.size());
				memcpy(msg.msg, tPacket.packet.msg, tPacket.packet.ph.len - PACKET_HEADER_SIZE);
				memcpy(tPacket.packet.msg, &msg, USER_NAME_SIZE + strlen(msg.msg));
				tPacket.packet.ph.len = PACKET_HEADER_SIZE + USER_NAME_SIZE + strlen(msg.msg);
				Broadcast(tPacket);

				//std::cout << "[" << msg.szName << InterlockedIncrement64(&tPacket.pUser->m_dwPacketCnt) << "]" << msg.msg;
			}break;
			case  PACKET_CHAR_NAME_CS_ACK:
			{
				KUser* pUser = tPacket.pUser;
				USER_NAME_ACK userName;
				memcpy(&userName, tPacket.packet.msg, sizeof(USER_NAME_ACK));
				pUser->name = userName.szName;
				//std::cout << userName.szName << std::endl;
				// 클라이언트 등록 허가
				SendPool(pUser, PACKET_JOIN_SIGNIN_SC, nullptr, 0);
				// 다른 클라이언트 유저 접속 통지
				//PACKET_JOIN_USER_SC+data
				USER_BASE info;
				ZeroMemory(&info, sizeof(USER_BASE));
				info.iIndex = 9;
				memcpy(info.szName, userName.szName, USER_NAME_SIZE);
				for (KUser* user : I_USERMGR.m_pUserList)
				{
					if (user->isCatting != true)continue;
					if (user->isConnect != true) continue;
					SendPool(user, PACKET_JOIN_USER_SC, (char*)&info, sizeof(USER_BASE));
				}
				pUser->isCatting = true;
			}break;
			}
		}
		m_RecvPool.Get().clear();
		m_RecvPool.UnLock();


		m_SendPool.Lock();
		std::list<K_PACKET>& list = m_SendPool.Get();
		for (K_PACKET& tPacket : m_SendPool.Get())
		{
			SendMsg(tPacket.pUser, tPacket.packet);
		}
		m_SendPool.Get().clear();
		m_SendPool.UnLock();

		Sleep(1);
	}
	return true;

}

bool KServer::SendPool(KUser* pUser, int type, char* data, int iSize)
{
	{
		KLock lock(this);
		K_PACKET tPacket;
		tPacket.pUser = pUser;

		ZeroMemory(&tPacket.packet, sizeof(UPACKET));
		tPacket.packet.ph.type = type;
		tPacket.packet.ph.len = PACKET_HEADER_SIZE + iSize;
		if (data != nullptr)
		{
			memcpy(tPacket.packet.msg, data, iSize);
		}
		m_SendPool.Push(tPacket);
	}
	return true;
}

bool KServer::SendPool(K_PACKET& packet)
{
	{
		KLock lock(this);
		m_SendPool.Push(packet);
	}
	return true;
}

bool KServer::SendPool(KUser* pUser, UPACKET& packet)
{
	if (pUser->isConnect == false)
	{
		closesocket(pUser->sock);
		return false;
	}
	int iSendByte = 0;
	pUser->sendBuffer.buf = (char*)&packet;
	pUser->sendBuffer.len = packet.ph.len;
	OVERLAPPED2* pOV = new OVERLAPPED2();
	pOV->iFlag = PACK_SEND;

	DWORD dwSendByte;
	int iRet = WSASend(pUser->sock, &pUser->sendBuffer, 1, &dwSendByte, 0, (LPOVERLAPPED)pOV, NULL);

	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			delete pOV;
			pUser->isConnect = false;
			closesocket(pUser->sock);
			//E_MSG("WaitForReceive");
			return false;
		}
	}
	return true;
}

int KServer::SendMsg(SOCKET sock, UPACKET& packet)
{
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pMsg[iSendSize],
			packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}

bool KServer::SendMsg(KUser* pUser, WORD type, char* data, int iSize)
{
	{
		KLock lock(this);
		K_PACKET tPacket;
		tPacket.pUser = pUser;

		ZeroMemory(&tPacket.packet, sizeof(UPACKET));
		tPacket.packet.ph.type = type;
		tPacket.packet.ph.len = PACKET_HEADER_SIZE + iSize;
		if (data != nullptr)
		{
			memcpy(tPacket.packet.msg, data, iSize);
		}
		m_SendPool.Push(tPacket);
	}
	return true;
}

bool KServer::SendMsg(KUser* pUser, UPACKET& packet)
{
	{
		KLock lock(this);
		K_PACKET tPacket;
		tPacket.pUser = pUser;
		memcpy(&tPacket.packet, &packet, packet.ph.len);
		m_SendPool.Push(tPacket);
	}
	return true;
}

void KServer::Broadcast(K_PACKET& tPacket)
{
	{
		KLock lock(this);
		for (KUser* user : I_USERMGR.m_pUserList)
		{
			if (user->isCatting != true)continue;
			if (user->isConnect != true) continue;
			tPacket.pUser = user;
			m_SendPool.Push(tPacket);
		}
	}
}

void KServer::Broadcast(KPacket& t)
{
	for (KNetUser* senduser : m_UserList)
	{
		int iRet = SendMsg(senduser->m_Sock, t.m_uPacket);
		if (iRet <= 0)
		{
			senduser->m_bConnect = false;
		}
	}
}

KServer::KServer()
{
}

KServer::~KServer()
{
}
