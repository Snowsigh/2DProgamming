#pragma once
#include "KDevice.h"
#include "KWindow.h"
#include "KTimer.h"
#include "KInput.h"
#include "KWrite.h"
#include "KCamara.h"
#include "KDxState.h"
#include "KMap.h"
class KCore : public KWindow
{

private:
	bool	GameInit();
	bool	GameRun();
	bool	GameFrame();
	bool	GameRender();
	bool	GameRelease();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)override;
public:
	KTimer m_kTimer;
	KWrite m_kWrite;
	bool		m_bDebugText = false;
public:
		bool SetUpCamera(TVector3 vCameraPos, TVector3 vTargetPos, float vDistance);
		KDebugCamera m_kCamera;
public:
	bool SetWireFrame();
	ID3D11RasterizerState* m_pRsWire;
	ID3D11RasterizerState* m_pRsSolid;
	bool m_bWiremod = false;
public:
	void DebugFrame();
public:
	bool Run();
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
public:
}; 
