#pragma once
#include "KStd.h"

#pragma pack(push, 1)
typedef struct {
	WORD len;
	WORD type;
}PACKET_HAEDER;

typedef struct {
	PACKET_HAEDER ph;
	char			msg[4096];
}UPACKET, *P_UPACKET;

struct KChatMsg
{
	long index;
	char chName[20];
	short damage;
	char chMsg[256];
};
#pragma pack(pop)

#define PACKET_HEADER_SIZE 4
#define PACKET_CHAT_MSG 1000

