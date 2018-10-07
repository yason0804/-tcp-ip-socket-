/*********** SocketServer.cpp : �������TCP/IPЭ���Socketͨ��--�ͻ���Socket ***********/


//#include "stdafx.h"
#include <stdio.h>
#include "conio.h"
#include "windows.h"

#include "winsock.h"
#pragma comment(lib,"ws2_32.lib")

void TCPClient()
{
	//����socket
	SOCKET sockclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sockclient)
	{
		return;
	}

	//�������������׽��ֵ�ַ
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5678);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.6.1");//����ip10.120.43.144

	int iRetVal = connect(sockclient, (struct sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == iRetVal)
	{
		printf("Client:����������ʧ�ܣ�");
		closesocket(sockclient);
		return;
	}
	printf("Client:���������ӳɹ���\n");

	//��������
	CHAR szSend[100] = "hello��I am client.";   
	send(sockclient, szSend, sizeof(szSend), 0);  

	//��������											
	CHAR szRecv[100] = { 0 };
	recv(sockclient, szRecv, 100, 0); 
	printf("Client���յ���%s\n", szRecv);

	closesocket(sockclient);
}


int main(int argc, char* argv[])
{
	//��ʼ��socket��
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	TCPClient();
	
	WSACleanup();
	getch();

	return 0;
}