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
	std::vector<int> m_ObejctList;
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

	}
};

class KOctree
{
public:
	KNode* m_pRootNode;
	int m_ChildNode = MAXCHILD;
public:
	void Init(KVector3 _vMaxCube);
	KNode* CreateNode(KNode* _pNode, KVector3 _vMin, KVector3 _vMax);
	void CheckIn();
	void BuildTree(KNode* _pNode);
	void Search();
	void AddObject();
	
	void Release();
};

