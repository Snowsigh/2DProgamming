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

private:
	bool	GameInit();
	bool	GameRun();
	bool	GameFrame();
	bool	GameRender();
	bool	GameRelease();
	
public:
	bool Run();
	virtual bool	Init()
	{
		return true;
	};
	virtual bool	Frame()
	{
		return true;
	};
	virtual bool	Render()
	{
		return true;
	};
	virtual bool	Release()
	{
		return true;
	};

public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
	void			ResizeDevice(UINT iWidth, UINT iHeight);
};

