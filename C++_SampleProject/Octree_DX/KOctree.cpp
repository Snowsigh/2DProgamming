#include "KOctree.h"
KNode* KOctree::CreateNode(KNode* _pParent, KVector3 _vMin, KVector3 _vMax)
{
	NodeCount++;
	KNode* pNode = new KNode(_vMin, _vMax);
	CreateVectexBuffer(pNode);
	CreateIndexBuffer(pNode);

	pNode->NodeNumber = NodeCount;
	if (_pParent != nullptr)
	{
		pNode->idepth += _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	return pNode;
}
bool KOctree::CheckIn(KNode* _pNode, KCube _vValue)
{
	if ((_pNode->m_Cube.vCtrlPoint.x <= _vValue.vCtrlPoint.x && _pNode->m_Cube.vCtrlPoint.y <= _vValue.vCtrlPoint.y && _pNode->m_Cube.vCtrlPoint.z <= _vValue.vCtrlPoint.z)
		&& (_pNode->m_Cube.vMaxPoint.x >= _vValue.vMaxPoint.x && _pNode->m_Cube.vMaxPoint.y >= _vValue.vMaxPoint.y && _pNode->m_Cube.vMaxPoint.z >= _vValue.vMaxPoint.z))
	{
		return true;
	}
	return false;
}
void KOctree::BuildTree(KNode* _pNode)
{
	if (_pNode->m_Cube.vSize.x >= MINCUBESIZE && _pNode->m_Cube.vSize.y >= MINCUBESIZE && _pNode->m_Cube.vSize.z >= MINCUBESIZE)
	{
		int tmp = m_ChildNode;
		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, _pNode->m_Cube.vCtrlPoint, _pNode->m_Cube.vCenterPoint);
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCtrlPoint.z),
			KVector3(_pNode->m_Cube.vMaxPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCenterPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCtrlPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCenterPoint.z),
			KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vMaxPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCenterPoint.z),
			KVector3(_pNode->m_Cube.vMaxPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vMaxPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCtrlPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCtrlPoint.z),
			KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vMaxPoint.y, _pNode->m_Cube.vCenterPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCtrlPoint.z),
			KVector3(_pNode->m_Cube.vMaxPoint.x, _pNode->m_Cube.vMaxPoint.y, _pNode->m_Cube.vCenterPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCtrlPoint.x, _pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCenterPoint.z),
			KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vMaxPoint.y, _pNode->m_Cube.vMaxPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, _pNode->m_Cube.vCenterPoint, _pNode->m_Cube.vMaxPoint);
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;
	}
}
bool KOctree::CreateVectexBuffer(KNode* _pNode)
{
	KVector3 tmpMin = _pNode->m_Cube.vCtrlPoint; 
	KVector3 tmpMax = _pNode->m_Cube.vMaxPoint;
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
	   {tmpMin.x,tmpMax.y,tmpMax.z},
	   {tmpMin.x,tmpMin.y,tmpMax.z},
	   {tmpMax.x,tmpMin.y,tmpMax.z},
	   {tmpMax.x,tmpMax.y,tmpMax.z},
	   {tmpMin.x,tmpMax.y,tmpMin.z},
	   {tmpMin.x,tmpMin.y,tmpMin.z},
	   {tmpMax.x,tmpMin.y,tmpMin.z},
	   {tmpMax.x,tmpMax.y,tmpMin.z},
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
	hr = g_pd3dDevice->CreateBuffer(&bd, &sd, &_pNode->m_pVertexBuffer);
	if (FAILED(hr)) return false;
	_pNode->uStride = sizeof(Vertex);

	return true;
}
bool KOctree::CreateIndexBuffer(KNode* _pNode)
{
	HRESULT hr;
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
	hr = g_pd3dDevice->CreateBuffer(&ibd, &isd, &_pNode->m_pIndexBuffer);
	if (FAILED(hr)) return false;
	return true;
}
bool KOctree::CreateConstantsBuffer(KNode* _pNode, TMatrix* pWorld, TMatrix* pView, TMatrix* pProj)
{
	HRESULT hr;
	//상수버퍼
	struct ConstantBuffer
	{
		TMatrix  matWorld;
		TMatrix  matView;
		TMatrix  matProj;
	};
	//VS 상수 버퍼
	ConstantBuffer cb;
	if (pWorld == nullptr)
	{
		cb.matWorld = pWorld->Transpose();
	}
	if (pView != nullptr)
	{
		cb.matView = pView->Transpose();
	}
	if (pProj != nullptr)
	{
		cb.matProj = pProj->Transpose();
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
	hr = g_pd3dDevice->CreateBuffer(&cbd, &csd, &_pNode->m_pConstantBuffer);
	if (FAILED(hr)) return false;
	//pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

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
	hr = g_pd3dDevice->CreateBuffer(&cbd2, &csd2, &_pNode->m_pConstantBufferPS);
	if (FAILED(hr)) return false;
	return true;
}
bool KOctree::CreateShaderLayout(ID3D11DeviceContext* pContext)
{
	HRESULT hr;
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

	pContext->IASetInputLayout(m_pVertexLayout);

	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}
bool KOctree::Release()
{
	if(m_pVertexLayout)m_pVertexLayout->Release();
	if(m_pVS)m_pVS->Release();
	if(m_pPS)m_pPS->Release();
	return true;
}