#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>
#include <istream>
#include <string>


class KOdbc
{
public:
	SQLHENV m_hEnv;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hTmt;
	SQLWCHAR m_wUser[256], m_wUserPw[256], m_wAccount[256], m_wLogin[256], m_wLogout[256];
	SQLINTEGER m_hInt;

public:
	KOdbc()
	{
	};
	~KOdbc()
	{
	};
public:
	bool Init();
	bool Connect(int iType, const TCHAR* c);
	bool Release();
	bool ExecSelect(const TCHAR* sql);
	bool ExecInsert(const TCHAR* sql, TCHAR* id, TCHAR* pw);
	bool ExecQuery(const TCHAR* sql);
	void Check();



};

