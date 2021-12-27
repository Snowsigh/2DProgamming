#pragma once
#include "KInput.h"
#include "KViewRT.h"
class KDevice 
{
public:
	ID3D11Device* m_pd3dDevice;		// 디바이스 객체
	IDXGISwapChain* m_pSwapChain;		// 스왑체인 객체
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰
	D3D11_VIEWPORT			m_ViewPort;			// 뷰포트 
	D3D_DRIVER_TYPE         m_driverType;		// 디바이스 타입( 디폴트:하드웨어 가속 )
	IDXGIFactory* m_pGIFactory;		// DXGI 객체
	ID3D11DeviceContext* m_pImmediateContext;// 디바이스 컨텍스트
	D3D_DRIVER_TYPE			m_DriverType;		// 디바이스 타입
	D3D_FEATURE_LEVEL       m_FeatureLevel;		// DirectX의 기능수준
	ID3D11DepthStencilView* m_pDepthStencilView; // depth
	ID3D11DepthStencilState* m_pDsvState; // depth
public:
	KViewDs m_DefaultDS;
	KViewRT m_DefaultRT;
public:
	void DX_CHECK(HRESULT hr, const TCHAR* funtion);
	HRESULT	CreateDevice();
	HRESULT CreateGIFactory();
	HRESULT CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);
	HRESULT	SetRenderTargetView();
	HRESULT	SetViewPort();
public:
	bool CleanupDevice();
	bool SetDevice();
public:
	HRESULT SetDepthStencilView();
public:
	KDevice(void);
	virtual ~KDevice(void);

	

};

