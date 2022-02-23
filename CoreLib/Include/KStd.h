#pragma once
#include <winsock2.h>
#include <windows.h>
#include <d3d11.h>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <iostream>
#include <assert.h>
#include "KCollsion.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "DirectXTK.lib")

extern RECT		g_rtClient;
extern HWND		g_hWnd;
extern float	g_fSecPerFrame;
extern float	g_fGameTimer;
extern POINT	g_ptMouse;

#define GAMEINIT int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int  nCmdShow)
#define GAMERUN(WindowName, Width, Height) {KSample g_Sample;g_Sample.InitWindow(hInstance,nCmdShow,	L#WindowName, Width, Height);g_Sample.Run();}
#define GAME(WindowName, Width, Height) GAMEINIT GAMERUN(WindowName, Width, Height)

template<class T> class KSingleton
{
public:
	static T& Get()
	{
		static T Instance;
		return Instance;
	}
};