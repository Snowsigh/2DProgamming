#include "KSample.h"
GAME(Octree, 1024, 768)
bool Sample::Init()
{
    SetUpCamera(TVector3(0, 0, -30), TVector3(0, 0, 0), 300.0f);

    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    m_pd3dDevice->CreateRasterizerState(&rd, &m_pRsWire);


    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_BACK;
    m_pd3dDevice->CreateRasterizerState(&rd, &m_pRsSolid);

    return true;

}

bool Sample::Frame()
{
   
    return false;
}

bool Sample::Render()
{
    return false;
}

bool Sample::Release()
{
    IFRELEASE(m_pRsWire)
    IFRELEASE(m_pRsSolid)
    return false;
}
