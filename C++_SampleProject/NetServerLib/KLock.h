#pragma once
#include "KServerObject.h"
class KLock
{
	KServerObject* m_pObj;
public:
	KLock(KServerObject* obj)
	{
		if (m_pObj != nullptr)
		{
			EnterCriticalSection(&m_pObj->m_cs);
		}
	}
	virtual	~KLock()
	{
		LeaveCriticalSection(&m_pObj->m_cs);
	}

};
