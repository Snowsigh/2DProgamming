#pragma once
#include "KVector.h"
struct float4x4
{
    union
    {
        struct 
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
            
        };
        float m[4][4];
    };
};

class KMatrix : public float4x4
{
public:
	
	KMatrix ChanigeKT(TMatrix v0) 
	{
		KMatrix q;
		q._11 = v0._11; q._12 = v0._12; q._13 = v0._13; q._14 = v0._14;
		q._21 = v0._21; q._22 = v0._22; q._23 = v0._23; q._24 = v0._24;
		q._31 = v0._31; q._32 = v0._32; q._33 = v0._33; q._34 = v0._34;
		q._41 = v0._41; q._42 = v0._42; q._43 = v0._43; q._44 = v0._44;	
		return q;
	}
	TMatrix ChanigeTK(KMatrix v0)
	{
		TMatrix q;
		q._11 = v0._11; q._12 = v0._12; q._13 = v0._13; q._14 = v0._14;
		q._21 = v0._21; q._22 = v0._22; q._23 = v0._23; q._24 = v0._24;
		q._31 = v0._31; q._32 = v0._32; q._33 = v0._33; q._34 = v0._34;
		q._41 = v0._41; q._42 = v0._42; q._43 = v0._43; q._44 = v0._44;
		return q;
	}

	KMatrix()
	{
		Identity();
	}
	void Identity()
	{
		_12 = _13 = _14 = 0;
		_21 = _23 = _24 = 0;
		_31 = _32 = _34 = 0;
		_41 = _42 = _43 = 0;
		_11 = _22 = _33 = _44 = 1;
	}
	static KMatrix RotationZ(float fRadian)
	{
		KMatrix matRet;
		float fCos = cosf(fRadian);
		float fSin = sinf(fRadian);
		matRet._11 = fCos; matRet._12 = fSin;
		matRet._21 = -fSin; matRet._22 = fCos;
		return matRet;
	}

	static KMatrix RotationY(float fRadian)
	{
		KMatrix matRet;
		float fCos = cosf(fRadian);
		float fSin = sinf(fRadian);
		matRet._11 = fCos; matRet._13 = -fSin;
		matRet._31 = fSin; matRet._33 = fCos;
		return matRet;
	}
	
	KMatrix Transpose()
	{
		KMatrix matrix;
		matrix._11 = _11; matrix._12 = _21; matrix._13 = _31; matrix._14 = _41;
		matrix._21 = _12; matrix._22 = _22; matrix._23 = _32; matrix._24 = _42;
		matrix._31 = _13; matrix._32 = _23; matrix._33 = _33; matrix._34 = _43;
		matrix._41 = _14; matrix._42 = _24; matrix._43 = _34; matrix._44 = _44;
		return matrix;
	}
	static KMatrix ViewLookAt(KVector3& vPos,
		KVector3& vTarget,
		KVector3& vUp)
	{
		KMatrix matRet;
		KVector3 vZ = (vTarget - vPos).Normal();
		KVector3 vX = (vUp ^ vZ).Normal();
		KVector3 vY = (vZ ^ vX).Normal();
		matRet._11 = vX.x; matRet._21 = vX.y; matRet._31 = vX.z;
		matRet._12 = vY.x; matRet._22 = vY.y; matRet._32 = vY.z;
		matRet._13 = vZ.x; matRet._23 = vZ.y; matRet._33 = vZ.z;
		matRet._41 = -(vPos | vX);
		matRet._42 = -(vPos | vY);
		matRet._43 = -(vPos | vZ);
		return matRet;
	}
	static KMatrix PerspectiveFovLH(
		float fNearPlane, float fFarPlane,
		float fovy, float Aspect) // w / h =1.33
	{
		float    h, w, Q;
		h = (float)(1 / tan(fovy * 0.5f));  // 1/tans(x) = cot(x)
		w = h / Aspect;
		Q = fFarPlane / (fFarPlane - fNearPlane);
		KMatrix ret;
		ZeroMemory(&ret, sizeof(KMatrix));
		ret._11 = w;
		ret._22 = h;
		ret._33 = Q;
		ret._43 = -Q * fNearPlane;
		ret._34 = 1;
		return ret;
	}

};

