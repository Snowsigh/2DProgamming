#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "KNetUser.h"
#include "KServer.h"

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
