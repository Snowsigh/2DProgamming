#pragma once
#include <KObject2D.h>
#include "KAnimationData.h"
class KNpcObject2D : public KObject2D
{
public:
	KAnimation* m_kAnimation;
	float AnimTime = 0.0f;
public:
	bool ActionTexInit();
	virtual void HitOverlap(KBaseObject* pObj, DWORD dwState);
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Logic();
	bool Release();
};

#define CHANGECLIP(A) if(m_kAnimation->GetClip() != m_kAnimation->GetData()->GetClip(A)){m_kAnimation->ChangeClip(A);}