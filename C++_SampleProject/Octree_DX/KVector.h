#pragma once
#include <math.h>
struct KVector3
{
public:
	float x;
	float y;
	float z;
	KVector3  operator += (const KVector3 p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	KVector3  operator * (const float s)
	{
		KVector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;
		return ret;
	}
	KVector3  operator + (const KVector3 p)
	{
		KVector3 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		ret.z = z + p.z;
		return ret;
	}
	KVector3  operator - (const KVector3 p)
	{
		KVector3 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		ret.z = z - p.z;
		return ret;
	}
	KVector3  operator / (const float fValue)
	{
		KVector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;
		return ret;
	}
	bool operator == (KVector3 p)
	{
		if (fabs(x - p.x) < 0.001f)
		{
			if (fabs(y - p.y) < 0.001f)
			{
				if (fabs(z - p.z) < 0.001f)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator >= (KVector3 p)
	{
		if (x >= p.x)
		{
			if (y >= p.y)
			{
				if (z >= p.z)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator <= (KVector3 p)
	{
		if (x <= p.x)
		{
			if (y <= p.y)
			{
				if (z <= p.z)
				{
					return true;
				}
			}
		}
		return false;
	}

	//크기
	float Length()
	{
		float ret = (x * x) + (y * y) + (z * z);
		return sqrt(ret);
	}
	//정규화
	KVector3 Normalize()
	{
		KVector3 vtmp;
		float length = 1.0f / Length();
		vtmp.x = vtmp.x * length;
		vtmp.y = vtmp.y * length;
		vtmp.z = vtmp.z * length;
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