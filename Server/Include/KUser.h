#pragma once
#include "KPacketPool.h"
#define USER_BUFFER_SIZE PACKET_HEADER_SIZE+MAX_MSG_SIZE

struct OVERLAPPED2
{
	OVERLAPPED ov;
	int iFlag;

};

class KUser : public KServerObject
{
public:
	long long m_dwPakcetCtrl;
	static SOCKET findSock;
	WSABUF sendBuffer;
	WSABUF recvBuffer;
	HANDLE userEvent;
	bool isCatting;
	bool isConnect;
	DWORD m_dwEndPos;
	DWORD m_dwStartPos;
	DWORD m_dwReadPos;
	DWORD m_dwWritePos;
public:
	std::string name;
	SOCKET sock;
	SOCKADDR_IN clientaddr;
	int m_iRecvByte;
	char m_szRecvBuffer[USER_BUFFER_SIZE];
	char m_szPackStream[MAX_STREAM_SIZE];
	bool operator() (KUser& val) const
	{
		return (findSock == val.sock);
	}
	
public:
	bool Dispatch(DWORD dwTransfer, OVERLAPPED2* ov);
	void Put(char* pBuffer, DWORD dwByte);
	bool WaitForReceive();
public:
	KUser();
	virtual ~KUser();
};

