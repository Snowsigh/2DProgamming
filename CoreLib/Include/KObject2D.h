#pragma once
#include "KBaseObject.h"
class KObject2D : public KDxObject
{
public:
	RECT				m_rtSource;
	RECT				m_rtDraw;
	KVector4			m_vColor;
public:
	float  m_fAlpha = 0.0f;
	bool   m_bFadeIn = false;
	bool   m_bFadeOut = false;
	virtual void    FadeIn();
	virtual void    FadeOut();
public:
	virtual void		SetRectSouce(RECT rt);
	virtual void		SetRectDraw(RECT rt);
	virtual void		AddPosition(KVector2 vPos);
	virtual void		SetPosition(KVector2 vPos);
	virtual void		UpdateRectDraw(RECT rt);
	// ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	virtual void	Convert(KVector2 center, float fWidth, float fHeight,
		std::vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC ��ȯ
	virtual void	Convert(std::vector<SimpleVertex>& list,
		std::vector<SimpleVertex>& retList);
	virtual void	ConvertIndex(KVector2 center, float fWidth, float fHeight,
		std::vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC ��ȯ
	virtual void	ConvertIndex(std::vector<SimpleVertex>& list,
		std::vector<SimpleVertex>& retList);
public:
	virtual bool		SetVertexData() override;
	virtual bool		SetIndexData() override;
	virtual bool		Frame() override;
};

