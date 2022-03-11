#include "KPlayerObject2D.h"
#include <KInput.h>
#include <string>
bool KPlayerObject2D::CreatePlayer(KShader* _VS, KShader* _PS, ID3D11Device* _Device, ID3D11DeviceContext* _Context)
{
	return ActionTexInit();
}

bool KPlayerObject2D::ActionTexInit()
{	
	KAnimationData* pData;
	pData = new KAnimationData(9); // 애니메이션 갯수
	KAnimationClip* pClip;		   // 넣을 애니메이션 로드

	pClip = new KAnimationClip(L"../../Data/Cuphead/Idle/cuphead_idle_000", 5);
	pData->AddClip(0, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Jump/Cuphead/cuphead_jump_000", 8);
	pData->AddClip(1, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Dash/Ground/cuphead_dash_000", 8);
	pData->AddClip(2, pClip);
	
	pClip = new KAnimationClip(L"../../Data/Cuphead/Run/Normal/cuphead_run_00", 16); //두자리 클립은 00 두개만 붙인다
	pData->AddClip(3, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Run/Normal/cuphead_run_turnaround_000", 2);
	pData->AddClip(4, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Shoot/Straight/cuphead_shoot_straight_000", 3);
	pData->AddClip(5, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Run/Shooting/Straight/cuphead_run_shoot_00", 16); //두자리 클립은 00 두개만 붙인다
	pData->AddClip(6, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Run/Shooting/Diagonal Up/cuphead_run_shoot_diagonal_up_00", 16); //두자리 클립은 00 두개만 붙인다
	pData->AddClip(7, pClip);

	pClip = new KAnimationClip(L"../../Data/Cuphead/Shoot/Diagonal Up/cuphead_shoot_diagonal_up_000", 3);
	pData->AddClip(8, pClip);



	PlayerAnimation = new KAnimation(pData);
	return true;
}
void KPlayerObject2D::HitOverlap(KBaseObject* pObj, DWORD dwState)
{
}

bool KPlayerObject2D::Frame()
{
	m_vColor.x = m_fAlpha;
	m_vColor.y = m_fAlpha;
	m_vColor.z = m_fAlpha;
	m_vColor.w = 1.0f;
	KObject2D::Frame();

	if (I_INPUT.GetKey(VK_UP) == KEY_HOLD)
	{
		UpdateRectDraw({ 0,0, 126 , 150 });
		CHANGECLIP(8)
		KVector2 pos;
		AddPosition(pos);
	}
	else if (I_INPUT.GetKey(VK_LEFT) == KEY_HOLD)
	{
		UpdateRectDraw({ 0,0, 135 , 155 });
		CHANGECLIP(3)
		KVector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame;
		AddPositionConvertex(pos);
	}
	else if (I_INPUT.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		UpdateRectDraw({ 0,0, 135 , 155 });
		CHANGECLIP(3)
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	else if (I_INPUT.GetKey('X') == KEY_HOLD) //Jump
	{
		UpdateRectDraw({ 0,0, 77 , 79 });
		CHANGECLIP(1)
		KVector2 pos;
		pos.y -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	else if (I_INPUT.GetKey('Z') == KEY_HOLD) //Fire
	{
		UpdateRectDraw({ 0,0, 126 , 150 });
		CHANGECLIP(5)
		KVector2 pos;
		AddPosition(pos);
	}
	else if (I_INPUT.GetKey('C') == KEY_HOLD) //Dash
	{
		KVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	else
	{
		UpdateRectDraw({ 0,0, 98 , 155 });
		CHANGECLIP(0)
		KVector2 pos;
		AddPosition(pos);
	}
	
	return true;
}

bool KPlayerObject2D::Render()
{
	
	m_pContext->PSSetShaderResources(0, 1, &PlayerAnimation->GetTex()->m_pSRV);
	
	/*if (m_pMaskTex != nullptr)
		m_pContext->PSSetShaderResources(1, 1, &m_pMaskTex->m_pSRV);*/

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

	AnimTime += g_fSecPerFrame * 20;
	if (AnimTime > 1.0f)
	{
		PlayerAnimation->UpdataFrame();
		AnimTime -= 1.0f;
	}
	

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

bool KPlayerObject2D::Shoot()
{
	PlayerAnimation->ChangeClip(6);
	return false;
}

bool KPlayerObject2D::Release()
{
	return true;
}

void KPlayerObject2D::AddPositionConvertex(KVector2 vPos)
{
	// 현재위치
	m_vPos += vPos;
	//  10,10f    ~     w(50, 10)
	//
	//   h
	m_rtCollision = KRect(m_vPos, m_fWidth, m_fHeight);

	ConvertIndex(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	ConvertVertex(m_VertexList);
	m_pContext->UpdateSubresource(
		m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
}

void KPlayerObject2D::ConvertVertex(std::vector<SimpleVertex>& retList)
{
	retList[1].t.x = -1;
	retList[3].t.x = -1;
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
