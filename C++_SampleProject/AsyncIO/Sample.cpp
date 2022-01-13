#include <Windows.h>
#include <iostream>

DWORD SectorsPerCluster;
DWORD BytesPerSecotr;
DWORD NumberOfFreeCluseters;
DWORD TotalNumberOfClusters;

void main()
{
	WCHAR lpRootPathName[] = L"E:\\";
	GetDiskFreeSpace(lpRootPathName,
		&SectorsPerCluster,
		&BytesPerSecotr,
		&NumberOfFreeCluseters,
		&TotalNumberOfClusters);
	setlocale(LC_ALL, "KOREAN");

	WCHAR* g_buffer = NULL;
	LARGE_INTEGER filesize;
	OVERLAPPED g_ReadOV = { 0, };
	OVERLAPPED g_WriteOV = { 0, };
	{
		HANDLE hFileAsync = CreateFile(L"DXSDK_Jun10.exe",
			GENERIC_READ | GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED |
			FILE_FLAG_NO_BUFFERING,
			NULL);
		if (hFileAsync != INVALID_HANDLE_VALUE)
		{
			GetFileSizeEx(hFileAsync, &filesize);
			DWORD dwSize = 0;
			if (filesize.QuadPart % BytesPerSecotr != 0)
			{
				dwSize = filesize.QuadPart / BytesPerSecotr;
				dwSize = (dwSize + 1) * BytesPerSecotr;
			}
			g_buffer = new WCHAR[filesize.QuadPart];
			DWORD dwRead;
			DWORD dwWritten;
			BOOL ret = ReadFile(hFileAsync, g_buffer, dwSize, &dwRead, &g_ReadOV);
			BOOL bPanding = FALSE;
			if (ret == FALSE)
			{
				DWORD dwError = GetLastError();
				if (dwError == ERROR_IO_PENDING)
				{
					std::wcout << L"로드 중";
					bPanding = TRUE;
				}
				else
				{
					std::wcout << L"로드 실패";
					bPanding = FALSE;
				}
			}
			else
			{
				std::wcout << L"로드 완료";

			}
			DWORD dwTarns = 0;
			BOOL bReturn;
			while (bPanding)
			{
				bReturn = GetOverlappedResult(hFileAsync, &g_ReadOV, &dwTarns, FALSE);
				if (bReturn == TRUE)
				{
					std::wcout << L"로드 완료";
					bPanding = FALSE;
				}
				else
				{
					DWORD dwError = GetLastError();
					if (dwError == ERROR_IO_INCOMPLETE)
					{
						std::wcout << L"Complete";
					}
					else
					{
						std::wcout << L"실패";
						bPanding = FALSE;
					}
				}
				Sleep(1000);
			}
		}
		CloseHandle(hFileAsync);
	}


}
