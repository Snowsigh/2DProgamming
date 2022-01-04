#include "KSample.h"
GAME(Octree, 1024, 768)
KBox* Sample::CreateBox(KVector3 _MaxArea, TMatrix* _w, TMatrix* _v, TMatrix* _p)
{
    KBox* newBox = new KBox;
    HRESULT hr = S_OK;
    struct Vertex
    {
        struct {
            float x;
            float y;
            float z;
        }pos;
    };
    const Vertex vertices[] =
    {
        {-1.0f,-1.0f,-1.0f},
        { 1.0f,-1.0f,-1.0f},
        {-1.0f,1.0f,-1.0f},
        { 1.0f,1.0f,-1.0f},
        {-1.0f,-1.0f,1.0f},
        { 1.0f,-1.0f,1.0f},
        {-1.0f,1.0f,1.0f},
        { 1.0f,1.0f,1.0f},
    };
    D3D11_BUFFER_DESC bd;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertices);
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer(&bd, &sd, &newBox->m_pVertexBuffer);
    if (FAILED(hr)) return nullptr;
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;
    //배열이 들어갈수있다.
    //m_pImmediateContext->IASetVertexBuffers(0u, 1u, &m_pVertexBuffer, &stride, &offset);

    const unsigned short indices[] =
    {
       0,2,1, 2,3,1,
       1,3,5, 3,7,5,
       2,6,3, 3,6,7,
       4,5,7, 4,7,6,
       0,4,2, 2,4,6,
       0,1,4, 1,5,4,
    };

    D3D11_BUFFER_DESC ibd = {};
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.ByteWidth = sizeof(indices);
    ibd.StructureByteStride = sizeof(unsigned short);
    D3D11_SUBRESOURCE_DATA isd;
    isd.pSysMem = indices;
    hr = g_pd3dDevice->CreateBuffer(&ibd, &isd, &newBox->m_pIndexBuffer);
    if (FAILED(hr)) return nullptr;

    //m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    float x = _MaxArea.x;
    float y = _MaxArea.y;
    float z = _MaxArea.z;

    //VS 상수 버퍼
    ConstantBuffer cb;
    if (_w == nullptr)
    {
        TMatrix d =
            DirectX::XMMatrixRotationZ(rand()) *
            DirectX::XMMatrixRotationY(rand()) *
            DirectX::XMMatrixTranslation(x, y, z);
        cb.matWorld = d.Transpose();
    }
    if (_v != nullptr)
    {
        cb.matView = _v->Transpose();
    }
    if (_p != nullptr)
    {
        cb.matProj = _p->Transpose();
    }

    D3D11_BUFFER_DESC cbd = {};
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(cb);
    cbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA csd;
    csd.pSysMem = &cb;
    hr = g_pd3dDevice->CreateBuffer(&cbd, &csd, &newBox->m_pConstantBuffer);
    if (FAILED(hr)) return nullptr;
    //pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
    
    return newBox;
}
bool Sample::Init()
{
    
    SetUpCamera(TVector3(0, 0, -30), TVector3(0, 0, 0), 300.0f);
    
    m_kOctree.Init(KVector3(200, 200, 200),m_pImmediateContext);
    
    m_1Box = CreateBox(KVector3(75, 75, 75), &m_kCamera.m_matWorld, &m_kCamera.m_matView, &m_kCamera.m_matProj);
    return true;
}

bool Sample::Frame()
{

    return false; 
}

bool Sample::Render()
{

    m_1Box->SetMatrix(nullptr, &m_kCamera.m_matView, &m_kCamera.m_matProj);
    UINT uStride = 0;
    UINT Offset = 0;

    m_pImmediateContext->UpdateSubresource(m_1Box->m_pConstantBuffer, 0, NULL, &m_1Box->cb, 0, 0);
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_1Box->m_pVertexBuffer, &uStride, &Offset);
    m_pImmediateContext->IASetIndexBuffer(m_1Box->m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_1Box->m_pConstantBuffer);
    
    m_kOctree.SetMatrix(nullptr, &m_kCamera.m_matView, &m_kCamera.m_matProj);
    m_kOctree.Render(m_pImmediateContext);

    

    
    
    return false;
}

bool Sample::Release()
{

    m_kOctree.Release();

    
    delete m_1Box;
    return false;
}
