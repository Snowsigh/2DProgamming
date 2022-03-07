#pragma once
#include <KWorld.h>
#include <KInput.h>
#include <KShaderMgr.h>
#include <KUIObject.h>
#include "KPlayerObject2D.h"
class KGameWorld : public KWorld
{
public:
	KSound* m_pBGSound;
	KTexture* m_pBG;
	KWorld* m_pNextWorld;


	KPlayerObject2D PlayerObj;


public:
	bool CreateModelType();
	bool Load(std::wstring file) override;
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

};

