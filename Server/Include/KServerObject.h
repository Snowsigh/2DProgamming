#pragma once
#include "KStd.h"
class KServerObject
{
public:
	CRITICAL_SECTION m_cs;
public:
	KServerObject()
	{
		InitializeCriticalSection(&m_cs);
	};
	virtual ~KServerObject()
	{
		DeleteCriticalSection(&m_cs);
	};
};

