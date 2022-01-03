#include "KSample.h"
GAME(Octree, 1024, 768)
bool Sample::Init()
{
    
    SetUpCamera(TVector3(0, 0, -30), TVector3(0, 0, 0), 300.0f);
    
    return true;
}

bool Sample::Frame()
{
    return false;
}

bool Sample::Render()
{
    m_kCube.DrawTestBox(0, 0.01, 0.01, 0.01, &m_kCamera.m_matWorld, &m_kCamera.m_matView, &m_kCamera.m_matProj, m_pImmediateContext);
    return false;
}

bool Sample::Release()
{

    m_kCube.Release();
    
    return false;
}
