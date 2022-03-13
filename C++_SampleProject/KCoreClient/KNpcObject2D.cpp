#include "KNpcObject2D.h"

bool KNpcObject2D::ActionTexInit()
{
	KAnimationData* pData;
	pData = new KAnimationData(5); // 애니메이션 갯수
	KAnimationClip* pClip;		   // 넣을 애니메이션 로드


	pClip = new KAnimationClip(L"../../Data/Monster/Boss/Cagney Carnation/Intro/Intro_", 20); 
	pData->AddClip(0, pClip);

	pClip = new KAnimationClip(L"../../Data/Monster/Boss/Cagney Carnation/Idle/Idle_", 24);
	pData->AddClip(1, pClip);

	pClip = new KAnimationClip(L"../../Data/Monster/Boss/Cagney Carnation/Creating Object/Create_", 26);
	pData->AddClip(2, pClip);

	pClip = new KAnimationClip(L"../../Data/Monster/Boss/Cagney Carnation/Firing Seed/FS_", 22); //두자리 클립은 00 두개만 붙인다
	pData->AddClip(3, pClip);

	pClip = new KAnimationClip(L"../../Data/Monster/Boss/Cagney Carnation/Final Form/Intro/Final_Intro_", 28); 
	pData->AddClip(4, pClip);





	m_kAnimation = new KAnimation(pData);
	return true;
}

void KNpcObject2D::HitOverlap(KBaseObject* pObj, DWORD dwState)
{
}

bool KNpcObject2D::Init()
{
	CHANGECLIP(1)
		m_kAnimation->m_bAniend = true;
	return false;
}

bool KNpcObject2D::Frame()
{
	m_vColor.x = m_fAlpha;
	m_vColor.y = m_fAlpha;
	m_vColor.z = m_fAlpha;
	m_vColor.w = 1.0f;
	KObject2D::Frame();

	Logic();
	return false;
}

bool KNpcObject2D::Render()
{
	if (m_kAnimation->m_bAniend)
	{
		m_pContext->PSSetShaderResources(0, 1, &m_kAnimation->GetTex()->m_pSRV);
		AnimTime += g_fSecPerFrame * 15;
		if (AnimTime > 1.0f)
		{
			m_kAnimation->UpdataFrameIng();
			AnimTime -= 1.0f;
		}
		if (m_kAnimation->AniEnd()) m_kAnimation->m_bAniend = false;
	}
	else 
	{
		m_pContext->PSSetShaderResources(0, 1, &m_kAnimation->GetTex()->m_pSRV);
		AnimTime += g_fSecPerFrame * 20;
		if (AnimTime > 1.0f)
		{
			m_kAnimation->UpdataFrame();
			AnimTime -= 1.0f;
		}
	}

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

bool KNpcObject2D::Logic()
{
	
	return false;
}

bool KNpcObject2D::Release()
{
	return false;
}
