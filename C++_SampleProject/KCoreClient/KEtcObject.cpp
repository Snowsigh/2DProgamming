#include "KEtcObject.h"

bool KEtcObject::Init()
{
	KObject2D::Init();
    return false;
}

bool KEtcObject::Frame()
{
	m_vColor.x = m_fAlpha;
	m_vColor.y = m_fAlpha;
	m_vColor.z = m_fAlpha;
	m_vColor.w = 1.0f;
	KObject2D::Frame();
    return false;
}

void KEtcObject::HitOverlap(KBaseObject* pObj, DWORD dwState)
{
}

void KEtcObject::HitSelect(KBaseObject* pObj, DWORD dwState)
{
}

KEtcObject::KEtcObject()
{
}

KEtcObject::~KEtcObject()
{
}
