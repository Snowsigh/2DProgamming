#include <KServer.h>

int main()
{
	I_SERVER.Init(10000);
	I_SERVER.Run();
	/*DWORD ThreadId;
	HANDLE hThreadRecv = ::CreateThread(0, 0, I_SERVER., (LPVOID)&server, 0, &ThreadId);
	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread(0, 0, SendThread, (LPVOID)&server, 0, &ThreadIdSend);
	server.Run();
	server.Release();
	CloseHandle(hThreadRecv);
	CloseHandle(hThreadSend);*/

	return 0;
}