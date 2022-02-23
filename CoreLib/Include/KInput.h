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
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};
class KInput : public KSingleton<KInput>
{
public:
public:
	DWORD m_dwKeyState[256];
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
	static KInput& Get()
	{
		static KInput theSingle;
		return theSingle;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	DWORD   GetKey(DWORD dwKey);
};

