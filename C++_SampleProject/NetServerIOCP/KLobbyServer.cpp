#include "KLobbyServer.h"

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
	return false;
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
