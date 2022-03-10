#pragma once
#include "KGameWorld.h"
#include "KPlayerObject2D.h"
#include <KCore.h>

class KSample : public KCore
{
public:
	KPlayerObject2D PlayerObj;
	KGameWorld m_GameWorld;


public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;
};

