#include "KThread.h"

void KThread::Create()
{
    if (m_bStart != false) return;
    m_hThread = _beginthreadex(
        nullptr, 0,
        Runner,
        this,
        0,
        &m_iID);
    m_bStart = true;
}

void KThread::Create(LPVOID pObject)
{
    if (m_bStart != false) return;
    m_hThread = _beginthreadex(
        nullptr, 0,
        Runner,
        this,
        0,
        &m_iID);
    m_pObject = pObject;
    m_bStart = true;
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
	return false;
}

unsigned int __stdcall KThread::Runner(LPVOID param)
{
    KThread* pThread = (KThread*)param;
    if (pThread != nullptr)
    {
        pThread->Run();
        return 1;
    }
    return 0;
}
