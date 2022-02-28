#pragma once
#include "KBaseMgr.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#pragma comment (lib, "d3dcompiler.lib")
class KTexture
{
public:
	int				m_iIndex;
	std::wstring	m_csName;
	std::wstring	m_szMsg;
	TCHAR			m_szBuffer[256];
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_pSRV;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	KTexture();
	virtual ~KTexture();
};
class KTextureMgr : public KBaseMgr<KTexture, KTextureMgr>
{
	friend class KSingleton<KTextureMgr>;
private:
	KTextureMgr() {};
public:
	~KTextureMgr() {};
};
#define I_Texture KTextureMgr::Get()
