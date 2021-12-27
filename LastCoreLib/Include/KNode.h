#pragma once
#include "KMap.h"
#include "KStd.h"
struct Rect
{
	float x, y, w, h;
};
struct KRect
{
	TVector2 p0;
	TVector2 p1;
	TVector2 wh;
};
typedef std::vector<DWORD> DWORD_VECTOR;
struct KLodPatch
{
	UINT iLodLevel;
	DWORD_VECTOR IndexList[16];
	ID3D11Buffer* IndexBufferList[16] = { nullptr, };
	void Release()
	{
		for (int iBuffer = 0; iBuffer < 16; iBuffer++)
		{
			if (IndexBufferList[iBuffer])
			{
				IndexBufferList[iBuffer]->Release();
				IndexBufferList[iBuffer] = nullptr;
			}

		}
	}
	KLodPatch() {};
	~KLodPatch()
	{
		Release();
	}
};
class KNode
{
public:
	UINT m_iLodLevel;
public:
	static      int g_iNewCounter;
	int			m_iIndex;
	POINT		m_Element;
	KRect		m_tRect;
	std::vector<TVector2>  m_ObjectList;
	std::vector<DWORD>  m_CornerList;
	std::vector<DWORD>  m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;
	std::vector<PNCT_VERTEX>  m_pVertexList;
	ID3D11Buffer* m_pVertexBuffer;
	TVector3			m_vCenter;
	KNode* m_pChild[4];
	KNode* m_NeighborList[4];
	int			m_iDepth;
	bool		m_bLeaf;
	KNode* m_pParent;
public:
	bool		AddObject(TVector2 pos);
	bool		IsRect(TVector2 pos);
	void		SetRect(float x, float y, float w, float h);
public:
	KNode() {};
	KNode(UINT x, UINT y, UINT w, UINT h);
	~KNode();
};

