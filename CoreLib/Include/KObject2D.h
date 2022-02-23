#pragma once
#include "KBaseObject.h"
class KObject2D : public KDxObject
{
public:
	RECT				m_rtSource;
	RECT				m_rtDraw;
public:
	virtual void		SetRectSouce(RECT rt);
	virtual void		SetRectDraw(RECT rt);
	virtual void		AddPosition(KVector2 vPos);
	virtual void		SetPosition(KVector2 vPos);
	virtual void		UpdateRectDraw(RECT rt);
	// 화면좌표 위치를 중점으로 NDC 변환
	virtual void	Convert(
		KVector2 center, float fWidth, float fHeight,
		std::vector<SimpleVertex>& retList);
	// 화면좌표계를 NDC 변환
	virtual void	Convert(std::vector<SimpleVertex>& list,
		std::vector<SimpleVertex>& retList);
public:
	virtual bool		SetVertexData() override;
};

