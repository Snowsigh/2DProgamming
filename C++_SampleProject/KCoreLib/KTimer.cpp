#include "KTimer.h"
#include <tchar.h>
bool KTimer::Init()
{
    m_iFPS = 0;
    m_fFrameTime = 0.0f;
    m_fAccumulation = 0.0f;
    m_fSecPerFrame = 0.0f;
    m_dwBeforeTick = timeGetTime();
    m_dwFrameCount = 0;
    return true;
}

bool KTimer::Frame()
{
    DWORD dwElapseTick = 0;
    DWORD dwCurrenTick = timeGetTime();
    dwElapseTick = dwCurrenTick - m_dwBeforeTick;
    m_fAccumulation += dwElapseTick / 1000.0f;
    m_fSecPerFrame = dwElapseTick / 1000.0f;
    m_fFrameTime += m_fSecPerFrame;

    if (m_fFrameTime >= 1.0f)
    {
        m_iFPS = m_dwFrameCount;
        m_dwFrameCount = 0;
        m_fFrameTime -= 1.0f;
    }

    m_dwFrameCount++;
    m_dwBeforeTick = dwCurrenTick;
    return true;
}

bool KTimer::Render()
{
    memset(m_strBuffer, 0, sizeof(TCHAR) * MAX_PATH);
    _stprintf_s(m_strBuffer, _T("FPS: %d, %10.6f %10.6f"), m_iFPS, m_fSecPerFrame, m_fAccumulation);
    return true;
}

bool KTimer::Release()
{
    return false;
}

KTimer::KTimer()
{
}

KTimer::~KTimer()
{
}
