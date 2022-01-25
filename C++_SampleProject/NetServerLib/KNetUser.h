#pragma once
#include "KPacket.h"
#include "KObjectPool.h"
#include "KServerObject.h"
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
class KNetUser : public KServerObject
{
	KServer* m_pServer = nullptr;
public:
	bool m_bConnect = false;
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	std::string m_csName;
	short m_iPort;
	WSABUF		m_wsaRecvBuffer;
	WSABUF		m_wsaSendBuffer;
	char		m_szRecv[256];
	char		m_szSend[256];

	char m_szRecvBuffer[2048];
	int m_iPacketPos;
	int m_iSavePos;
	int m_iReadPos;
	std::list<KPacket> m_pPacketPool;

	int DispatchRead(char* szRecvBuffer, int iRecvByte);
	int Dispatch(DWORD dwTrans, KOV* tov);
	int DispatchRecv(char* szRecvBuffer, int iRecvByte);
	int DispatchSend(DWORD dwTrans);

	void set(SOCKET sock, SOCKADDR_IN addr, KServer* pServer);
	int  Recv();
	int  SendMsg(char* msg, int iSize, WORD type);
	int  SendMsg(UPACKET& packet);
	bool DisConnect();

};

