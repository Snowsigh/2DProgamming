#pragma once
#include <KObject2D.h>
class KEtcObject : public KObject2D
{
public:
	bool Init() override;
	bool Frame() override;
	void HitOverlap(KBaseObject* pObj, DWORD dwState);
	void HitSelect(KBaseObject* pObj, DWORD dwState);
public:
	KEtcObject();
	~KEtcObject();
};

