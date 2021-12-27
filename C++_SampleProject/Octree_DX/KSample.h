#pragma once
#include <KCore.h>
class Sample : public KCore
{
public:
	KDebugCamera m_kCamera;

	ID3D11RasterizerState* m_pRsWire;
	ID3D11RasterizerState* m_pRsSolid;

	bool m_bWiremod = false;


public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

};
