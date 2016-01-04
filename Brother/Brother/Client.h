#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Ws2tcpip.h>

class Client
{
private:
	SOCKET s;
	WSADATA wsaData;
	SOCKADDR_IN saddr;
	HOSTENT *lpHost;
	unsigned int addr;
	//ポート番号
	u_short uport;
	
public:
	Client(char* portnum);
	~Client();
	//引数にサーバーのIPアドレスを指定する。
	void serverConnect(const char* IPAdd);
	void sendData(char* data, int len);
	void recvData(char* data,int len);
};