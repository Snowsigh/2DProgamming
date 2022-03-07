#pragma once
#include <KObject2D.h>
#include <string>
class KAnimationClip
{
private:
	KTexture* m_pTex;
	int m_iMaxFrame;
	int m_iFrame; //현재 프레임
public:
	KAnimationClip(std::wstring _FileName, int _MaxFrame)
	{
		m_pTex = new KTexture[_MaxFrame];
		for (int i = 0; i < _MaxFrame; i++)
		{
			std::wstring name = _FileName;
			name += std::to_wstring(i+1);
			name += L".png";
			I_Texture.Load(name);
			m_pTex[i] = I_Texture.m_list.find(name);
		}
		m_iFrame = 0;
		m_iMaxFrame = _MaxFrame;
	}
	~KAnimationClip()
	{
		if (m_pTex) { delete[] m_pTex; m_pTex = nullptr; }
	}
	int GetFrameMAX() { return m_iMaxFrame; }
	KTexture* GETTex(int _iFrame){return m_pTex[] }
};
class KAnimationData 
{
private:
	KTexture* m_pTex;
	int m_iMaxClip;
	KAnimationClip* m_pActionClip;
	KAnimationClip** m_pClipBuffer;
public:
	KAnimationData(KTexture* _Tex, int _MaxClip) : m_iMaxClip(_MaxClip)
	{
		m_pTex = _Tex;
		m_pActionClip = nullptr;
		m_pClipBuffer = new KAnimationClip * [m_iMaxClip];
	}
	~KAnimationData()
	{
		for (int i = m_iMaxClip - 1; i >= 0; i--)
		{
			if (m_pClipBuffer[i]) { delete m_pClipBuffer[i]; m_pClipBuffer[i] = nullptr; }
		}
		if (m_pClipBuffer) { delete[] m_pClipBuffer; m_pClipBuffer = nullptr; }
	}
	KTexture* GetTex() { return m_pTex;}
	int GetClipMax() { return m_iMaxClip;}
	KAnimationClip* GetCilp(int _num)
	{
		if (_num >= m_iMaxClip) return nullptr;
		return m_pClipBuffer[_num];
	}
};

class KAnimation : public KObject2D
{
private:
	KAnimationClip* m_pActionClip;
	KAnimationData* m_pActionData;
	int m_iFrame;
public:
	KAnimation(KTexture* _Tex, KAnimationData* _Data) 
	{
		m_pActionData = _Data;
		m_pActionClip = m_pActionData->GetCilp(0);
		m_iFrame = 0;
	};
	~KAnimation()
	{
		if (m_pActionData) { delete m_pActionData; m_pActionData = nullptr; }
	}
	bool ChangeAnimation(int _iClip)
	{
		if (_iClip > (m_pActionData->GetClipMax() - 1)) return false;
		m_pActionClip = m_pActionData->GetCilp(_iClip);
		m_iFrame = 0;
		return true;
	}
	void UpdataFrame()
	{
		m_iFrame = (m_iFrame + 1) % m_pActionClip->GetFrameMAX();
		m_pColorTex = m_pActionClip->
	}
};
