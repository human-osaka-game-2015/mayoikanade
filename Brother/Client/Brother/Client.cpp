#include "Client.h"
#include <windows.h>
Client::Client(char* portnum)
{
	//ポート番号の指定
	uport = atoi(portnum);

	//初期化時にバージョンを指定している。このバージョンはwinsock2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) 
	{
		MessageBox(NULL, "WSAStartup関数の失敗", NULL, MB_OK);
		WSACleanup();
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) 
	{
		MessageBox(NULL, "ソケットオープンエラー", NULL, MB_OK);
		WSACleanup();
	}


}

Client::~Client()
{
	//通信終了
	shutdown(s, SD_BOTH);
	closesocket(s);
	WSACleanup();
}

void Client::serverConnect(const char* IPAdd)
{
	lpHost = gethostbyname(IPAdd);
	if (lpHost == NULL) 
	{
		addr = inet_addr(IPAdd);
		lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
	}
	if (lpHost == NULL) 
	{
		MessageBox(NULL, "エラーです", NULL, MB_OK);
		closesocket(s);
		WSACleanup();
	}

	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = lpHost->h_addrtype;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = *((u_long *)lpHost->h_addr);

	if (connect(s, (SOCKADDR *)&saddr, sizeof(saddr)) == SOCKET_ERROR) 
	{
		MessageBox(NULL, "connect Error", NULL, MB_OK);
		closesocket(s);
		WSACleanup();
	}
}

void Client::sendData(char* data, int len)
{
	send(s, data, len, 0);
}

void Client::recvData(char* data, int len)
{
	recv(s, data, len, 0);
}