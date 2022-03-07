#include "KWorld.h"
KWorld* KWorld::m_pWorld = nullptr;

bool KWorld::Load(std::wstring saveFile)
{
    return false;
}

bool KWorld::Init()
{
    return false;
}

bool KWorld::Frame()
{
	for (auto obj : m_UIobj)
	{
		KObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Frame();
		}
	}
	return true;
}

bool KWorld::Render()
{
	for (auto obj : m_UIobj)
	{
		KObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Render();
		}
	}
	return true;
}

bool KWorld::Release()
{
	for (auto obj : m_UIobj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_Itemobj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_Npcobj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_Mapobj)
	{
		obj.second->Release();
		delete obj.second;
	}
	m_UIobj.clear();
	m_Itemobj.clear();
	m_Npcobj.clear();
	m_Mapobj.clear();
	return true;
}
