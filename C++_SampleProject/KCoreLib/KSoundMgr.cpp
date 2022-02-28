#include "KSoundMgr.h"

void KSound::Set(FMOD::System* pSystem, std::wstring name, int iIndex)
{
	m_pSystem = pSystem;
	m_csName = name;
	m_iIndex = iIndex;
}

bool KSound::Init()
{
	return false;
}

bool KSound::Frame()
{
	if (m_pSound == nullptr || m_pChannel == nullptr) return true;

	unsigned int ms = 0;
	unsigned int size = 0;
	m_pSound->getLength(&size, FMOD_TIMEUNIT_MS);
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);

	_stprintf_s(m_szBuffer,
		_T("전체시간[%02d:%02d:%02d]:경과시간[%02d:%02d:%02d]"),
		size / 1000 / 60,
		size / 1000 % 60,
		size / 10 % 60,
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 60);

	return true;
}

bool KSound::Render()
{
	return false;
}

bool KSound::Release()
{
	if (m_pSound)
	{
		m_pSound->release();
		m_pSound = nullptr;
	}
	return true;
}

void KSound::Play(bool bLoop)
{
	bool bPlay = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&bPlay);
	}
	if (bPlay == false)
	{
		// 채널은 플레이 되는 사운드의 제어를 담당.
		FMOD_RESULT	ret = m_pSystem->playSound(
			m_pSound, nullptr, false, &m_pChannel);
		if (ret == FMOD_OK)
		{
			//m_pChannel->setVolume(0.5f);
			if (bLoop)
				m_pChannel->setMode(FMOD_LOOP_NORMAL);
			else
				m_pChannel->setMode(FMOD_LOOP_OFF);
		}
	}
}

void KSound::PlayEffect()
{
	FMOD::Channel* pChannel = nullptr;
	// 채널은 플레이 되는 사운드의 제어를 담당.
	FMOD_RESULT	ret = m_pSystem->playSound(
		m_pSound, nullptr, false, &pChannel);
	if (ret == FMOD_OK)
	{
	}
}

void KSound::Stop()
{
	if (m_pChannel != nullptr)
	{
		m_pChannel->stop();
	}
}

void KSound::Paused()
{
	bool bPlay = false;
	m_pChannel->isPlaying(&bPlay);
	if (bPlay)
	{
		bool paused;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}

void KSound::VolumeUp(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume + fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min(1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}

void KSound::VolumeDown(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume - fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min(1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}

KSound::KSound()
{
}

KSound::~KSound()
{
}

KSound* KSoundMgr::Load(std::string filename)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };

	std::wstring fullpathname = to_mw(filename);
	_tsplitpath_s(fullpathname.c_str(), Dirve, Dir, FileName, FileExt);
	std::wstring name = FileName;
	name += FileExt;

	for (auto data : m_list)
	{
		if (data.second->m_csName == name)
		{
			return data.second;
		}
	}

	KSound* pSound = new KSound;
	FMOD_RESULT ret = m_pSystem->createSound(filename.c_str(),
		FMOD_DEFAULT, 0,
		&pSound->m_pSound);



	if (ret != FMOD_OK)
	{
		return nullptr;
	}
	m_list.insert(make_pair(name, pSound));

	pSound->Set(m_pSystem, name, m_iIndex);
	m_iIndex++;
	return pSound;
}

KSound* KSoundMgr::GetPtr(std::wstring key)
{
	auto iter = m_list.find(key);
	if (iter != m_list.end())
	{
		return (*iter).second;
	}
	return nullptr;
}

bool KSoundMgr::Init()
{
	FMOD_RESULT ret;
	ret = FMOD::System_Create(&m_pSystem);
	ret = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

bool KSoundMgr::Frame()
{
	m_pSystem->update();
	return false;
}

bool KSoundMgr::Render()
{
	return false;
}

bool KSoundMgr::Release()
{
	for (auto data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();

	if (m_pSystem)
	{
		m_pSystem->close();
		m_pSystem->release();
	}
	m_pSystem = nullptr;
	return true;
}

KSoundMgr::~KSoundMgr()
{
	Release();
}
