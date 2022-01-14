#pragma once
#include "KServerObj.h"
class KThread : public KServerObj
{
public:
	uintptr_t m_hThread;
	unsigned int m_iID;
	bool m_bStart;
	LPVOID m_pObject;
public:
	void Create();
	void Create(LPVOID pObject);
	void Join();
	void Detach();
	virtual bool Run();
	static unsigned int WINAPI Runner(LPVOID param);
};

