#include "KBaseObject.h"
#include "KObjectMgr.h"
void KBaseObject::HitOverlap(KBaseObject* pObj, DWORD dwState)
{
}

void KBaseObject::HitSelect(KBaseObject* pObj, DWORD dwState)
{
}

void KDxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}

bool KDxObject::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		m_pd3dDevice,
		szColorFileName,
		(ID3D11Resource**)&m_pTexture0,
		&m_pSRV0);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			m_pd3dDevice,
			szColorFileName,
			(ID3D11Resource**)&m_pTexture0,
			&m_pSRV0);
		if (FAILED(hr))
		{
			return false;
		}
	}
	m_pTexture0->GetDesc(&m_TextureDesc);

	hr = DirectX::CreateWICTextureFromFile(
		m_pd3dDevice,
		szMaskFileName,
		(ID3D11Resource**)&m_pTexture1,
		&m_pSRV1);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			m_pd3dDevice,
			szMaskFileName,
			(ID3D11Resource**)&m_pTexture0,
			&m_pSRV0);
		if (FAILED(hr))
		{
			return false;
		}
	}

	return true;
}

bool KDxObject::SetVertexData()
{
	return false;
}

bool KDxObject::Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, const TCHAR* szTextureFileName, const TCHAR* szMaskFileName)
{
	HRESULT hr;
	m_rtCollision = KRect(m_vPos, m_fWidth, m_fHeight);
	I_ObjectMgr.AddCollisionExecute(this,
		std::bind(&KBaseObject::HitOverlap, this,
			std::placeholders::_1,
			std::placeholders::_2));
	I_ObjectMgr.AddSelectExecute(this,
		std::bind(&KBaseObject::HitSelect, this,
			std::placeholders::_1,
			std::placeholders::_2));

	SetDevice(m_pd3dDevice, m_pContext);
	if (!LoadTexture(szTextureFileName, szMaskFileName))
	{
		return false;
	}
	if (!SetVertexData())
	{
		return false;
	}
	//gpu�޸𸮿� ���� �Ҵ�(���ϴ� �Ҵ� ũ��)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))
	{
		return false;
	}
	// ���׸�->��ƿ��Ƽ->txt���� �ۼ�
	// ���̴� ������->������Ʈ ������ ���ؼ� ���̴���ü ���� 

	hr = D3DCompileFromFile(
		L"VertexShader.txt",
		NULL,
		NULL,
		"VS",
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
	hr = m_pd3dDevice->CreateVertexShader(
		m_pVSCodeResult->GetBufferPointer(),
		m_pVSCodeResult->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}


	hr = D3DCompileFromFile(
		L"PixelShader.txt",
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		&m_pPSCodeResult,
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
	hr = m_pd3dDevice->CreatePixelShader(
		m_pPSCodeResult->GetBufferPointer(),
		m_pPSCodeResult->GetBufferSize(),
		NULL,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		return false;
	}
	// �������̴��� ����� ���ؼ� �������̾ƿ��� �����Ѵ�.	
	// ���������� �� ������ � ������ �������̴��� ������ �ų�
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32_FLOAT, 0,0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0,8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(
		layout,
		NumElements,
		m_pVSCodeResult->GetBufferPointer(),
		m_pVSCodeResult->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}

	// (�ҽ��÷�*D3D11_BLEND_SRC_ALPHA) 
	//                  + 
	// (����÷�*D3D11_BLEND_INV_SRC_ALPHA)
	// �÷�   =  �����÷��� = (1,1,1,1)
	// ����ũ =  1.0 - �����÷��� = (1,1,1,1)

	// FinalColor = SrcColor*SrcAlpha + DestColor*(1.0f- SrcAlpha) 	    
	// if SrcAlpha == 0 ��������
	//           FinalColor() = SrcColor*0 + DestColor*(1-0)
	//                FinalColor = DestColor;
	// if SrcAlpha == 1 ����������
	//           FinalColor() = SrcColor*1 + DestColor*(1-1)
	//                FinalColor = SrcColor;
	// ȥ�ջ��� = �ҽ�(���ݵ�ο찴ü �ȼ�) (����) ���(����� ��ü:�ȼ�)
	// ȥ�ջ��� = �ȼ����̴� ��� �÷�  (����:��Ģ����) ��¹����� �÷�
	D3D11_BLEND_DESC  blenddesc;
	ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
	/*bd.AlphaToCoverageEnable;
	bd.IndependentBlendEnable;*/
	blenddesc.RenderTarget[0].BlendEnable = TRUE;
	blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//// A ���� ����
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

bool KDxObject::Init()
{
	return false;
}

bool KDxObject::Frame()
{
	return false;
}

bool KDxObject::Render()
{
	m_pContext->PSSetShaderResources(0, 1, &m_pSRV0);
	m_pContext->PSSetShaderResources(1, 1, &m_pSRV1);
	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(m_AlphaBlend, 0, -1);
	}
	else
	{
		m_pContext->OMSetBlendState(m_AlphaBlendDisable, 0, -1);
	}

	m_pContext->IASetInputLayout(m_pVertexLayout);
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides = sizeof(SimpleVertex);
	UINT Offsets = 0;

	m_pContext->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer,
		&Strides, &Offsets);
	m_pContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		//D3D_PRIMITIVE_TOPOLOGY_POINTLIST
		//D3D_PRIMITIVE_TOPOLOGY_LINELIST
	);
	m_pContext->Draw(m_VertexList.size(), 0);
	return true;
}

bool KDxObject::Release()
{
	return false;
}

KDxObject::KDxObject()
{
}

KDxObject::~KDxObject()
{
}