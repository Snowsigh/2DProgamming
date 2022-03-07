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
#include <tchar.h>
#include <atlconv.h>
#include <dxgidebug.h>
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

static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};

template<class T> class KSingleton
{
public:
	static T& Get()
	{
		static T Instance;
		return Instance;
	}
};
static void DisplayText(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char buf[1024 + 256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	OutputDebugStringA((char*)buf);
	va_end(arg);
}
static void MemoryReporting()
{
#if defined(DEBUG) | defined(_DEBUG)
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));
	IDXGIDebug* debug;
	GetDebugInterface(IID_PPV_ARGS(&debug));
	OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_ALL);
	OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");
	debug->Release();
#endif
}