#pragma once
#include <iostream>
#include <vector>
#include "KVector.h"
#define MAXCHILD 8
#define MINCUBESIZE 30.0f

struct KCube
{
	KVector3 vCtrlPoint;
	KVector3 vMaxPoint;
	KVector3 vSize;
	KVector3 vCenterPoint;
};
struct KNode
{
	KCube m_Cube;
	int idepth;
	KNode* m_pParent;
	KNode* m_pChild[MAXCHILD];
	std::vector<KCube*> m_ObejctList;
	int NodeNumber = 0;
	bool InCube(KVector3 _vPos)
	{
		if (m_Cube.vCtrlPoint.x <= _vPos.x && m_Cube.vMaxPoint.x >= _vPos.x &&
			m_Cube.vCtrlPoint.y <= _vPos.y && m_Cube.vMaxPoint.y >= _vPos.y &&
			m_Cube.vCtrlPoint.z <= _vPos.z && m_Cube.vMaxPoint.z >= _vPos.z)
		{
			return true;
		}
			return false;
	}

	KNode(KVector3 _vMin, KVector3 _vMax)
	{
		idepth = 0;
		m_pParent = nullptr;
		m_Cube.vCtrlPoint = _vMin;
		m_Cube.vMaxPoint = _vMax;
		m_Cube.vSize = (_vMax - _vMin) / 2.0f;
		m_Cube.vCenterPoint = _vMin + m_Cube.vSize;
		for (int iChild = 0; iChild < MAXCHILD; iChild++)
		{
			m_pChild[iChild] = nullptr;
		}

	}
};

class KOctree
{
public:
	KNode* m_pRootNode;
	int m_ChildNode = MAXCHILD;
	int NodeCount = 0;
public:
	void Init(KVector3 _vMaxCube);
	KNode* CreateNode(KNode* _pNode, KVector3 _vMin, KVector3 _vMax);
	bool CheckIn(KNode* _pNode, KCube _vValue);
	void BuildTree(KNode* _pNode);
	KNode* Search(KNode* _pNode, KCube _vValue);
	void AddObject(KVector3 _vMin, KVector3 _vMax);


	void Show(KNode* _pNode);

};

