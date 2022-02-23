#include "KInput.h"
POINT g_ptMouse;

bool KInput::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256);
	return false;
}

bool KInput::Frame()
{
	//ȭ��(��ũ��)��ǥ��
	GetCursorPos(&m_ptMouse);
	//Ŭ���̾�Ʈ(������)��ǥ��
	ScreenToClient(g_hWnd, &m_ptMouse);
	g_ptMouse = m_ptMouse;

	// ���콺 ��ư VK_LBUTTON,  VK_RBUTTON, VK_MBUTTON,
	for (int iKey = 0; iKey < 256; iKey++)
	{
		SHORT sKey = GetAsyncKeyState(iKey);
		// 0000 0000 0000 0000
		// 1000 0000 0000 0000
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[iKey] == KEY_FREE)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else
		{
			if (m_dwKeyState[iKey] == KEY_PUSH ||
				m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}
	}

	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON];
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];
	return false;
}

bool KInput::Render()
{
	return false;
}

bool KInput::Release()
{
	return false;
}

DWORD KInput::GetKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}
