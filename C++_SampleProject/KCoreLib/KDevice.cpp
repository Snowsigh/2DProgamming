#include "KDevice.h"

HRESULT KDevice::InitDeivice()
{
	HRESULT hr = S_OK;
	CreateDevice();
	CreateRenderTarget();
	CreateViewPort();
	return hr;
}

bool KDevice::CreateDevice()
{
	HRESULT hr;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_iWindowWidth;
	sd.BufferDesc.Height = m_iWindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		if (SUCCEEDED(hr = D3D11CreateDeviceAndSwapChain(
			NULL, m_DriverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd,
			&m_pSwapChain, &m_pd3dDevice, &m_FeatureLevel,
			&m_pImmediateContext)))
		{
			if (FAILED(hr) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if (m_pImmediateContext) m_pImmediateContext->Release();
				if (m_pd3dDevice) m_pd3dDevice->Release();
				continue;
			}
			break;
		}

	}
	if (FAILED(hr))
	{
		return false;
	}

	CreateRenderTarget();
	CreateViewPort();

	return true;
	
}

bool KDevice::CreateRenderTarget()
{
	HRESULT hr;
	//랜더타켓 생성
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		return hr;
	}
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	return true;
}

bool KDevice::CreateViewPort()
{
	//뷰포트 생성
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);
	m_ViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_ViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
	return true;
}

bool KDevice::CleanUpDevice()
{
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();

	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
	return true;
}
void KDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTargetView)m_pRenderTargetView->Release();

	HRESULT hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount,
		iWidth, iHeight,
		m_SwapChainDesc.BufferDesc.Format,
		m_SwapChainDesc.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_SwapChainDesc);

	}
	CreateRenderTarget();
	CreateViewPort();
}
KDevice::KDevice(void)
{
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
}

KDevice::~KDevice(void)
{
}
