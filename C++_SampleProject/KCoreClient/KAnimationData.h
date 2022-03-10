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
				if (i < 10)
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
public:
	int m_iMaxClip;
	KAnimationClip* IDleClip;
	KAnimationClip* RunClip;
	KAnimationClip* TurnClip;
	KAnimationClip* JumpClip;
	KAnimationClip* ShootClip;
	KAnimationClip* RunShootClip;
	KAnimationClip* DashClip;
	KAnimationClip** m_pClipBuffer;
public:
	KAnimationData()
	{

	}
	~KAnimationData()
	{

	}

};

class KAnimation
{
private:
	KAnimationData* m_AniData;
	KAnimationClip* m_pClip;
	KTexture* m_pTex;
	int m_iFrame;


	void UpdataFrame()
	{
		m_iFrame = (m_iFrame + 1) % m_pClip->GetFrameMAX();
		m_pTex = m_pClip->GetTex(m_iFrame);
	}
};

