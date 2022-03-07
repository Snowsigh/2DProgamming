#pragma once
#include "KStd.h"
class KDxState
{
public:
public:
	static ID3D11BlendState* m_AlphaBlend;
	static ID3D11BlendState* m_AlphaBlendDisable;
	static ID3D11SamplerState* m_pSamplerState;

public:
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};