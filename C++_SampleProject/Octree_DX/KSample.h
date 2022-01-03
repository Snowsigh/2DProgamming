#pragma once
#include <KCore.h>
#include "KOctree.h"
#include "KCube.h"
class Sample : public KCore
{
public:	
	KCubes m_kCube;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

};
