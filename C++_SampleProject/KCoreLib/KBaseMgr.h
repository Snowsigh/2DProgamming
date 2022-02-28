#pragma once
#include "KStd.h"
template <class T, class S>
class KBaseMgr : public KSingleton<S>
{
public:
	friend class KSingleton<KBaseMgr>;
public:
	int		m_iIndex;
	ID3D11Device* m_pd3dDevice;
	std::map<std::wstring, T* >  m_list;
public:
	std::wstring Splitpath(std::wstring path, std::wstring entry);
	virtual void	Set(ID3D11Device* pd3dDevice)
	{
		m_pd3dDevice = pd3dDevice;
	}
	T* Load(std::wstring filename);
	T* GetPtr(std::wstring key);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	KBaseMgr();
public:
	~KBaseMgr();
};

template<class T, class S>
inline std::wstring KBaseMgr<T, S>::Splitpath(std::wstring path, std::wstring entry)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };

	std::wstring fullpathname = path;
	_tsplitpath_s(fullpathname.c_str(), Dirve, Dir, FileName, FileExt);
	std::wstring name = FileName;
	name += FileExt;
	if (entry.empty() == false)
	{
		name += entry;
	}
	return name;
}

template<class T, class S>
inline T* KBaseMgr<T, S>::Load(std::wstring filename)
{
	std::wstring name = Splitpath(filename, L"");
	T* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	pData = new T;
	if (pData->Load(m_pd3dDevice, filename) == false)
	{
		delete pData;
		return nullptr;
	}
	pData->m_csName = name;
	m_list.insert(make_pair(pData->m_csName, pData));
	m_iIndex++;
	return pData;
}

template<class T, class S>
inline T* KBaseMgr<T, S>::GetPtr(std::wstring key)
{
	auto iter = m_list.find(key);
	if (iter != m_list.end())
	{
		return (*iter).second;
	}
	return nullptr;
}

template<class T, class S>
inline bool KBaseMgr<T, S>::Init()
{
	return false;
}

template<class T, class S>
inline bool KBaseMgr<T, S>::Frame()
{
	return false;
}

template<class T, class S>
inline bool KBaseMgr<T, S>::Render()
{
	return false;
}

template<class T, class S>
inline bool KBaseMgr<T, S>::Release()
{
	for (auto data : m_list)
	{
		data.second->Release();
		delete data.second;
	}
	m_list.clear();
	return true;
}

template<class T, class S>
inline KBaseMgr<T, S>::KBaseMgr()
{
	m_iIndex = 0;
}

template<class T, class S>
inline KBaseMgr<T, S>::~KBaseMgr()
{
	Release();
}
