#include "KOdbc.h"



bool KOdbc::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return FALSE;
	}

	
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS) // 3.8
	{
		return FALSE;
	}

	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return FALSE;
	}

	return TRUE;
}

bool KOdbc::Connect(int iType, const TCHAR* c)
{
	TCHAR InCon[256] = { 0, };
	SQLRETURN ret;
	switch (iType)
	{
	case 0:
	{
		ret = SQLDriverConnect(m_hDbc, NULL,
			(SQLWCHAR*)L"Driver={SQL Server};SERVER=localhost, 1433; DATABASE=KGames; UID=koras; PWD=ale@dma37", SQL_NTS,
			NULL, 1024, NULL, SQL_DRIVER_NOPROMPT);
	}break;

	case 1:
	{
		HWND hWnd = GetDesktopWindow();
		SQLSMALLINT len;
		ret = SQLDriverConnect(m_hDbc, hWnd,
			(SQLWCHAR*)L"Driver={SQL Server}", SQL_NTS,
			(SQLWCHAR*)InCon, _countof(InCon),
			&len, SQL_DRIVER_PROMPT);
	}break;
	}


	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return FALSE;
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hTmt) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

bool KOdbc::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hTmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}

bool KOdbc::ExecSelect(const TCHAR* sql)
{
	SQLRETURN ret;

	SQLLEN Lint, lUserid, lUserpw, IAccount, ILogin, ILogout;



	ret = SQLBindCol(m_hTmt, 1, SQL_C_ULONG, &m_hInt, 0, &Lint);
	ret = SQLBindCol(m_hTmt, 2, SQL_UNICODE, m_wUser, sizeof(m_wUser), &lUserid);
	ret = SQLBindCol(m_hTmt, 3, SQL_UNICODE, m_wUserPw, sizeof(m_wUserPw), &lUserpw);
	ret = SQLBindCol(m_hTmt, 4, SQL_UNICODE, m_wAccount, sizeof(m_wAccount), &IAccount);
	ret = SQLBindCol(m_hTmt, 5, SQL_UNICODE, m_wLogin, sizeof(m_wLogin), &ILogin);
	ret = SQLBindCol(m_hTmt, 6, SQL_UNICODE, m_wLogout, sizeof(m_wLogout), &ILogout);


	TCHAR sql4[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql4, L"AllDataSelect");//select * from gameuser");
	ret = SQLExecDirect(m_hTmt, (SQLTCHAR*)sql, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return FALSE;
	}
	while (SQLFetch(m_hTmt) != SQL_NO_DATA)
	{
		std::wcout << "index : " << m_hInt << "\tUserId : " << m_wUser << "\tAccount : " << m_wAccount << "\nLogin : " << m_wLogin << "\tLogout : " << m_wLogout << std::endl;
		std::wcout << "------------------------------------------------------------------------------------------------\n";
		memset(m_wUser, 0, sizeof(SQLWCHAR) * 256);
		memset(m_wUserPw, 0, sizeof(SQLWCHAR) * 256);
		memset(m_wAccount, 0, sizeof(SQLWCHAR) * 256);
		memset(m_wLogin, 0, sizeof(SQLWCHAR) * 256);
		memset(m_wLogout, 0, sizeof(SQLWCHAR) * 256);
	}


	SQLCloseCursor(m_hTmt);
	return true;
}

bool KOdbc::ExecInsert(const TCHAR* sql, TCHAR* id, TCHAR* pw)
{
	SQLRETURN retcode;
	SWORD sReturn1 = 0;
	TCHAR callsp[256] = { 0, };
	wsprintf(callsp, sql);
	retcode = SQLPrepare(m_hTmt, callsp, SQL_NTS);
	SQLLEN cbRetParam1 = SQL_NTS;
	retcode = SQLBindParameter(m_hTmt, 1, SQL_PARAM_OUTPUT,
		SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn1, 0, &cbRetParam1);

	SQLBindParameter(m_hTmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 20, 0, (SQLWCHAR*)id, sizeof((SQLWCHAR*)id), NULL);

	SQLBindParameter(m_hTmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 20, 0, (SQLWCHAR*)pw, sizeof((SQLWCHAR*)pw), NULL);
	retcode = SQLExecute(m_hTmt);							
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return false;
	}
	while (SQLMoreResults(m_hTmt) != SQL_NO_DATA);
	SQLFreeStmt(m_hTmt, SQL_UNBIND);
	SQLFreeStmt(m_hTmt, SQL_RESET_PARAMS);
	SQLCloseCursor(m_hTmt);
	return false;
}

bool KOdbc::ExecQuery(const TCHAR* sql)
{
	SQLRETURN ret;
	TCHAR sql4[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql4, sql);
	ret = SQLExecDirect(m_hTmt, (SQLTCHAR*)&sql4, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return FALSE;
	}


	SQLCloseCursor(m_hTmt);

	return true;
}

void KOdbc::Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(m_hEnv, m_hDbc,
		m_hTmt,
		szSQLState,
		&iSQLCode,
		errorBuffer,
		sizeof(errorBuffer),
		&length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
