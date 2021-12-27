#pragma once
#include "KDevice.h"
#include "KModel.h"

class KVertex : public KModel
{

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();


public:
	KVertex();
	virtual ~KVertex() {};
};


