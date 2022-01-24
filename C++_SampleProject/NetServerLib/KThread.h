#pragma once
#include "KServerObject.h"
#include <process.h>
class KThread : public KServerObject
{
public:
	unsigned int m_hThread;
	unsigned int m_iID;
	bool m_bStarted;
	LPVOID m_pObject;
public:
	void CreateThread();
	void CreateThread(LPVOID pValue);
	void Join();
	void Detach();
	virtual bool Run();
	static unsigned int WINAPI HandleRunner(LPVOID prameter);
public:
	KThread();
	virtual ~KThread();
};

