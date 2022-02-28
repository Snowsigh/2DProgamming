#include "KShaderMgr.h"

bool KShader::CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry)
{
	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		NULL,
		NULL,
		entry.c_str(),
		"vs_5_0",
		0,
		0,
		&m_pVSCodeResult,
		&m_pErrorMsgs
	);
	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)m_pErrorMsgs->GetBufferPointer(),
			"ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = pd3dDevice->CreateVertexShader(
		m_pVSCodeResult->GetBufferPointer(),
		m_pVSCodeResult->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool KShader::CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry)
{
	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		NULL,
		NULL,
		entry.c_str(),
		"ps_5_0",
		0,
		0,
		&m_pPsCodeResult,
		&m_pErrorMsgs
	);
	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)m_pErrorMsgs->GetBufferPointer(),
			"ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = pd3dDevice->CreatePixelShader(
		m_pPsCodeResult->GetBufferPointer(),
		m_pPsCodeResult->GetBufferSize(),
		NULL,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool KShader::Init()
{
	return false;
}

bool KShader::Frame()
{
	return false;
}

bool KShader::Render()
{
	return false;
}

bool KShader::Release()
{
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	return true;
}

bool KShader::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	if (!CreateVertexShader(pd3dDevice, filename))
	{
		return false;
	}
	if (!CreatePixelShader(pd3dDevice, filename))
	{
		return false;
	}
	return true;
}

KShader::KShader()
{
}

KShader::~KShader()
{
}

KShader* KShaderMgr::CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry)
{
	std::wstring name = Splitpath(filename, to_mw(entry));
	KShader* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	pData = new KShader;
	if (!pData->CreateVertexShader(pd3dDevice, filename, entry))
	{
		delete pData;
		return nullptr;
	}
	pData->m_csName = name;
	m_list.insert(make_pair(pData->m_csName, pData));
	m_iIndex++;
	return pData;
}

KShader* KShaderMgr::CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry)
{
	std::wstring name = Splitpath(filename, to_mw(entry));
	KShader* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	pData = new KShader;
	if (!pData->CreatePixelShader(pd3dDevice, filename, entry))
	{
		delete pData;
		return nullptr;
	}
	pData->m_csName = name;
	m_list.insert(make_pair(pData->m_csName, pData));
	m_iIndex++;
	return pData;
}
KShaderMgr::KShaderMgr()
{
	m_iIndex = 0;
}

KShaderMgr::~KShaderMgr()
{
	Release();
}
