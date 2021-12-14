#pragma once
#include "KNodes.h"
class KFileIO
{
public:
	int iCount = 0;
public:
	KNode* fileInput();
	void fileOutput(const KNode* _Node, const int _ivalue);
	int NodeCount();
};

