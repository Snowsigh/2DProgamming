#pragma once
#include "KPacket.h"
#include "KObjectPool.h"
class KServer;
// 비동기 작업이 완료 시점까지 OVERLAPPED 유지되어 있어야 된다.
struct KOV : public KObjectPool<KOV>
{
	enum { MODE_RECV = 1, MODE_SEND = 2, MODE_EXIT };
	OVERLAPPED ov;
	int  type;
	KOV(int packetType)
	{
		ZeroMemory(&ov, sizeof(OVERLAPPED));
		type = packetType;
	}
	KOV()
	{
		ZeroMemory(&ov, sizeof(OVERLAPPED));
		type = MODE_RECV;
	}
};
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

