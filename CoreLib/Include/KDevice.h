#pragma once
#include "KWindow.h"
class KDevice : public KWindow
{
public:
	ID3D11Device* m_pd3dDevice;		// 디바이스 객체	
	ID3D11DeviceContext* m_pImmediateContext;// 디바이스 컨텍스트 객체
	IDXGISwapChain* m_pSwapChain;		// 스왑체인 객체		
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰 객체

	D3D_DRIVER_TYPE			m_DriverType;		// 디바이스 타입 속성값
	D3D_FEATURE_LEVEL       m_FeatureLevel;		// Direct3D 특성레벨 속성값
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// 스왑체인 속성값 
	D3D11_VIEWPORT			m_ViewPort;			// 뷰 포트 속성값


public:
	bool		CreateDevice();
	bool		CreateRenderTarget();
	bool		CreateViewPort();
	bool		CleanUpDevice();
	KDevice();
	~KDevice();
};

