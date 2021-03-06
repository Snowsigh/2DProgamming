#pragma once
#include "KShaderMgr.h"
#include "KTextureMgr.h"
#include "KDxState.h"
#include <d3dcompiler.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#pragma comment (lib, "d3dcompiler.lib")

struct SimpleVertex
{
	KVector2 v;
	KVector2 t;
};
enum KCollisionType
{
	Block = 0,
	Overlap,
	Ignore,
};
enum KSelectType
{
	Select_Block = 0,
	Select_Overlap,
	Select_Ignore,
};
// 0001  - 기본
// 0010  - 권총
// 0100  - 장총
// 1000  - 수류탄

// 0111 = 7(속성)
// 1111 = 15
enum KSelectState
{
	T_DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
	T_HOVER = 1,	// 커서가 위에 있을 때
	T_FOCUS = 2,	// T_ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
	T_ACTIVE = 4,	// 마우스 왼쪽 버튼 누르고 있을 때
	T_SELECTED = 8, // T_ACTIVE 상태에서 왼쪼버튼 놓았을 때
};
class KBaseObject
{
public:
	bool		m_bDead;
	int			m_iCollisionID;
	int			m_iSelectID;
	float		m_fSpeed;
	KVector2	m_vPos;
	KVector2	m_vDirection;
	float		m_fWidth;
	float		m_fHeight;
	KRect		m_rtCollision;
	DWORD		m_dwCollisonType;
	DWORD		m_dwSelectType;
	DWORD		m_dwSelectState;
	DWORD		m_dwPreSelectState;
	bool		m_bSelect;
	bool		m_bAlphaBlend = true;
public:
	virtual void	HitOverlap(KBaseObject* pObj, DWORD dwState);
	virtual void	HitSelect(KBaseObject* pObj, DWORD dwState);
	virtual void	SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisonType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:

	KBaseObject()
	{
		m_bDead = false;
		m_bSelect = false;
		m_dwSelectState = T_DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_vDirection.x = 0.0f;
		m_vDirection.y = 0.0f;
		m_dwCollisonType = KCollisionType::Overlap;
		m_dwSelectType = KCollisionType::Overlap;
	}
};
struct KIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};

struct KConstantData
{
	KVector4 Color;
	KVector4 Timer;
};

class KDxObject : public KBaseObject
{
public:
	KTexture* m_pColorTex = nullptr;
	KTexture* m_pMaskTex = nullptr;
	KShader* m_pVShader = nullptr;
	KShader* m_pPShader = nullptr;
public:
	ID3D11BlendState* m_AlphaBlend;
	ID3D11BlendState* m_AlphaBlendDisable;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;

	std::vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;

	KConstantData    m_ConstantList;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;
public:
	void    SetDevice(ID3D11Device* m_pd3dDevice,
		ID3D11DeviceContext* m_pContext);
	virtual bool    LoadTexture(const TCHAR* szColorFileName,
		const TCHAR* szMaskFileName);
	virtual bool    SetVertexData();
	virtual bool    SetIndexData();
	virtual bool    SetConstantData();
	virtual bool	Create(ID3D11Device* m_pd3dDevice,
		ID3D11DeviceContext* m_pContext,
		const TCHAR* szShaderFileName = nullptr,
		const TCHAR* szTextureFileName = nullptr,
		const TCHAR* szMaskFileName = nullptr);
	virtual bool	CreateVertexBuffer();
	virtual bool    CreateIndexBuffer();
	virtual bool	CreateConstantBuffer();
	virtual bool    CreateVertexShader(const TCHAR* szFile);
	virtual bool    CreatePixelShader(const TCHAR* szFile);
	virtual bool    CreateInputLayout();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	KDxObject();
	~KDxObject();
};

