#pragma once
#include "KStd.h"
class KTimer : public KSingleton<KTimer>
{
	UINT m_iFPS;
	float m_fSecPerFrame;
	float m_fAccumulation;
	float m_fFrameTime;
	DWORD m_dwFrameCount;
	DWORD m_dwBeforeTick;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	KTimer();
	virtual ~KTimer();
	
public:
	TCHAR m_strBuffer[MAX_PATH];
};

#define I_TIMER KTimer::Get()
