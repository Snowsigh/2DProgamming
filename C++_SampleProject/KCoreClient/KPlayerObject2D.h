#pragma once
#include <KObject2D.h>
#include "KAnimationData.h"
class KPlayerObject2D : public KObject2D
{
public:
	KAnimation* PlayerAnimation;
	float AnimTime = 0.0f;
public:
	bool CreatePlayer(KShader* _VS,KShader* _PS, ID3D11Device* _Device, ID3D11DeviceContext* _Context);
	bool ActionTexInit();
	virtual void HitOverlap(KBaseObject* pObj, DWORD dwState);
	bool Frame() override;
	bool Render() override;
	bool Shoot();
	bool Release();
	void AddPositionConvertex(KVector2 vPos);
	void ConvertVertex(std::vector<SimpleVertex>& retList);
public:
	KPlayerObject2D();
	~KPlayerObject2D();
};


#define CHANGECLIP(A) if(PlayerAnimation->GetClip() != PlayerAnimation->GetData()->GetClip(A)){PlayerAnimation->ChangeClip(A);}