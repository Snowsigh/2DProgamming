#include "KTextureMgr.h"

bool KTexture::Init()
{
	return false;
}

bool KTexture::Frame()
{
	return false;
}

bool KTexture::Render()
{
	return false;
}

bool KTexture::Release()
{
	if (m_pTexture) m_pTexture->Release();
	if (m_pSRV) m_pSRV->Release();
	return true;
}

bool KTexture::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	HRESULT hr = DirectX::CreateDDSTextureFromFile(
		pd3dDevice,
		filename.c_str(),
		(ID3D11Resource**)&m_pTexture,
		&m_pSRV);
	if (FAILED(hr))
	{
		hr = DirectX::CreateWICTextureFromFile(
			pd3dDevice,
			filename.c_str(),
			(ID3D11Resource**)&m_pTexture,
			&m_pSRV);
		if (FAILED(hr))
		{
			return false;
		}
	}
	m_pTexture->GetDesc(&m_TextureDesc);
	return true;
}

KTexture::KTexture()
{
}

KTexture::~KTexture()
{
}
