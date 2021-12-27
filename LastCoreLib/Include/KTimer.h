#pragma once
#include "KStd.h"
// 1,실행시간 누적(게임플레이 시간)
// 2,1프레임의 경과 시간
// 3,1초에 실행된 카운터(FPS)
class KTimer
{
public:
	LARGE_INTEGER m_liFrequency;
	LARGE_INTEGER m_liCurrent;
	LARGE_INTEGER m_liFrame;
	int m_iTmpCounter;
	int m_iFPS;
	float m_fSPF;
	float m_fGameTimer;
	TCHAR m_szTimerString[MAX_PATH] = { 0, };
	
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	KTimer();
	virtual ~KTimer();
};

