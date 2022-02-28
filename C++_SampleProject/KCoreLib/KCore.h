#pragma once
#include "KDevice.h"
#include "KBaseObject.h"
#include "KInput.h"
#include "KTimer.h"
#include "KWriteFont.h"
class KCore : public KDevice
{
public:
	KTimer m_GameTimer;
	KWriteFont m_dwWrite;
	ID3D11SamplerState* m_pSamplerState = nullptr;
private:
	bool	GameInit();
	bool	GameRun();
	bool	GameFrame();
	bool	GameRender();
	bool	GameRelease();

public:
	bool Run();
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
	void			ResizeDevice(UINT iWidth, UINT iHeight);
};

