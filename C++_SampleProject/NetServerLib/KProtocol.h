#pragma once
#include "KStd.h"
#define PACKET_HEADER_SIZE 4
#define MAX_MSG_SIZE 4096
#pragma pack(push, 1)
typedef struct {
	WORD len;
	WORD type;
}PACKET_HAEDER;

typedef struct {
	PACKET_HAEDER ph;
	char	msg[MAX_MSG_SIZE];
}UPACKET, *P_UPACKET;

struct KChatMsg
{
	long index;
	char chName[20];
	short damage;
	char chMsg[256];
};


#define PACKET_CHAT_MSG 1000
#define PACK_RECV 1000
#define PACK_SEND 2000
#define PACK_END  3000
#define MAX_STREAM_SIZE 4096*5

#define PACKET_CHAR_MSG			 1000 // DATA
#define PACKET_CHAR_NAME_SC_REQ  1001 // DATA
#define PACKET_CHAR_NAME_CS_ACK  1002 // DATA
#define PACKET_JOIN_SIGNIN_SC	 1003 // x
#define PACKET_JOIN_USER_SC		 1004 // DATA
#define PACKET_DRUP_CS_REQ		 1005 // x
#define PACKET_DRUP_SC_ACK		 1006 // x
#define PACKET_DRUP_USERS_SC	 1007 // DATA


// SIZE
#define USER_BASE_SIZE 24
#define USER_NAME_SIZE 20
#define USER_NAME_REQ_MSG_SIZE 30

typedef struct {
	int   iIndex;
	char  szName[USER_NAME_SIZE];
}USER_BASE;
typedef struct {
	int   iIndex;
	char  szName[USER_NAME_SIZE];
}USER_NAME_ACK;

typedef struct {
	USER_BASE base;
	char  msg[USER_NAME_REQ_MSG_SIZE];
}USER_NAME_REQ;
typedef struct {
	char  szName[USER_NAME_SIZE];
	char  msg[MAX_MSG_SIZE - USER_NAME_SIZE];// 메세지 실제 크기
}USER_CHAT_MSG;

#pragma pack(pop)