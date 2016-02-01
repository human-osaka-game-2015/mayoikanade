#include "Client.h"
#include <windows.h>



Client::Client(char* portnum)
{
	//�|�[�g�ԍ��̎w��
	uport = atoi(portnum);

	//���������Ƀo�[�W�������w�肵�Ă���B���̃o�[�W������winsock2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) 
	{
		MessageBox(NULL, "WSAStartup�֐��̎��s", NULL, MB_OK);
		WSACleanup();
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) 
	{
		MessageBox(NULL, "�\�P�b�g�I�[�v���G���[", NULL, MB_OK);
		WSACleanup();
	}


}

Client::~Client()
{
	//�ʐM�I��
	shutdown(s, SD_BOTH);
	closesocket(s);
	WSACleanup();
}

void Client::serverConnect(const char* IPAdd)
{
	//lpHost = gethostbyname(IPAdd);
	lpHost = gethostbyname(IPAdd);

	if (lpHost == NULL) 
	{
		addr = inet_addr(IPAdd);
		lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
	}
	if (lpHost == NULL) 
	{
		MessageBox(NULL, "�G���[�ł�", NULL, MB_OK);
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