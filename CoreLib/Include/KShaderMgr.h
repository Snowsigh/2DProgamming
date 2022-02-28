#pragma once
#include "KBaseMgr.h"
#include <d3dcompiler.h>
class KShader
{
public:
	int m_iIndex;
	std::wstring m_csName;
	std::wstring m_szMsg;
	TCHAR m_szBuffer[256];
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3DBlob* m_pVSCodeResult = nullptr;
	ID3DBlob* m_pErrorMsgs = nullptr;
	ID3DBlob* m_pPsCodeResult = nullptr;
public:
	virtual bool CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "VS");
	virtual bool CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "PS");
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	KShader();
	virtual	~KShader();
};
class KShaderMgr : public KBaseMgr<KShader, KShaderMgr>
{
	friend class KSingleton<KShaderMgr>;
public:
	KShader* CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
	KShader* CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
private:
	KShaderMgr();
public:
	~KShaderMgr();

};
#define I_Shader KShaderMgr::Get()

