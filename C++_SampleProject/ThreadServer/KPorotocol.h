#pragma once
#include <Windows.h>
#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)
typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;

typedef struct
{
	PACKET_HEADER ph;
	char msg[4096];
}UPACKET, *P_UPPACKET;
struct KChatMsg
{
	long index;
	char name[20];
	short damage;
	char message[256];

};
#pragma pack(pop)
#define PACKET_CHAT_MSG 1000
