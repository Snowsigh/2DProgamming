#pragma once
#include <iostream>
#include <math.h>
struct KFloat2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
struct KFloat3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};

class KVector3 : public KFloat3
{
public:
	KVector3();
	KVector3(float x, float y, float z);
	KVector3(const KVector3& v);
public:
	KVector3 operator + (const KVector3& v);
	KVector3 operator - (const KVector3& v);
	KVector3 operator * (float fValue);
	KVector3 operator / (float fValue);
	bool operator == (const KVector3& v);
	bool operator != (const KVector3& v);
	// 정규화
	KVector3 Normalize();
	KVector3 Normal();
	friend KVector3 Normalize(KVector3& v);
	// 크기
	float Length();
};

class KVector2 : public KFloat2
{
public:
	KVector2();
	KVector2(float x, float y);
	KVector2(const KVector2& v);
public:
	KVector2 operator + (const KVector2& v);
	KVector2 operator - (const KVector2& v);
	KVector2 operator * (float fValue);
	KVector2 operator / (float fValue);
	KVector2 operator += (const KVector2& v);
	KVector2 operator -= (const KVector2& v);
	bool operator == (const KVector2& v);
	bool operator != (const KVector2& v);
	// 정규화
	KVector2 Normalize();
	KVector2 Normal();
	friend KVector2 Normalize(KVector2& v);
	// 크기
	float Length();
	float Distance(KVector2& v);
};