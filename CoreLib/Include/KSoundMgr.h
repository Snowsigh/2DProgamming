#pragma once
#include "KStd.h"
#include "Include/fmod.hpp"
#include "Include/fmod_errors.h"
#pragma comment(lib,"fmod_vc.lib")
class KSound
{
public:
	int				m_iIndex;
	std::wstring	m_csName;
	FMOD::System* m_pSystem = nullptr;
	FMOD::Sound* m_pSound = nullptr;
	FMOD::Channel* m_pChannel = nullptr;
	float			m_fVolume = 0.5f;
	std::wstring	m_szMsg;
	TCHAR			m_szBuffer[256];
public:
	void	Set(FMOD::System* pSystem, std::wstring name, int iIndex);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	void    Play(bool bLoop = false);
	void    PlayEffect();
	void    Stop();
	void    Paused();
	void    VolumeUp(float fVolume = 0.1f);
	void    VolumeDown(float fVolume = 0.1f);
public:
	KSound();
	~KSound();
};

class KSoundMgr : public KSingleton<KSoundMgr>
{
	int		m_iIndex;
public:
	friend class KSingleton<KSoundMgr>;
	FMOD::System* m_pSystem = nullptr;
	std::map<std::wstring, KSound* >  m_list;
public:
	KSound* Load(std::string filename);
	KSound* GetPtr(std::wstring key);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
private:
	KSoundMgr();
public:
	~KSoundMgr();
};

#define I_Sound KSoundMgr::Get()

