#pragma once
#include "KModel.h"
class KShape : public KModel
{

};
class KPlane : public KShape
{
public:
	bool CreateVertexData() override;
	bool CreateIndexData() override;


};

