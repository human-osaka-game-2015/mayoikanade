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

	//�����̃\�P�b�g�A�h���X(IPv4)
	SOCKADDR_IN saddr;

	//����̃\�P�b�g�A�h���X(IPv4)
	SOCKADDR_IN from;

	//�|�[�g�ԍ�
	u_short uport;

public:
	SOCKET listen_s, s;

	Server(char* portnum);
	void Clientlisten();
	void recvData(char* data, int len);
	void sendData(char* data, int len);
	~Server();
};