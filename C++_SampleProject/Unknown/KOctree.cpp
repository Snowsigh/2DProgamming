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
	pNode->NodeNumber = NodeCount;
	if (_pParent != nullptr)
	{
		pNode->idepth += _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	return pNode;
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

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCtrlPoint.z  ) ,
																	KVector3(_pNode->m_Cube.vMaxPoint.x,_pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCenterPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCtrlPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCenterPoint.z),
																	KVector3(_pNode->m_Cube.vCenterPoint.x,	_pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vMaxPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCenterPoint.x, _pNode->m_Cube.vCtrlPoint.y, _pNode->m_Cube.vCenterPoint.z),
																	KVector3(_pNode->m_Cube.vMaxPoint.x,_pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vMaxPoint.z));
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, KVector3(_pNode->m_Cube.vCtrlPoint.x,	_pNode->m_Cube.vCenterPoint.y, _pNode->m_Cube.vCtrlPoint.z),
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

		_pNode->m_pChild[MAXCHILD - tmp] = CreateNode(_pNode, _pNode->m_Cube.vCenterPoint,_pNode->m_Cube.vMaxPoint);
		BuildTree(_pNode->m_pChild[MAXCHILD - tmp]);
		tmp--;
	}
}

KNode* KOctree::Search(KNode* _pNode, KCube _vValue)
{
	if (CheckIn(_pNode,_vValue))
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
