#include <Windows.h>

#pragma pack(push, 1)
typedef struct KPACKET_USER_POSITION{
	WORD user_idx; // ���� �ε���
	WORD posX;
	WORD posY;
	WORD direction;
};

#pragma pack(pop)