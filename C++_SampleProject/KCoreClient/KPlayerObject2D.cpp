#include "KPlayerObject2D.h"
#include <KInput.h>
#include <string>
bool KPlayerObject2D::CreatePlayer(KShader* _VS, KShader* _PS, ID3D11Device* _Device, ID3D11DeviceContext* _Context)
{
	m_pd3dDevice = _Device;
	m_pContext = _Context;
	SetDevice(m_pd3dDevice, m_pContext);

	ActionTexInit();
	Init();
	SetRectDraw({ 0,0, 98 , 155 });
	SetRectSouce({ 0,0,98,155 });
	SetPosition(KVector2((200), (500)));
	m_pMaskTex = nullptr;
	m_pVShader = _VS;
	m_pPShader = _PS;
	for (int j = 0; j < PlayerAnimation->GetData()->GetClipMax(); j++)
	{
		PlayerAnimation->ChangeClip(j);
		for (int i = 0; i < PlayerAnimation->GetClip()->GetFrameMAX(); i++)
		{
			m_pColorTex = PlayerAnimation->GetClip()->GetTex(i);
			if (!Create(m_pd3dDevice, m_pContext))
			{
				return false;
			}
		}
		
	}


	SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
}
bool KPlayerObject2D::Create(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext)
{
		HRESULT hr;
		/*m_rtCollision = TRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&TBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&TBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));*/
		if (!SetVertexData())
		{
			return false;
		}
		if (!SetIndexData())
		{
			return false;
		}
		if (!SetConstantData())
		{
			return false;
		}
		if (!CreateVertexBuffer())
		{
			return false;
		}
		if (!CreateIndexBuffer())
		{
			return false;
		}
		if (!CreateConstantBuffer())
		{
			return false;
		}
		if (!CreateInputLayout())
		{
			return false;
		}
		// (소스컬러*D3D11_BLEND_SRC_ALPHA) 
		//                  + 
		// (대상컬러*D3D11_BLEND_INV_SRC_ALPHA)
		// 컬러   =  투명컬러값 = (1,1,1,1)
		// 마스크 =  1.0 - 투명컬러값 = (1,1,1,1)

		// FinalColor = SrcColor*SrcAlpha + DestColor*(1.0f- SrcAlpha) 	    
		// if SrcAlpha == 0 완전투명
		//           FinalColor() = SrcColor*0 + DestColor*(1-0)
		//                FinalColor = DestColor;
		// if SrcAlpha == 1 완전불투명
		//           FinalColor() = SrcColor*1 + DestColor*(1-1)
		//                FinalColor = SrcColor;
		// 혼합상태 = 소스(지금드로우객체 픽셀) (연산) 대상(백버퍼 객체:픽셀)
		// 혼합상태 = 픽셀쉐이더 출력 컬러  (연산:사칙연산) 출력버퍼의 컬러
		D3D11_BLEND_DESC  blenddesc;
		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		blenddesc.AlphaToCoverageEnable = true;
		//bd.IndependentBlendEnable;
		blenddesc.RenderTarget[0].BlendEnable = TRUE;
		blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//// A 연산 저장
		blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;
		hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlend);

		blenddesc.RenderTarget[0].BlendEnable = FALSE;
		hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_AlphaBlendDisable);
		return true;
}

bool KPlayerObject2D::ActionTexInit()
{	
	KAnimationData* pData;
	pData = new KAnimationData(7); // 애니메이션 갯수
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

	PlayerAnimation = new KAnimation(pData);
	
	KTexture* pTex;
	pTex = pData->GetClip(3)->GetTex(8);
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

bool KPlayerObject2D::Shoot()
{
	PlayerAnimation->ChangeClip(6);
	return false;
}

bool KPlayerObject2D::Release()
{
	PlayerAnimation->~KAnimation();
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
