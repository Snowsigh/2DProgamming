#pragma once
#include <KObject2D.h>
#include "KAnimationData.h"
class KPlayerObject2D : public KObject2D
{
public:
	KAnimationData PlayerAnimation;
	
public:
	bool ActionTexInit();
	virtual void HitOverlap(KBaseObject* pObj, DWORD dwState);
	bool Frame() override;
	bool Render() override;
public:
	KPlayerObject2D();
	~KPlayerObject2D();
};

#define TEXCHACK(A) pTex=PlayerAnimation.A->GetTex(PlayerAnimation.A->GetFrameMAX()-1);