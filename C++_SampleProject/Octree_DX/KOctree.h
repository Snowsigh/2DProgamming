#pragma once
#include <map>
#include <queue>
#include <vector>
#include <KDevice.h>
//#include "KVector.h"
#define MAXCHILD 8
#define MINCUBESIZE 30.0f

struct PNCT_VERTEX
{
	KVector3 pos;
	KVector3 normal;
	KVector4 color;
	KVector2 tex;
	PNCT_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
};

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

	std::vector<PNCT_VERTEX>  m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;


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

	bool SetNodebuffers(KNode* _pNode, ID3D11DeviceContext* pContext);
	void CreatevertexList(KNode* _pNode, KVector3 _vMin, KVector3 _vMax);
	HRESULT CreateVertexBuffer(KNode* pNode);
public:
	bool	Frame();
	bool	Render(ID3D11DeviceContext* pContext);
	bool    Release();
};

