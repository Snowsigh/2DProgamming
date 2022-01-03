#pragma once
#include <map>
#include <queue>
#include <vector>
#include <KDevice.h>
#define MAXCHILD 8
#define MINCUBESIZE 30
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

	ID3D11Buffer* m_pIndexBuffer;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11Buffer* m_pConstantBufferPS;
	 UINT uStride = NULL;
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
	~KNode()
	{
		m_ObejctList.clear();
		if(m_pIndexBuffer)m_pIndexBuffer->Release();
		if(m_pVertexBuffer)m_pVertexBuffer->Release();
		if(m_pConstantBuffer)m_pConstantBuffer->Release();
		if(m_pConstantBufferPS)m_pConstantBufferPS->Release();
	}
};
class KOctree
{
public:
	KNode* m_pRootNode;
	int m_ChildNode = MAXCHILD;
	int NodeCount = 0;

	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;
public:
	KNode* CreateNode(KNode* _pNode, KVector3 _vMin, KVector3 _vMax);
	bool CheckIn(KNode* _pNode, KCube _vValue);
	void BuildTree(KNode* _pNode);
	bool CreateVectexBuffer(KNode* _pNode);
	bool CreateIndexBuffer(KNode* _pNode);
	bool CreateConstantsBuffer(KNode* _pNode, TMatrix* pWorld, TMatrix* pView, TMatrix* pProj);
	bool CreateShaderLayout(ID3D11DeviceContext* pContext);
	bool Release();
public:
	KOctree();
	~KOctree();

private:

};
