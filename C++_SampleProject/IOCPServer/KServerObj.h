#pragma once
#include <KStd.h>
class KServerObj
{
public:
	CRITICAL_SECTION m_cs;
	HANDLE m_hKillevent;
public:
	KServerObj();
	virtual ~KServerObj();
};

