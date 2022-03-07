#include "KPlayerObject2D.h"
#include <KInput.h>
#include <string>
bool KPlayerObject2D::ActionTexInit()
{

	return false;
}
void KPlayerObject2D::HitOverlap(KBaseObject* pObj, DWORD dwState)
{
}

bool KPlayerObject2D::Frame()
{
	if (I_INPUT.GetKey(VK_UP) == KEY_HOLD)
	{
		Create(m_pd3dDevice, m_pContext, nullptr, L"../../Data/Cuphead/Aim/Up/cuphead_aim_up_0001");
	}
	if (I_INPUT.GetKey(VK_LEFT) == KEY_HOLD)
	{
		KVector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (I_INPUT.GetKey(VK_DOWN) == KEY_HOLD)
	{
		KVector2 pos;
		pos.y += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (I_INPUT.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (I_INPUT.GetKey('X') == KEY_HOLD) //Jump
	{
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (I_INPUT.GetKey('Z') == KEY_HOLD) //Fire
	{
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (I_INPUT.GetKey('C') == KEY_HOLD) //Dash
	{
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	return true;
}

KPlayerObject2D::KPlayerObject2D()
{
	m_fSpeed = 300.0f; // ¼Ó·Â
	m_dwCollisonType = KCollisionType::Overlap;
	m_dwSelectType = KSelectType::Select_Overlap;
}

KPlayerObject2D::~KPlayerObject2D()
{
}
