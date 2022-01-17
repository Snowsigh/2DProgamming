#include "KThread.h"
void KThread::CreateThread()
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(NULL, 0,
		HandleRunner,
		(LPVOID)this,
		0, &m_iID);
	m_bStarted = true;
}
bool KThread::Run()
{
	return true;
}
unsigned int WINAPI KThread::HandleRunner(LPVOID prameter)
{
	KThread* ptThread = (KThread*)prameter;
	ptThread->Run();
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