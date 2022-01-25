#include "KLobbyServer.h"

int main()
{
	KLobbyServer server;
	server.Init(10000);
	server.Run();
	server.Release();

	return 0;
}