#pragma once
#include <iostream>
#include <vector>
#include "KVector.h"
#define MAXCHILD 8
struct KCube
{
	KVector3 vCtrlPoint;
	KVector3 vMaxPoint;
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
		else
			return false;
	}

};

class KOctree
{

};

