#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Ws2tcpip.h>
#include <ws2def.h>

class Server
{
private:
	WSADATA wsaData;

	//自分のソケットアドレス(IPv4)
	SOCKADDR_IN saddr;

	//相手のソケットアドレス(IPv4)
	SOCKADDR_IN from;

	//ポート番号
	u_short uport;

public:
	SOCKET listen_s, s;

	Server(char* portnum);
	void Clientlisten();
	void recvData(char* data, int len);
	void sendData(char* data, int len);
	~Server();
};