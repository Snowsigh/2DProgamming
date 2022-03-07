#include "..\KCoreClient\Sample.h"
#include "KSample.h"
GAME(Octree, 1024, 768)
bool Sample::Init()
{
    
    SetUpCamera(TVector3(0, 0, -30), TVector3(0, 0, 0), 300.0f);
    
    m_kOctree.Init(KVector3(200, 200, 200),m_pImmediateContext);
    
    return true;
}

bool Sample::Frame()
{

    return false; 
}

bool Sample::Render()
{
    m_kOctree.SetMatrix(nullptr, &m_kCamera.m_matView, &m_kCamera.m_matProj);
    m_kOctree.Render(m_pImmediateContext);

  
    
    return false;
}

bool Sample::Release()
{

    m_kOctree.Release();

    
    return false;
}
