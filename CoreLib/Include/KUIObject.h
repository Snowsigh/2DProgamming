#pragma once
#include "KObject2D.h"
#include "KSoundMgr.h"
struct KStatePlayData
{
	KTexture* pTex;
	KSound* pSound;
	KStatePlayData(const KStatePlayData& _data)
	{
		pTex = _data.pTex;
		pSound = _data.pSound;
		DisplayText("KStatePlayDataCopy\n");
	}
	KStatePlayData()
	{
		DisplayText("KStatePlayData\n");
	}
	KStatePlayData(KTexture* _tex, KSound* _sound)
	{
		pTex = _tex;
		pSound = _sound;
		DisplayText("KStatePlayDataCopy\n");
	}
};
class KUIObject : public KObject2D
{
public:
	std::vector<KStatePlayData> m_pStatePlayList;
	RECT	m_rtOffset;
	RECT	m_rtOffsetTex;
public:
	bool	Frame() override;
	bool	Render()override;
	bool    SetVertexData()override;
	bool    SetIndexData()override;
	KUIObject()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};
class KImageObject : public KUIObject
{
public:
	bool	Init() override;
	bool	Frame() override;
	bool	Render()override;
};
class KButtonObject : public KUIObject
{
public:
	virtual void	HitSelect(KBaseObject* pObj, DWORD dwState) override;
	bool	Init() override;
	bool	Frame() override;
	bool	Render()override;
};

