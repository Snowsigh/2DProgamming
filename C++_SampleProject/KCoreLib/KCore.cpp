#include "KCore.h"



bool	KCore::GameRun()
{
    if (!GameFrame()) return false;
    if (!GameRender()) return false;
    return true;
}
bool	KCore::GameInit()
{
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
        float ClearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
        m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
        m_pSwapChain->Present(0, 0);
        return true;

}
bool	KCore::Release() {
    CleanUpDevice();
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