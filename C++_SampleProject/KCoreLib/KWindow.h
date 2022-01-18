#pragma once
#include "KStd.h"
class KWindow
{
public:
	RECT m_rtWindow;
	RECT m_rtClient;
	UINT m_iWindowWidth;		// Ŭ���̾�Ʈ ���� ����ũ��
	UINT m_iWindowHeight;	// Ŭ���̾�Ʈ ���� ����ũ��
	UINT m_iWindowX;
	UINT m_iWindowY;

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

