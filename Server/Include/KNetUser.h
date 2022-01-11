#pragma once
#include "KPacket.h"
class KNetUser
{
public:
	bool m_bConnect = false;
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	std::string m_csName;
	short m_iPort;

	char m_szRecvBuffer[2048];
	int m_iPacketPos;
	int m_iSavePos;
	int m_iReadPos;
	std::list<KPacket> m_packetPool;
	int DispatchRead(char* szRecvBuffer, int iRecvByte);
	void set(SOCKET sock, SOCKADDR_IN addr);
};

