#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "KNetUser.h"
#include "KServer.h"
int KNetUser::DispatchRead(char* szRecvBuffer, int iRecvByte)
{
	//p1(m_iPacketPos)  p2(2.1)       pn   (m_ReadPos)
	//2035 ~ 2038 ~ 22  ~ 50  ~  2028 ~ 2038 ~ 2048 
	//0 ~ 5 ~ iRecvByte
	if (m_iSavePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iPacketPos = 0;
		m_iSavePos = m_iReadPos;
	}
	memcpy(&m_szRecvBuffer[m_iSavePos], szRecvBuffer, iRecvByte);
	m_iSavePos += iRecvByte;// 버퍼에 이전에 저장된 위치
	m_iReadPos += iRecvByte; // 패킷시작 위치로부터 받은 바이트

	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		// 패킷 해석 가능
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
		// 적어도 1개의 패킷은 도착했다.
		if (pPacket->ph.len <= m_iReadPos)
		{
			do {
				KPacket tPacket(pPacket->ph.type);
				memcpy(&tPacket.m_uPacket,
					&m_szRecvBuffer[m_iPacketPos],
					pPacket->ph.len);
				m_pPacketPool.push_back(tPacket);

				// 다음패킷 처리
				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len <= m_iReadPos);
		}
	}
	return 1;
}

void KNetUser::set(SOCKET sock, SOCKADDR_IN addr)
{
	m_bConnect = true;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
	m_iPacketPos = 0;
	m_iSavePos = 0;
	m_iReadPos = 0;
	m_Sock = sock;
	m_Addr = addr;
	m_csName = inet_ntoa(addr.sin_addr);
	m_iPort = ntohs(addr.sin_port);
}

int KNetUser::Dispatch(DWORD dwTrans, KOV* tov)
{
	delete tov;
	if (m_bConnect == false)
	{
		return 0;
	}
	if (tov->type == KOV::MODE_RECV)
	{
		if (!DispatchRecv(m_szRecv, dwTrans))
		{
		}
		Recv();
		return 1;
	}
	if (tov->type == KOV::MODE_SEND)
	{
		if (!DispatchSend(dwTrans))
		{
		}
	}
	return 1;
}

int KNetUser::DispatchRecv(char* szRecvBuffer, int iRecvByte)
{
	if (m_iSavePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iPacketPos = 0;
		m_iSavePos = m_iReadPos;
	}
	memcpy(&m_szRecvBuffer[m_iSavePos], szRecvBuffer, iRecvByte);
	m_iSavePos += iRecvByte;// 버퍼에 이전에 저장된 위치
	m_iReadPos += iRecvByte; // 패킷시작 위치로부터 받은 바이트

	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		// 패킷 해석 가능
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
		// 적어도 1개의 패킷은 도착했다.
		if (pPacket->ph.len <= m_iReadPos)
		{
			do {
				KPacket tPacket(pPacket->ph.type);
				memcpy(&tPacket.m_uPacket,
					&m_szRecvBuffer[m_iPacketPos],
					pPacket->ph.len);
				/*if (pPacket->ph.type == PACKET_CHAT_MSG)
				{
					m_packetPool.push_back(tPacket);
				}
				else*/
				{
					XPacket xPacket;
					xPacket.pUser = this;
					xPacket.packet = tPacket;
					m_pServer->m_packetPool.push_back(xPacket);
				}

				// 다음패킷 처리
				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len <= m_iReadPos);
		}
	}
	return 1;
}

int KNetUser::DispatchSend(DWORD dwTrans)
{
	return 0;
}

void KNetUser::set(SOCKET sock, SOCKADDR_IN addr, KServer* pServer)
{
	m_pServer = pServer;
	m_bConnect = true;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
	m_iPacketPos = 0;
	m_iSavePos = 0;
	m_iReadPos = 0;
	m_Sock = sock;
	m_Addr = addr;
	m_csName = inet_ntoa(addr.sin_addr);
	m_iPort = ntohs(addr.sin_port);
}

int KNetUser::Recv()
{
	KOV* ov = new KOV(KOV::MODE_RECV);
	m_wsaRecvBuffer.len = sizeof(char) * 256;
	m_wsaRecvBuffer.buf = m_szRecv;
	DWORD dwRead;
	DWORD lpFlags = 0;
	BOOL ret = WSARecv(m_Sock,
		&m_wsaRecvBuffer,
		1,
		&dwRead,
		&lpFlags,
		(WSAOVERLAPPED*)ov,
		nullptr);
	if (ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}

int KNetUser::SendMsg(char* msg, int iSize, WORD type)
{
	// 비동기 로드	
	UPACKET uPacket;
	uPacket.ph.len = iSize + PACKET_HEADER_SIZE;
	uPacket.ph.type = type;
	memcpy(uPacket.msg, msg, iSize);
	//memcpy(m_szSend, &uPacket, uPacket.ph.len);
	KOV* ov = new KOV(KOV::MODE_SEND);
	m_wsaSendBuffer.len = uPacket.ph.len;
	m_wsaSendBuffer.buf = (char*)&uPacket;

	DWORD dwWrite;
	DWORD lpFlags = 0;
	BOOL ret = WSASend(m_Sock,
		&m_wsaSendBuffer,
		1,
		&dwWrite,
		0,
		(WSAOVERLAPPED*)ov,
		nullptr);
	if (ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}

int KNetUser::SendMsg(UPACKET& packet)
{
	KOV* ov = new KOV(KOV::MODE_SEND);
	m_wsaSendBuffer.len = packet.ph.len;
	m_wsaSendBuffer.buf = (char*)&packet;

	DWORD dwWrite;
	DWORD lpFlags = 0;
	BOOL ret = WSASend(m_Sock,
		&m_wsaSendBuffer,
		1,
		&dwWrite,
		0,
		(WSAOVERLAPPED*)ov,
		nullptr);
	if (ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}

bool KNetUser::DisConnect()
{
	closesocket(m_Sock);
	return true;
}
