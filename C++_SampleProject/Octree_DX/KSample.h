#pragma once
#include <KCore.h>
#include "KOctree.h"
#include "KCube.h"
class Sample : public KCore
{
public:	
	ID3D11RasterizerState* RasState;
	KOctree m_kOctree;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

};
