#pragma once
#include "KVector.h"
enum KCollisionResult
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
struct KRect2D
{
	KVector2 vMin;
	KVector2 vMax;
	KVector2 vMiddle;
	KVector2 size;
	bool operator == (const KRect2D& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	KRect2D() {};
	KRect2D(KVector2 vMin, KVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	KRect2D(KVector2 v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + KVector2(w, h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
// »≠∏È¡¬«•∞Ë+¡ﬂæ”¿Ã ø¯¡°
struct KRect
{
	KVector2 vMin;
	KVector2 vMax;
	KVector2 vMiddle;
	KVector2 size;
	bool operator == (const KRect& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	KRect() {};
	KRect(KVector2 vMin, KVector2 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	KRect(KVector2 pos, float w, float h)
	{
		vMiddle = pos;
		this->vMin = vMiddle - KVector2(w / 2.0f, h / 2.0f);
		this->vMax = vMiddle + KVector2(w / 2.0f, h / 2.0f);
		this->size.x = w;
		this->size.y = h;
	}
};
struct KBox
{
	KVector3 vMin;
	KVector3 vMax;
	KVector3 vMiddle;
	KVector3 size;
	bool operator == (const KBox& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	KBox() {};
	KBox(KVector3 vMin, KVector3 vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	KBox(KVector3 v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + KVector3(w, h, q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
class KCollsion
{
public:
	static bool   RectToPoint(KRect rt, int x, int y);
	static bool   RectToPoint(KRect rt, KVector2 v);
	static KCollisionResult    RectToRect(KRect, KRect);
	static KCollisionResult    ToRect(KRect rt1, KRect rt2);
	static KRect  UnionRect(KRect rt1, KRect rt2);
	static bool  IntersectRect(KRect rt1, KRect rt2, KRect* rt);

	static bool   BoxToPoint(KBox rt, int x, int y, int z);
	static bool   BoxToPoint(KBox rt, KVector3 v);
	static KCollisionResult    BoxToBox(KBox, KBox);
	static KBox   UnionBox(KBox rt1, KBox rt2);
	static bool  IntersectBox(KBox rt1, KBox rt2, KBox* rt);
};

