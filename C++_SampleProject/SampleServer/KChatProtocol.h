#include <Windows.h>

#pragma pack(push, 1)
typedef struct KPACKET_USER_POSITION{
	WORD user_idx; // 유저 인덱스
	WORD posX;
	WORD posY;
	WORD direction;
};

#pragma pack(pop)