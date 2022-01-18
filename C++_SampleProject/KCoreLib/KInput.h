#pragma once
#include "KStd.h"
struct KInputState
{
	DWORD dwKeyW;
	DWORD dwKeyA;
	DWORD dwKeyS;
	DWORD dwKeyD;
	DWORD dwKeySP;
};

enum KeyState
{
	KET_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class KInput : public KSingleton<KInput>
{
public:

};

