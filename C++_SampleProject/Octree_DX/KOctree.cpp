#include "KOctree.h"
void KOctree::Init(KVector3 _Max,ID3D11DeviceContext* pContext)
{

	m_pRootNode = CreateNode(nullptr, KVector3(0, 0, 0), _Max);
	if (m_pRootNode == nullptr)
		 return;
	CreateConstantsBuffer();
	CreateShaderLayout(pContext);
	BuildTree(m_pRootNode);
}
KNode* KOctree::CreateNode(KNode* _pParent, KVector3 _vMin, KVector3 _vMax)
{
	NodeCount++;
	KNode* pNode = new KNode(_vMin, _vMax);
	CreateVectexBuffer(pNode);
	CreateIndexBuffer(pNode);
	if (_pParent != nullptr)
	{
		pNode->idepth = _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	pNode->NodeNumber = NodeCount;
	if (_pParent != nullptr)
	{
		pNode->idepth += _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	return pNode;
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

KNode* KOctree::CheckIn(KNode* _pNode, KCube* _vValue)
{
	KNode* tmpNode = _pNode;
	if ((_pNode->m_Cube.vCtrlPoint.x <= _vValue->vCtrlPoint.x && _pNode->m_Cube.vCtrlPoint.y <= _vValue->vCtrlPoint.y && _pNode->m_Cube.vCtrlPoint.z <= _vValue->vCtrlPoint.z)
		&& (_pNode->m_Cube.vMaxPoint.x >= _vValue->vMaxPoint.x && _pNode->m_Cube.vMaxPoint.y >= _vValue->vMaxPoint.y && _pNode->m_Cube.vMaxPoint.z >= _vValue->vMaxPoint.z))
	{
		for (int iChild = 0; iChild < MAXCHILD; iChild++)
		{
			if (_pNode->m_pChild[iChild] != nullptr)
			tmpNode = CheckIn(_pNode->m_pChild[iChild], _vValue);
		}
		
	}
	else
	{
		tmpNode = _pNode->m_pParent;
	}
	return tmpNode;
}
bool KOctree::ObjectCheak(KCube* _Object)
{
	
	KNode* TargetNode = CheckIn(m_pRootNode, _Object);
	if (TargetNode == nullptr) return false;
	
	for (int iObject = 0; iObject < TargetNode->m_ObejctList.size(); iObject++)
	{
		if (TargetNode->m_ObejctList[iObject] == _Object)
		{
			return false;
		}
	}
	TargetNode->m_ObejctList.push_back(_Object);
	return true;


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
	   {tmpMin.x,tmpMax.y,tmpMax.z}, // 0
	   {tmpMin.x,tmpMin.y,tmpMax.z}, // 1
	   {tmpMax.x,tmpMin.y,tmpMax.z}, // 2
	   {tmpMax.x,tmpMax.y,tmpMax.z}, // 3
	   {tmpMin.x,tmpMax.y,tmpMin.z}, // 4
	   {tmpMin.x,tmpMin.y,tmpMin.z}, // 5
	   {tmpMax.x,tmpMin.y,tmpMin.z}, // 6
	   {tmpMax.x,tmpMax.y,tmpMin.z}, // 7
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
	   0,1,2, 0,2,3, // ¿·¸é
	   0,3,7, 0,7,4, // À­¸é
	   3,2,6, 3,6,7, // ¿·¸é
	   7,6,5, 7,5,4, // ¿·¸é
	   4,5,1, 4,1,0, // ¿·¸é
	   2,1,5, 2,5,6, // ¹Ø¸é
	};
	_pNode->m_uIndexSize = sizeof(indices);
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = _pNode->m_uIndexSize;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd;
	isd.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&ibd, &isd, &_pNode->m_pIndexBuffer);
	if (FAILED(hr)) return false;
	return true;
}
bool KOctree::CreateConstantsBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(KBData);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	D3D11_SUBRESOURCE_DATA csd;
	ZeroMemory(&csd, sizeof(D3D11_SUBRESOURCE_DATA));
	csd.pSysMem = &m_kbData;
	hr = g_pd3dDevice->CreateBuffer(&cbd, &csd, &m_pConstantBuffer);
	if (FAILED(hr)) return false;
	//pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	//PS »ó¼ö¹öÆÛ
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
	ZeroMemory(&cbd2, sizeof(D3D11_BUFFER_DESC));
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.ByteWidth = sizeof(cb2);
	D3D11_SUBRESOURCE_DATA csd2;
	ZeroMemory(&csd2, sizeof(D3D11_SUBRESOURCE_DATA));
	csd2.pSysMem = &cb2;
	hr = g_pd3dDevice->CreateBuffer(&cbd2, &csd2, &m_pConstantBufferPS);
	if (FAILED(hr)) return false;
	return true;
}
bool KOctree::SetMatrix(TMatrix* _w, TMatrix* _v, TMatrix* _p)
{
	if (_w != nullptr)
	{
		m_kbData.matWorld = _w->Transpose();
	}
	if (_v != nullptr)
	{
		m_kbData.matView = _v->Transpose();
	}
	if (_p != nullptr)
	{
		m_kbData.matProj = _p->Transpose();
	}
	return true;
}
bool KOctree::CreateShaderLayout(ID3D11DeviceContext* pContext)
{
	HRESULT hr;
	ID3DBlob* m_pVSBlob = nullptr;
	ID3DBlob* m_pPSBlob = nullptr;
	ID3DBlob* error = nullptr;

	//1. ÇÈ¼¿ ¼ÎÀÌ´õ »ý¼º
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

	//2. ¹ÙÀÎµå ÇÈ¼¿ ¼ÎÀÌ´õ
	

	//3. ¹öÅØ½º ¼ÎÀÌ´õ »ý¼º

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

	//4. ¹ÙÀÎµå ¹öÅØ½º ¼ÎÀÌ´õ
	

	//5. Input ¹öÅØ½º ·¹ÀÌ¾Æ¿ô (2D À§Ä¡¸¸)

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

	

	return true;
}


