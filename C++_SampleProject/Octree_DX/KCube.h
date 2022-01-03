#pragma once
#include <map>
#include <queue>
#include <vector>
#include <KDevice.h>
class KCubes
{
public:
    ID3D11Buffer* m_pVertexBuffer = nullptr;
    ID3D11Buffer* m_pIndexBuffer = nullptr;
    ID3D11Buffer* m_pConstantBuffer = nullptr;
    ID3D11Buffer* m_pConstantBuffer2 = nullptr;
    ID3D11InputLayout* m_pVertexLayout = nullptr;
    ID3D11VertexShader* m_pVS = nullptr;
    ID3D11PixelShader* m_pPS = nullptr;
public:

    bool DrawTestBox(float angle, float x, float y, float z, TMatrix* w, TMatrix* v, TMatrix* p, ID3D11DeviceContext* pContext)
    {

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
           {100.0f,100.0f,100.0f},
           { 200.0f,100.0f,100.0f},
           {100.0f,200.0f,100.0f},
           { 200.0f,200.0f,100.0f},
           {100.0f,100.0f,200.0f},
           { 200.0f,100.0f,200.0f},
           {100.0f,200.0f,200.0f},
           { 200.0f,200.0f,200.0f},
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
        hr = g_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
        if (FAILED(hr)) return false;
        const UINT stride = sizeof(Vertex);
        const UINT offset = 0u;
        //배열이 들어갈수있다.
        pContext->IASetVertexBuffers(0u, 1u, &m_pVertexBuffer, &stride, &offset);

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
        hr = g_pd3dDevice->CreateBuffer(&ibd, &isd, &m_pIndexBuffer);
        if (FAILED(hr)) return false;

        pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

        //상수버퍼
        struct ConstantBuffer
        {
            TMatrix  matWorld;
            TMatrix  matView;
            TMatrix  matProj;
        };
        //VS 상수 버퍼
        ConstantBuffer cb;
        if (w == nullptr)
        {
            TMatrix d =
               DirectX::XMMatrixRotationZ(angle) *
               DirectX::XMMatrixRotationY(angle) *
               DirectX::XMMatrixTranslation(x, y, z);
            cb.matWorld = d.Transpose();
        }
        if (v != nullptr)
        {
            cb.matView = v->Transpose();
        }
        if (p != nullptr)
        {
            cb.matProj = p->Transpose();
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
        hr = g_pd3dDevice->CreateBuffer(&cbd, &csd, &m_pConstantBuffer);
        if (FAILED(hr)) return false;
        //pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
        pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

        //PS 상수버퍼
        struct ConstantBuffer2
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            }face_colors[6];
        };
        const ConstantBuffer2 cb2 =
        {
           {
              {0.5f,1.0f,0.0f},
              {0.0f,0.5f,1.0f},
              {1.0f,0.0f,0.5f},
              {0.5f,0.5f,1.0f},
              {0.5f,1.0f,0.5f},
              {1.0f,0.5f,0.5f},
           }
        };

        D3D11_BUFFER_DESC cbd2 = {};
        cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbd2.Usage = D3D11_USAGE_DYNAMIC;
        cbd2.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
        cbd2.MiscFlags = 0u;
        cbd2.ByteWidth = sizeof(cb2);
        cbd2.StructureByteStride = 0;
        D3D11_SUBRESOURCE_DATA csd2;
        csd2.pSysMem = &cb2;
        hr = g_pd3dDevice->CreateBuffer(&cbd2, &csd2, &m_pConstantBuffer2);
        if (FAILED(hr)) return false;
        pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer2);

        ID3DBlob* m_pVSBlob = nullptr;
        ID3DBlob* m_pPSBlob = nullptr;
        ID3DBlob* error = nullptr;

        //1. 픽셀 셰이더 생성
        hr = D3DCompileFromFile(
            L"PixelShader.txt",
            nullptr,
            nullptr,
            "PixelS",
            "ps_5_0",
            0,
            0,
            &m_pPSBlob,
            &error);
        if (FAILED(hr)) return false;
        hr = g_pd3dDevice->CreatePixelShader(m_pPSBlob->GetBufferPointer(),
            m_pPSBlob->GetBufferSize(), nullptr, &m_pPS);
        if (FAILED(hr)) return false;

        //2. 바인드 픽셀 셰이더
        pContext->PSSetShader(m_pPS, nullptr, 0);

        //3. 버텍스 셰이더 생성

        hr = D3DCompileFromFile(
            L"VertexS.txt",
            nullptr,
            nullptr,
            "VertexS",
            "vs_5_0",
            0,
            0,
            &m_pVSBlob,
            &error);
        if (FAILED(hr)) return false;
        hr = g_pd3dDevice->CreateVertexShader(m_pVSBlob->GetBufferPointer(),
            m_pVSBlob->GetBufferSize(), nullptr, &m_pVS);
        if (FAILED(hr)) return false;

        //4. 바인드 버텍스 셰이더
        pContext->VSSetShader(m_pVS, nullptr, 0);

        //5. Input 버텍스 레이아웃 (2D 위치만)

        const D3D11_INPUT_ELEMENT_DESC layout[] =
        {
           {"POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
           {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA, 0}
        };
        hr = g_pd3dDevice->CreateInputLayout(layout, _countof(layout),
            m_pVSBlob->GetBufferPointer(),
            m_pVSBlob->GetBufferSize(),
            &m_pVertexLayout
        );
        if (FAILED(hr)) return false;

        m_pPSBlob->Release();
        m_pVSBlob->Release();
        if (error)error->Release();

        //6. 바인드 버텍스 레이아웃
        pContext->IASetInputLayout(m_pVertexLayout);

        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        pContext->DrawIndexed((UINT)(std::size(indices)), 0, 0);

        return true;
    };
    bool Release()
    {
        if (m_pVertexBuffer) m_pVertexBuffer->Release();
        if (m_pIndexBuffer) m_pIndexBuffer->Release();
        if (m_pConstantBuffer)m_pConstantBuffer->Release();
        if (m_pConstantBuffer2)m_pConstantBuffer2->Release();
        if (m_pVertexLayout) m_pVertexLayout->Release();
        if (m_pVS) m_pVS->Release();
        if (m_pPS) m_pPS->Release();


        return true;
    }
};

