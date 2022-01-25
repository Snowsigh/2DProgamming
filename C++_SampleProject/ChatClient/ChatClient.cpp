#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include "KPacket.h"
#pragma comment	(lib, "ws2_32.lib")

HANDLE g_hConnectEvent;
HANDLE g_hExecuteSemaphore;
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	// 1번 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	// 2번 패킷 전송 : 운영체제 sendbuffer(short바이트), recvbuffer
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
int SendPacket(SOCKET sock, char* msg, WORD type)
{
	// 1번 패킷 생성
	KPacket tPacket(type);
	tPacket << 999 << "곽근오" << (short)50 << msg;
	KPacket tPacketTest(tPacket);
	KChatMsg recvdata;
	ZeroMemory(&recvdata, sizeof(recvdata));
	tPacketTest >> recvdata.index >> recvdata.chName
		>> recvdata.damage >> recvdata.chMsg;
	char* pData = (char*)&tPacket.m_uPacket;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pData[iSendSize],
			tPacket.m_uPacket.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < tPacket.m_uPacket.ph.len);
	return iSendSize;
}
int RecvPacketHeader(SOCKET sock, UPACKET& recvPacket)
{
	char szRecvBuffer[256] = { 0, };
	//패킷헤더 받기
	ZeroMemory(&recvPacket, sizeof(recvPacket));
	bool bRun = true;
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(sock, szRecvBuffer,
			PACKET_HEADER_SIZE, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(sock);
			std::cout << " 접속종료됨." << std::endl;
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				std::cout << " 비정상 접속종료됨." << std::endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (iRecvSize < PACKET_HEADER_SIZE);
	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
	return 1;
}
int RecvPacketData(SOCKET sock, UPACKET& recvPacket)
{
	// 데이터 받기
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(sock, recvPacket.msg,
			recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(sock);
			std::cout << " 접속종료됨." << std::endl;
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				std::cout << " 비정상 접속종료됨." << std::endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
	return 1;
}

DWORD WINAPI SendThread(LPVOID lpThreadParameter)
{
	SOCKET sock = (SOCKET)lpThreadParameter;
	char szBuffer[256] = { 0, };

	while (1)
	{
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0)
		{
			break;
		}
		ZeroMemory(szBuffer, sizeof(char) * 256);
		fgets(szBuffer, 256, stdin);
		if (strlen(szBuffer) == 0)
		{
			std::cout << "정상 종료됨.." << std::endl;
			break;
		}

		int iSendByte = SendPacket(sock, szBuffer, PACKET_CHAT_MSG);
		if (iSendByte < 0)
		{
			std::cout << "비정상 종료됨.." << std::endl;
			break;
		}
	}
	return 0;
}
DWORD WINAPI RecvThread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	bool bRun = false;
	while (1)
	{
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0)
		{
			break;
		}

		UPACKET packet;
		int iRet = RecvPacketHeader(sock, packet);
		if (iRet < 0) continue;
		if (iRet == 1)
		{
			int iRet = RecvPacketData(sock, packet);
			if (iRet < 0) break;
			if (iRet == 0) continue;
			// 메세지 처리
			KPacket data;
			data.m_uPacket = packet;
			KChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			data >> recvdata.index >> recvdata.chName
				>> recvdata.damage >> recvdata.chMsg;
			std::cout << "\n" <<
				"[" << recvdata.chName << "]"
				<< recvdata.chMsg;
		}
	}
	return 0;
}
void main()
{
	g_hConnectEvent =
		CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hExecuteSemaphore =
		CreateSemaphore(NULL, 3, 3, L"ExecuteA");

	if (WaitForSingleObject(g_hExecuteSemaphore, 0) == WAIT_TIMEOUT)
	{
		CloseHandle(g_hExecuteSemaphore);
		MessageBox(NULL, L"이미 3개의 인스턴스가 실행 중입니다.", L"알림", MB_OK);
		return;
	}

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET,
		SOCK_STREAM, 0); //SOCK_STREAM, SOCK_DGRAM
			 //IPPROTO_TCP,IPPROTO_UDP


	DWORD ThreadId;
	HANDLE hThread = ::CreateThread(
		0,
		0,
		SendThread,
		(LPVOID)sock,
		0,
		&ThreadId
	);
	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread(
		0,
		0,
		RecvThread,// 반환
		(LPVOID)sock,
		0,
		&ThreadIdRecv
	);

	Sleep(1000);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.53");
	int iRet = connect(
		sock,
		(sockaddr*)&sa,
		sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	std::cout << "접속성공!" << std::endl;

	SetEvent(g_hConnectEvent);

	u_long on = 0;
	ioctlsocket(sock, FIONBIO, &on);


	while (1)
	{
		 
		Sleep(1);
	

	}
	std::cout << "접속종료" << std::endl;
	Sleep(1);
	CloseHandle(hThread);
	closesocket(sock);
	WSACleanup();


	CloseHandle(g_hConnectEvent);
}