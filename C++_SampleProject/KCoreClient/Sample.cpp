#include "Sample.h"
#include <string>
GAME(CupHead,1024,768)
void	KSample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void	KSample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
bool	KSample::Init()
{
	I_Sound.Init();

	m_GameWorld.Init();
	m_GameWorld.m_pd3dDevice = m_pd3dDevice;
	m_GameWorld.m_pContext = m_pImmediateContext;
	m_GameWorld.Load(L"intor.txt");


	KWorld::m_pWorld = &m_GameWorld;

	return true;
}
bool	KSample::Frame()
{
	KWorld::m_pWorld->Frame();
	return true;
 }
bool	KSample::Render()
{
	KWorld::m_pWorld->Render();

	/*std::wstring msg = L"FPS:";
	msg += std::to_wstring(I_TIMER.m_iFPS);
	msg += L"  GT:";
	msg += std::to_wstring(I_TIMER.m_fFrameTime);
	m_dwWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 1, 1));*/


	return true;
 }
bool	KSample::Release()
{
	I_Sound.Release();
	m_GameWorld.Release();
	

	return true;
 }