#include "KOctree.h"
void KOctree::Init(KVector3 _vMaxCube)
{

	m_pRootNode = CreateNode(nullptr, KVector3(0, 0, 0), _vMaxCube);
	BuildTree(m_pRootNode);
}

KNode* KOctree::CreateNode(KNode* _pParent, KVector3 _vMin, KVector3 _vMax)
{
	NodeCount++;
	KNode* pNode = new KNode(_vMin, _vMax);
	CreatevertexList(pNode, _vMin, _vMax);
	pNode->NodeNumber = NodeCount;
	if (_pParent != nullptr)
	{
		pNode->idepth += _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	return pNode;
}
void KOctree::CreatevertexList(KNode* _pNode, KVector3 _vMin, KVector3 _vMax)
{
	_pNode->m_VertexList[0].pos = KVector3(_vMin.x, _vMax.y, _vMin.z);
	_pNode->m_VertexList[1].pos = KVector3(_vMin.x, _vMax.y, _vMax.z);
	_pNode->m_VertexList[2].pos = KVector3(_vMax.x, _vMax.y, _vMin.z);
	_pNode->m_VertexList[3].pos = KVector3(_vMax.x, _vMax.y, _vMax.z);
	_pNode->m_VertexList[4].pos = KVector3(_vMin.x, _vMin.y, _vMin.z);
	_pNode->m_VertexList[5].pos = KVector3(_vMin.x, _vMin.y, _vMax.z);
	_pNode->m_VertexList[6].pos = KVector3(_vMax.x, _vMin.y, _vMin.z);
	_pNode->m_VertexList[7].pos = KVector3(_vMax.x, _vMin.y, _vMax.z);
}

bool KOctree::CheckIn(KNode* _pNode, KCube _vValue) // 노드안에 속해 있는지 체크
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

KNode* KOctree::Search(KNode* _pNode, KCube _vValue)
{
	if (CheckIn(_pNode, _vValue))
	{
		for (int iChild = 0; iChild < MAXCHILD; iChild++)
		{
			if (_pNode->m_pChild[iChild] != nullptr)
			{
				KNode* tmp;
				tmp = Search(_pNode->m_pChild[iChild], _vValue);
				if (tmp != nullptr)
					return tmp;
			}
		}
		return _pNode;
	}
	return nullptr;
}

void KOctree::AddObject(KVector3 _vMin, KVector3 _vMax)
{

	KCube* m_pCube = new KCube;
	m_pCube->vCtrlPoint = _vMin;
	m_pCube->vMaxPoint = _vMax;
	m_pCube->vSize = (_vMax - _vMin) / 2.0f;
	m_pCube->vCenterPoint = _vMin + m_pCube->vSize;

	KNode* tmp = Search(m_pRootNode, *m_pCube);
	if (tmp != nullptr)
	{
		tmp->m_ObejctList.push_back(m_pCube);
	}


}

void KOctree::Show(KNode* _pNode)
{
	if (!_pNode->m_ObejctList.empty())
	{
		std::cout << "|||오브젝트 위치 노드|||" << "  " << "|||해당하는 위치 오브젝트 갯수|||" << std::endl;
		std::cout << "\t" << _pNode->NodeNumber << "\t\t\t\t" << _pNode->m_ObejctList.size() << std::endl;
	}
	for (int iChild = 0; iChild < MAXCHILD; iChild++)
	{
		if (_pNode->m_pChild[iChild] != nullptr)
		{
			Show(_pNode->m_pChild[iChild]);
		}
	}
}


HRESULT KOctree::CreateVertexBuffer(KNode* pNode)
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(PNCT_VERTEX) * pNode->m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &pNode->m_VertexList.at(0);
	hr = g_pd3dDevice->CreateBuffer(&bd, &data, &pNode->m_pVertexBuffer);
	if (FAILED(hr)) return hr;
	return hr;
}

bool KOctree::Frame()
{
	return false;
}

bool KOctree::Render(ID3D11DeviceContext* pContext)
{
	SetNodebuffers(m_pRootNode, pContext);
	return false;
}
bool KOctree::SetNodebuffers(KNode* _pNode, ID3D11DeviceContext* pContext)
{
	for (int iChild = 0; iChild < MAXCHILD; iChild++)
	{
		UINT pStrides = sizeof(PNCT_VERTEX);
		UINT pOffsets = 0;
		pContext->IASetVertexBuffers(0, 1,&_pNode->m_pVertexBuffer, &pStrides, &pOffsets);
		if(_pNode->m_pChild[iChild] != nullptr)
		SetNodebuffers(_pNode->m_pChild[iChild], pContext);
	}
	return true;
}

bool KOctree::Release()
{
	return false;
}
