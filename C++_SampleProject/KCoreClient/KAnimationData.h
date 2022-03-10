#pragma once
#include <KObject2D.h>
#include <string>
class KAnimationClip
{
private:
	KTexture** m_pTex;
	int m_iMaxFrame;
	int m_iFrame; //현재 프레임
public:
	KAnimationClip(std::wstring _FileName, int _MaxFrame)
	{
		m_pTex = new KTexture*[_MaxFrame];
		for (int i = 0; i < _MaxFrame; i++)
		{
			if (_MaxFrame > 9)
			{
				if (i < 9)
				{
					std::wstring name = _FileName;
					name += L"0";
					name += std::to_wstring(i + 1);
					name += L".png";
					m_pTex[i] = I_Texture.Load(name);
				}
				else
				{
					std::wstring name = _FileName;
					name += std::to_wstring(i + 1);
					name += L".png";
					m_pTex[i] = I_Texture.Load(name);
				}
				
			}
			else
			{
				std::wstring name = _FileName;
				name += std::to_wstring(i + 1);
				name += L".png";
				m_pTex[i] = I_Texture.Load(name);
			}
		}
		m_iFrame = 0;
		m_iMaxFrame = _MaxFrame;
	}
	~KAnimationClip()
	{
		if (m_pTex) { delete[] m_pTex; m_pTex = nullptr; }
	}
	int GetFrameMAX() { return m_iMaxFrame; }
	KTexture* GetTex(int _Frame)
	{
		return m_pTex[_Frame];
	}
};
class KAnimationData 
{
private:
	int m_iMaxClip;
	KAnimationClip* m_pClip;
	KAnimationClip** m_pClipBuffer;
public:
	KAnimationData(int _MaxClip) : m_iMaxClip(_MaxClip)
	{
		m_pClip = nullptr;
		m_pClipBuffer = new KAnimationClip*[m_iMaxClip];
	}
	~KAnimationData()
	{
		for (int i = m_iMaxClip - 1; i >= 0; i--)
		{
			if (m_pClipBuffer[i]) { delete m_pClipBuffer[i]; m_pClipBuffer[i] = nullptr; }
			if (m_pClipBuffer) { delete m_pClipBuffer; m_pClipBuffer = nullptr; }
		}
	}
	bool AddClip(int _iClipNumber, KAnimationClip* _Clip)
	{
		if (_iClipNumber >= m_iMaxClip) return false;
		m_pClipBuffer[_iClipNumber] = _Clip;
		return true;
	}
	KAnimationClip*	GetClip(int _Num)
	{
		if (_Num >= m_iMaxClip) return nullptr;
		return m_pClipBuffer[_Num];
	}
	int GetClipMax()
	{
		return m_iMaxClip;
	}

};

class KAnimation
{
private:
	KAnimationData* m_AniData;
	KAnimationClip* m_pClip;
	KTexture* m_pTex;
	int m_iFrame;

public:
	KAnimation(KAnimationData* _Data)
	{
		m_AniData = _Data;
		m_pClip = m_AniData->GetClip(0);
		m_pTex = m_AniData->GetClip(0)->GetTex(0);
		m_iFrame = 0;
		
	}
	~KAnimation()
	{
		if (m_AniData) { delete m_AniData; m_AniData = nullptr; }
	}
	bool ChangeClip(int _iClip)
	{
		if (_iClip > m_AniData->GetClipMax() - 1) return false;
		m_pClip = m_AniData->GetClip(_iClip);
		m_iFrame = 0;
		return true;
	}
	void UpdataFrame()
	{
		m_iFrame = (m_iFrame + 1) % m_pClip->GetFrameMAX();
		m_pTex = m_pClip->GetTex(m_iFrame);
	}

	KAnimationClip*	GetClip()
	{
		return m_pClip;
	}
	KAnimationData* GetData()
	{
		return m_AniData;
	}
};

