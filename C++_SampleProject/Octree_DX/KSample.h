#pragma once
#include <KCore.h>
#include "KOctree.h"
#include "KCube.h"
struct ConstantBuffer
{
	TMatrix  matWorld;
	TMatrix  matView;
	TMatrix  matProj;
};
struct KBox
{
	ConstantBuffer cb;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11Buffer* m_pConstantBuffer;

	void SetMatrix(TMatrix* _w, TMatrix* _v, TMatrix* _p)
	{
		if (_w != nullptr)
		{
			cb.matWorld = _w->Transpose();
		}
		if (_v != nullptr)
		{
			cb.matView = _v->Transpose();
		}
		if (_p != nullptr)
		{
			cb.matProj = _p->Transpose();
		}
	}
	~KBox()
	{
		if(m_pVertexBuffer)m_pVertexBuffer->Release();
		if(m_pIndexBuffer)m_pIndexBuffer->Release();
		if(m_pConstantBuffer)m_pConstantBuffer->Release();
	}
};
class Sample : public KCore
{
public:	
	ID3D11RasterizerState* RasState;
	KOctree m_kOctree;
	KBox* m_1Box;
	

public:
	KBox* CreateBox(KVector3 _MaxArea, TMatrix* _w, TMatrix* _v, TMatrix* _p);
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

};
