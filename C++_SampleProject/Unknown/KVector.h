#pragma once
#include <math.h>
struct KVector3
{
public:
	float x;
	float y;
	float z;
	KVector3  operator += (KVector3 p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	KVector3  operator * (float s)
	{
		KVector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;
		return ret;
	}
	KVector3  operator + (KVector3 p)
	{
		KVector3 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		ret.z = z + p.z;
		return ret;
	}
	KVector3  operator - (KVector3 p)
	{
		KVector3 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		ret.z = z - p.z;
		return ret;
	}
	KVector3  operator / (float fValue)
	{
		KVector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;
		return ret;
	}
public:
	KVector3() {}
	KVector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};