#pragma once
#include "KStd.h"
#include "KDevice.h"
#include "KTexture.h"

struct PNCT_VERTEX
{
	TVector3 pos;
	TVector3 normal;
	TVector4 color;
	TVector2 tex;
	PNCT_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
};


struct KB_Data
{
	TMatrix matWorld;
	TMatrix matView;
	TMatrix matProj;
	TMatrix matNormal;
	TVector4  vLightDir;
	TVector4 matTime;
};

class KModel
{
public:
	KB_Data m_kbData;
	UINT m_iNumIndex;
	KTexture m_kTex;
	
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	ID3D11Buffer* m_pConstantBuffer = nullptr;

	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;
	ID3D11PixelShader* m_pMainPS = nullptr;

	ID3DBlob* m_pVStemp = nullptr;

	std::vector<PNCT_VERTEX> m_VertexList;
	std::vector<DWORD> m_IndexList;
	ID3D11DeviceContext* m_pContext;

	TMatrix m_matWorld;
public:
	void		SetMatrix(TMatrix* pMatWorld,
		TMatrix* pMatView, TMatrix* pMatProj);
	virtual bool	CreateVertexData();
	virtual	bool CreateIndexData() ;
	virtual	HRESULT CreateIndexBuffer() ;

public:
	virtual	HRESULT	CreateVertexBuffer() ;
	virtual	HRESULT CreateConstantBuffer();
	virtual	HRESULT	LoadShaderAndInputLayout(LPCWSTR vsFile, LPCWSTR psFile);
	virtual	HRESULT LoadShader(LPCWSTR vsFile, LPCWSTR psFile);

	virtual	bool Create(ID3D11DeviceContext* pContext, LPCWSTR vsFile, LPCWSTR psFile);
	virtual bool Create(ID3D11DeviceContext* pContext, LPCWSTR vsFile, LPCWSTR psFile, LPCWSTR TexName);
	virtual	bool LoadObject(std::wstring filename);
public:
	static ID3DBlob* LoadShaderBlob(std::wstring vs, std::string function, std::string version);
	bool LoadTexture(LPCWSTR TexName);
public:

	virtual bool	 Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual	bool	Render();
	virtual bool	PostRender(UINT iNumIndex);

	virtual bool   Release();
	KModel();
	virtual ~KModel() {};
};

