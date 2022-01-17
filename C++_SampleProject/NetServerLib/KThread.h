#pragma once
#include "KServerObject.h"
#include <process.h>
class KThread : public KServerObject
{
public:
	unsigned int m_hThread;
	unsigned int m_iID;
	bool m_bStarted;
public:
	void CreateThread();
	virtual bool Run();
	static unsigned int WINAPI HandleRunner(LPVOID prameter);
public:
	KThread();
	virtual ~KThread();
};

