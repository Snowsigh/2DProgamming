#pragma once
#include "KStd.h"
class KWrite
{
public:
	ID2D1Factory* m_pd2dFactory;
	IDWriteFactory* m_pdWriteFactory;
	ID2D1RenderTarget* m_pRT;// 3d ¿¬µ¿
	IDWriteTextFormat* m_pTextFormat;
	IDWriteTextFormat* m_pTextFormat50;
	ID2D1SolidColorBrush* m_pTextBrush;
public:
	HRESULT CreateDeviceResources(IDXGISurface1* pSurface);
	bool	DrawText(RECT rt, const TCHAR* text,
		D2D1::ColorF color, IDWriteTextFormat* pTextFormat = nullptr);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

};