bool KOctree::DrawNode(KNode* _pNode, ID3D11DeviceContext* pContext)
{
	const UINT tmpStride = _pNode->uStride;
	const UINT tmpOffset = 0;
	pContext->IASetVertexBuffers(0, 1, &_pNode->m_pVertexBuffer, &tmpStride, &tmpOffset);
	pContext->IASetIndexBuffer(_pNode->m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	for (int iChild = 0; iChild < MAXCHILD; iChild++)
	{
		if (_pNode->m_pChild[iChild] != nullptr)
		{
			DrawNode(_pNode->m_pChild[iChild], pContext);
		}
	}
	pContext->DrawIndexed(_pNode->m_uIndexSize, 0, 0);
	return true;
}
void KOctree::Render(ID3D11DeviceContext* pContext)
{
	pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_kbData, 0, 0);
	pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pContext->PSSetConstantBuffers(0, 1, &m_pConstantBufferPS);
	pContext->PSSetShader(m_pPS, nullptr, 0);
	pContext->VSSetShader(m_pVS, nullptr, 0);
	pContext->IASetInputLayout(m_pVertexLayout);
	pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DrawNode(m_pRootNode, pContext);
}

bool KOctree::Release()
{
	DeleteNode(m_pRootNode);

	if(m_pVertexLayout)m_pVertexLayout->Release();
	if(m_pVS)m_pVS->Release();
	if(m_pPS)m_pPS->Release();
	if (m_pConstantBuffer)m_pConstantBuffer->Release();
	if (m_pConstantBufferPS)m_pConstantBufferPS->Release();


	return true;
}
KNode* KOctree::DeleteNode(KNode* _pNode)
{
	for (int iChild = 0; iChild < MAXCHILD; iChild++)
	{
		if (_pNode->m_pChild[iChild] != nullptr)
			DeleteNode(_pNode->m_pChild[iChild]);
	}
	delete _pNode;
	_pNode = nullptr;
	return nullptr;
}


