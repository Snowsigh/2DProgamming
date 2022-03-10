#include "KPlayerObject2D.h"
#include <KInput.h>
#include <string>
bool KPlayerObject2D::ActionTexInit()
{	
	KTexture* pTex;
	PlayerAnimation.IDleClip = new KAnimationClip(L"../../Data/Cuphead/Idle/cuphead_idle_000", 5);
	TEXCHACK(IDleClip)
	PlayerAnimation.JumpClip = new KAnimationClip(L"../../Data/Cuphead/Jump/Cuphead/cuphead_jump_000", 8);
	TEXCHACK(JumpClip)
	PlayerAnimation.DashClip = new KAnimationClip(L"../../Data/Cuphead/Dash/Ground/cuphead_dash_000", 8);
	TEXCHACK(DashClip)
	PlayerAnimation.RunClip = new KAnimationClip(L"../../Data/Cuphead/Run/Normal/cuphead_run_00", 16); //두자리 클립은 00 두개만 붙인다
	TEXCHACK(RunClip)
	PlayerAnimation.TurnClip = new KAnimationClip(L"../../Data/Cuphead/Run/Normal/cuphead_run_turnaround_000", 2);
	TEXCHACK(TurnClip)
	PlayerAnimation.ShootClip = new KAnimationClip(L"../../Data/Cuphead/Shoot/Straight/cuphead_shoot_straight_000", 3);
	TEXCHACK(ShootClip)
	PlayerAnimation.RunShootClip = new KAnimationClip(L"../../Data/Cuphead/Run/Shooting/Straight/cuphead_run_shoot_00", 16); //두자리 클립은 00 두개만 붙인다
	TEXCHACK(RunShootClip)


	return true;
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

bool KPlayerObject2D::Render()
{
	
	if (m_pColorTex != nullptr)
		m_pContext->PSSetShaderResources(0, 1, &m_pColorTex->m_pSRV);
	if (m_pMaskTex != nullptr)
		m_pContext->PSSetShaderResources(1, 1, &m_pMaskTex->m_pSRV);
	if (m_pVShader != nullptr)
	{
		m_pContext->VSSetShader(m_pVShader->m_pVertexShader, NULL, 0);
	}
	if (m_pPShader != nullptr)
	{
		m_pContext->PSSetShader(m_pPShader->m_pPixelShader, NULL, 0);
	}

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(KDxState::m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(KDxState::m_AlphaBlendDisable, 0, -1);
	}

	m_pContext->IASetInputLayout(m_pVertexLayout);


	/*UINT StartSlot;
	UINT NumBuffers;*/
	UINT Strides = sizeof(SimpleVertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer,
		&Strides, &Offsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		//D3D_PRIMITIVE_TOPOLOGY_POINTLIST
		//D3D_PRIMITIVE_TOPOLOGY_LINELIST
	);

	if (m_IndexList.size() <= 0)
		m_pContext->Draw(m_VertexList.size(), 0);
	else
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
	return true;
}

KPlayerObject2D::KPlayerObject2D()
{
	m_fSpeed = 300.0f; // 속력
	m_dwCollisonType = KCollisionType::Overlap;
	m_dwSelectType = KSelectType::Select_Overlap;
}

KPlayerObject2D::~KPlayerObject2D()
{
}
