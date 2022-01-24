#include "KServer.h"
void KServer::LoginReq(KPacket& t, KNetUser* user)
{
	
}
bool KServer::Init(int iPort )
{
	m_fnExecutePacket[PACKET_LOGIN_REQ] =
		std::bind(&KServer::LoginReq, this,
			std::placeholders::_1,
			std::placeholders::_2);

	m_Accept.Set(iPort);
	m_Accept.CreateThread(this);
	m_Accept.Detach();
	return true;
}

bool KServer::Run()
{
	m_Accept.Run();
	return true;

}

bool KServer::Release()
{
	KObjectPool<KNetUser>::AllFree();
	KObjectPool<KOV>::AllFree();
	return false;
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

bool KServer::SendMsg(KNetUser* pUser, WORD type, char* data, int iSize)
{
	pUser->SendMsg(data, iSize, type);
	return true;
}

bool KServer::SendMsg(KNetUser* pUser, UPACKET& packet)
{
	pUser->SendMsg(packet);
	return true;
}

int KServer::BroadcastUserPacketPool(KNetUser* user)
{
	if (user->m_pPacketPool.size() > 0)
	{
		std::list<KPacket>::iterator iter;
		for (iter = user->m_pPacketPool.begin();
			iter != user->m_pPacketPool.end(); )
		{
			for (KNetUser* senduser : m_UserList)
			{
				int iRet = SendMsg(senduser->m_Sock, (*iter).m_uPacket);
				if (iRet <= 0)
				{
					senduser->m_bConnect = false;
				}
			}
			iter = user->m_pPacketPool.erase(iter);
		}
	}
	return 1;
}

bool KServer::AddUser(SOCKET sock, SOCKADDR_IN clientAddr)
{
	return true;
}

bool KServer::DelUser(SOCKET sock)
{
	return false;
}

bool KServer::DelUser(KNetUser* pUser)
{
	pUser->DisConnect();
	return false;
}

bool KServer::DelUser(m_UserIter& iter)
{
	DelUser((KNetUser*)*iter);
	return false;
}

int KServer::Broadcast(KPacket& t)
{
	for (KNetUser* senduser : m_UserList)
	{
		int iRet = SendMsg(senduser->m_Sock, t.m_uPacket);
		if (iRet <= 0)
		{
			senduser->m_bConnect = false;
		}
	}
	return 1;
}

KServer::KServer()
{
}

KServer::~KServer()
{
}
