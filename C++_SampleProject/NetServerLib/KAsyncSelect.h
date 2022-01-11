#pragma once
#include "KNetwork.h"
#define NETWORK_MSG WM_USER+1
class KAsyncSelect : public KNetwork
{
public:
	bool m_bconnect = false;
	
	bool Connect(HWND hWnd, int iprotocol, int iport, const char* ip);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

