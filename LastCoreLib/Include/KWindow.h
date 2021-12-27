#pragma once
#include"KDevice.h"

class KWindow : public KDevice
{
public:
	RECT m_rtWindow;
	RECT m_rtClient;

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	bool m_bGameRun;
public:
	bool InitWindow(HINSTANCE hInstance, int nCmdShow, const WCHAR* strWindowTitle, int iWidth, int iHeight);
	LRESULT WndMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	 virtual LRESULT  MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	bool MsgRun();

public:
	KWindow(void);
	virtual ~KWindow(void);

};

