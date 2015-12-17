#include "Server.h"
#include <windows.h>

Server::Server(char* portnum)
{
	//ポート番号の指定
	uport = atoi(portnum);

	//初期化時にバージョンを指定している。このバージョンはwinsock2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		MessageBox(NULL, "WSAStartup関数の失敗", NULL, MB_OK);
		WSACleanup();
	}

	listen_s = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_s < 0) 
	{
		MessageBox(NULL, "ソケットオープンエラー", NULL, MB_OK);
		WSACleanup();
	}

	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listen_s, (struct sockaddr *)&saddr, sizeof(saddr)) == SOCKET_ERROR) 
	{
		MessageBox(NULL, "bind Error", NULL, MB_OK);

		closesocket(listen_s);
		WSACleanup();
	}
}

Server::~Server()
{
	shutdown(s, SD_BOTH);
	closesocket(s);
	WSACleanup();
}

void Server::Clientlisten()
{
	//待機状態を設定
	if (listen(listen_s, 0) == SOCKET_ERROR) 
	{
		MessageBox(NULL, "listen Error", NULL, MB_OK);
		closesocket(listen_s);
		WSACleanup();
	}

	int fromlen = (int)sizeof(from);
	
	s = accept(listen_s, (SOCKADDR *)&from, &fromlen);
	
	if (s == INVALID_SOCKET) 
	{
		MessageBox(NULL, "accept error", NULL, MB_OK);
		closesocket(listen_s);
		WSACleanup();
	}

	//リッスン・ソケットはもう不要
	closesocket(listen_s);
}

void Server::recvData(char* data,int len)
{
	int sizeR;
	sizeR = recv(s, data, len, 0);

}

void Server::sendData(char* data, int len)
{
	send(s, data, len, 0);
}