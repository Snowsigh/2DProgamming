#include "KThread.h"
void KThread::CreateThread()
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(NULL, 0,
		HandleRunner,
		this,
		0, &m_iID);
	m_bStarted = true;
}
void KThread::CreateThread(LPVOID pValue)
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(NULL, 0,
		HandleRunner,
		this,
		0, &m_iID);
	m_pObject = pValue;
	m_bStarted = true;
}
void KThread::Join()
{
	::WaitForSingleObject((HANDLE)m_hThread, INFINITE);
}
void KThread::Detach()
{
	CloseHandle((HANDLE)m_hThread);
}
bool KThread::Run()
{
	return true;
}
unsigned int WINAPI KThread::HandleRunner(LPVOID prameter)
{
	KThread* ptThread = (KThread*)prameter;
	if (ptThread != nullptr)
	{
		ptThread->Run();
		return 1;
	}
	return 0;
}
KThread::KThread()
{
	m_hThread = 0;
	m_iID = 0;
	m_bStarted = false;
}
KThread::~KThread()
{

}