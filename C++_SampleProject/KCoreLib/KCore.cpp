#include "KCore.h"
#include "KObjectMgr.h"
#include "KShaderMgr.h"
#include "KSoundMgr.h"
#include "KTextureMgr.h"

bool	KCore::GameRun()
{
    if (!GameFrame()) return false;
    if (!GameRender()) return false;
    return true;
}
bool	KCore::GameInit()
{
    m_GameTimer.Init();
    KInput::Get().Init();
    if (SUCCEEDED(InitDeivice()))
    {
        I_Shader.Set(m_pd3dDevice);
        I_Texture.Set(m_pd3dDevice);

        if (m_dwWrite.Init())
        {
            IDXGISurface1* pSurface = nullptr;
            HRESULT hr = m_pSwapChain->GetBuffer(0,
                __uuidof(IDXGISurface1),
                (void**)&pSurface);
            if (SUCCEEDED(hr))
            {
                m_dwWrite.SetRenderTarget(pSurface);
            }
            if (pSurface) pSurface->Release();
        }
    }
    Init();
    return true;
}
bool	KCore::GameFrame()
{

    Frame();
    return true;
}
bool	KCore::GameRender()
{
    Render();
    return true;
}
bool	KCore::GameRelease()
{
    Release();
    return true;
}

bool	KCore::Init()
{
    CreateDevice();
    return true;
}
bool	KCore::Frame() {


    return true;
}
bool	KCore::Render() {

        // 백퍼버를 지운다.
        float ClearColor[4] = { 0.0f, 0.6f, 0.0f, 1.0f }; //red,green,blue,alpha
        m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
        m_pSwapChain->Present(0, 0);
        return true;

}
bool	KCore::Release() {
    CleanUpDevice();
    return true;
}
void KCore::ResizeDevice(UINT iWidth, UINT iHeight)
{
}
bool KCore::Run()
{
    GameInit();
    while (1)
    {
        if (!MsgRun())
        {
            break;
        }
        GameRun();
    }
    GameRelease();
    return true;
}