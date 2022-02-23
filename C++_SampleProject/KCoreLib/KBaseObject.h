#pragma once
#include "KStd.h"
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
// 0001  - �⺻
// 0010  - ����
// 0100  - ����
// 1000  - ����ź

// 0111 = 7(�Ӽ�)
// 1111 = 15
enum KSelectState
{
	T_DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
	T_HOVER = 1,	// Ŀ���� ���� ���� ��
	T_FOCUS = 2,	// T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
	T_ACTIVE = 4,	// ���콺 ���� ��ư ������ ���� ��
	T_SELECTED = 8, // T_ACTIVE ���¿��� ���ɹ�ư ������ ��
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
	bool		m_bSelect;
	bool		m_bAlphaBlend = true;
public:
	virtual void	HitOverlap(KBaseObject* pObj, DWORD dwState);
	virtual void	HitSelect(KBaseObject* pObj, DWORD dwState);
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
class KDxObject : public KBaseObject
{
public:

public:
	ID3D11ShaderResourceView* m_pSRV0;
	ID3D11Texture2D* m_pTexture0;
	ID3D11ShaderResourceView* m_pSRV1;
	ID3D11Texture2D* m_pTexture1;
	ID3D11BlendState* m_AlphaBlend;
	ID3D11BlendState* m_AlphaBlendDisable;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;

	ID3DBlob* m_pVSCodeResult = nullptr;
	ID3DBlob* m_pErrorMsgs = nullptr;
	ID3DBlob* m_pPSCodeResult = nullptr;
public:

	void    SetDevice(ID3D11Device* m_pd3dDevice,
		ID3D11DeviceContext* m_pContext);
	virtual bool    LoadTexture(const TCHAR* szColorFileName,
		const TCHAR* szMaskFileName);
	virtual bool    SetVertexData();
	virtual bool	Create(ID3D11Device* m_pd3dDevice,
		ID3D11DeviceContext* m_pContext,
		const TCHAR* szTextureFileName = nullptr,
		const TCHAR* szMaskFileName = nullptr);
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	KDxObject();
	~KDxObject();
};
