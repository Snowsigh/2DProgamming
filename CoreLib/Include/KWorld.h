#pragma once
#include "KObject2D.h"
class KWorld
{
public:
	enum KWorldID
	{
		K_LOADING, K_LOGIN, K_LOBBY, K_ZONE, K_RESULT,
	};
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;
	bool m_bLoadzone = false;
public:
	static KWorld* m_pWorld;
	std::map<std::wstring, KObject2D*> m_UIobj;
	std::map<std::wstring, KObject2D*> m_Itemobj;
	std::map<std::wstring, KObject2D*> m_Npcobj;
	std::map<std::wstring, KObject2D*> m_Mapobj;
	using m_mapiter = std::map<std::wstring, KObject2D*>::iterator;
public:
	virtual bool	Load(std::wstring saveFile);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

