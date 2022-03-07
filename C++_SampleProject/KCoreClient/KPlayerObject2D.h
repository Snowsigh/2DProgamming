#pragma once
#include <KObject2D.h>
class KPlayerObject2D : public KObject2D
{
public:
	
public:
	bool ActionTexInit();
	virtual void HitOverlap(KBaseObject* pObj, DWORD dwState);
	bool Frame() override;
public:
	KPlayerObject2D();
	~KPlayerObject2D();
};

