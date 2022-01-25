#pragma once
#include <Windows.h>
#include <string>
#define PACKET_HEADER_SIZE 4
#define MAX_MSG_SIZE 4096

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

enum KPACKET_TYPE
{
	PACKET_VERIFICATION_REQ = 1,
	PACKET_VERIFICATION_ACK,

	PACKET_CHAT_NAME_REQ = 1000, // 대화명 입력요청	
	PACKET_CHAT_NAME_ACK, // 대화명 입력 응답
	PACKET_CHAT_MSG, // 보통 채팅 메세지.
	PACKET_LOGIN_REQ, // 로그인요청
	PACKET_LOGOUT_REQ, // 로그아웃요청
	PACKET_LOGIN_ACK, // 로그인응답
	PACKET_LOGOUT_ACK, // 로그아웃응답
	PACKET_LOGOUT_PLAYER, // 로그아웃 플레이어

	PACKET_CREATE_ACCOUNT_REQ = 2000, // 계정생성요청
	PACKET_DELETE_ACCOUNT_REQ, // 계정삭제요청
	PACKET_CREATE_ACCOUNT_ACK, // 계정생성응답
	PACKET_DELETE_ACCOUNT_ACK, // 계정삭제응답

	PACKET_USER_POSITION = 3000, // 케릭터 위치 이동 시작
	PACKET_STOP_POSITION,// 케릭터 정지
	PACKET_LOBBY_USER_INFO, // 대기방 유저리스트 정보


	PACKET_CREATE_CHARACTER_REQ = 4000, // 케릭터 생성 요청
	PACKET_DELETE_CHARACTER_REQ, // 케릭터 삭제 요청
	PACKET_CREATE_CHARACTER_ACK, // 케릭터 생성 응답
	PACKET_DELETE_CHARACTER_ACK, // 케릭터 삭제 응답

	PACKET_HIT_CHARACTER = 5000, // 케릭터 피격 받음
	PACKET_HIT_NPC, // NPC 피격 받음
	PACKET_ATTACK_CHARACTER, // 케릭터 공격 시작
	PACKET_ATTACK_NPC, // NPC 공격 시작
	PACKET_DEAD_CHARACTER, // 케릭터 죽음
	PACKET_DEAD_NPC, // NPC 죽음
	PACKET_DAMAGE_CHARACTER, // 케릭터 데미지 받음
	PACKET_DAMAGE_NPC, // NPC 데미지 받음
	PACKET_SPAWN_CHARACTER, // 케릭터 스폰
	PACKET_SPAWN_NPC, // NPC 스폰
	PACKET_SPAWN_NPC_LIST, // 
	PACKET_SYNC_CHARACTER, // 케릭터 동기화
	PACKET_SYNC_NPC_LIST, // NPC 동기화	
	PACKET_NPC_TARGETMOVE,  // NPC 타켓이동	


	PACKET_ZONE_ENTRY_REQ = 6000,//게임존 입장 요청
	PACKET_ZONE_ENTRY_ACK, // 게임 존 입장 응답
	PACKET_ZONE_NEW_PLAYER, // 게임 존 입장 케릭터 정보 전송
	PACKET_ZONE_PLAYERS_INFO, // 게임 존에 입장한 유저들의 플레이 케릭터 정보 전송 
	PACKET_ZONE_USER_INFO,// 게임존 유저리스트 정보(플레이어+기타(옵저버 등))
	PACKET_ZONE_TARGET_REQ, // 존 타켓 위치 요청  
	PACKET_ZONE_TARGET_ACK, // 존 타켓 위치 응답
};
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
struct KLoginReq
{
	char szID[20];
	char szPS[20];
};
struct KLoginAck
{
	int iResult;// 1=승인, -1=ID없다. -2=PS없다.
};
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