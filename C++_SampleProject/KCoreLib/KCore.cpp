#include "KCore.h"
#include "KObjectMgr.h"
#include "KShaderMgr.h"
#include "KSoundMgr.h"
#include "KTextureMgr.h"
#include "KDxState.h"
bool	KCore::GameRun()
{
    if (!GameFrame()) return false;
    if (!GameRender()) return false;
    return true;
}
bool	KCore::GameInit()
{
    m_GameTimer.Init();
    I_INPUT.Init();
    if (SUCCEEDED(InitDeivice()))
    {
        I_Shader.Set(m_pd3dDevice);
        I_Texture.Set(m_pd3dDevice);
        KDxState::SetState(m_pd3dDevice);
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
    m_GameTimer.Frame();
    I_ObjectMgr.Frame();
    I_Sound.Frame();
    m_dwWrite.Frame();
    I_INPUT.Frame();
    
    Frame();
    return true;
}
bool	KCore::GameRender()
{
    // 백퍼버를 지운다.
    float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
    m_pImmediateContext->PSSetSamplers(0, 1, &KDxState::m_pSamplerState);
    m_GameTimer.Render();
    I_INPUT.Render();
    Render();
   // m_dwWrite.Render();
    m_pSwapChain->Present(0,0);
 

    m_pSwapChain->Present(0, 0);
    
    return true;
}
bool	KCore::GameRelease()
{
    Release();
    CleanUpDevice();
    KDxState::Release();
    m_dwWrite.Release();
    m_GameTimer.Release();
    I_INPUT.Release();


    return true;
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

void KCore::ResizeDevice(UINT iWidth, UINT iHeight)
{
    if (m_pd3dDevice == nullptr) return;
    DeleteResizeDevice(iWidth, iHeight);

    m_dwWrite.DeleteDeviceResize();

    KDevice::ResizeDevice(iWidth, iHeight);

    IDXGISurface1* pSurface = nullptr;
    HRESULT hr = m_pSwapChain->GetBuffer(0,
        __uuidof(IDXGISurface1),
        (void**)&pSurface);
    if (SUCCEEDED(hr))
    {
        m_dwWrite.SetRenderTarget(pSurface);
    }
    if (pSurface) pSurface->Release();

    CreateResizeDevice(iWidth, iHeight);
}
