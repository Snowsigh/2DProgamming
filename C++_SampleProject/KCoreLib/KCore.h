#pragma once
#include "KDevice.h"
#include "KBaseObject.h"
#include "KInput.h"
#include "KTimer.h"
class KCore : public KDevice
{

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
};

