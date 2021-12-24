#include "KOctree.h"

void KOctree::Init(KVector3 _vMaxCube)
{

	m_pRootNode = CreateNode(nullptr, KVector3(0, 0, 0), _vMaxCube);
	BuildTree(m_pRootNode);
}

KNode* KOctree::CreateNode(KNode* _pParent, KVector3 _vMin, KVector3 _vMax)
{
	KNode* pNode = new KNode(_vMin, _vMax);
	if (_pParent != nullptr)
	{
		pNode->idepth += _pParent->idepth + 1;
		pNode->m_pParent = _pParent;
	}
	return pNode;
}

void KOctree::CheckIn()
{
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

void KOctree::Search()
{
}

void KOctree::AddObject()
{
}

void KOctree::Release()
{
}
