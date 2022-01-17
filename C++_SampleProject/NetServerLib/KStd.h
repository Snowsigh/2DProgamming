#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include <list>
#include <iostream>
#include <process.h>
#include <vector>

#pragma comment	(lib, "ws2_32.lib")

template <class T> class KSingleton
{
public:
	static T& Get()
	{
		static T Instance;
		return Instance;
	}
};
template<typename T> class TCheck
{
public:
	bool operator() (T val) const
	{
		return (val->sock == m_iSock);
	}
	SOCKET m_iSock;
};


static void ERROR_MSG(const char* pMsg)
{
	void* lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	if (lpMsgBuf != nullptr)
	{
		std::string msg = (char*)lpMsgBuf;
		msg += std::to_string(WSAGetLastError());
		MessageBoxA(NULL, msg.c_str(), pMsg, MB_OK);
		LocalFree(lpMsgBuf);
	}
	return;
}

