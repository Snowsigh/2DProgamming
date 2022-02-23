#include "KVector.h"
//Vector2
KVector2::KVector2()
{
	x = y = 0.0f;
}
KVector2::KVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
KVector2::KVector2(const KVector2& v)
{
	x = v.x;
	y = v.y;
}
KVector2 KVector2::operator + (const KVector2& v)
{
	KVector2 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	return ret;
}
KVector2 KVector2::operator - (const KVector2& v)
{
	KVector2 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	return ret;
}

KVector2 KVector2::operator * (float fValue)
{
	KVector2 ret;
	ret.x = this->x * fValue;
	ret.y = this->y * fValue;
	return ret;
}
KVector2 KVector2::operator / (float fValue)
{
	KVector2 ret;
	ret.x = this->x / fValue;
	ret.y = this->y / fValue;
	return ret;
}
KVector2 KVector2::operator += (const KVector2& v)
{
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	return *this;
}
KVector2 KVector2::operator -= (const KVector2& v)
{
	this->x = this->x - v.x;
	this->y = this->y - v.y;
	return *this;
}
bool KVector2::operator == (const KVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return true;
		}
	}
	return false;
}
bool KVector2::operator != (const KVector2& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return false;
		}
	}
	return true;
}

KVector2 KVector2::Normal()
{
	KVector2 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	return ret;
}
KVector2 KVector2::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	return *this;
}
KVector2 Normalize(KVector2& v)
{
	KVector2 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	return ret;
}
// 크기
float KVector2::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}
// 두벡터의 거리 반환
float KVector2::Distance(KVector2& v)
{
	float fDist = (*this - v).Length();
	return fDist;
}
;
//vector3
KVector3::KVector3()
{
	x = y = z = 0.0f;
}
KVector3::KVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
KVector3::KVector3(const KVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
KVector3 KVector3::operator + (const KVector3& v)
{
	KVector3 ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	ret.z = this->z + v.z;
	return ret;
}
KVector3 KVector3::operator - (const KVector3& v)
{
	KVector3 ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	ret.z = this->z - v.z;
	return ret;
}
KVector3 KVector3::operator * (float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	this->z *= fValue;
	return *this;
}
KVector3 KVector3::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	this->z /= fValue;
	return *this;
}
bool KVector3::operator == (const KVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return true;
			}
		}
	}
	return false;
}
bool KVector3::operator != (const KVector3& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return false;
			}
		}
	}
	return true;
}

KVector3 KVector3::Normal()
{
	KVector3 ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	ret.z = z * length;
	return ret;
}
KVector3 KVector3::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	z *= length;
	return *this;
}
KVector3 Normalize(KVector3& v)
{
	KVector3 ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	ret.z = v.z * length;
	return ret;
}
// 크기
float KVector3::Length()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}
