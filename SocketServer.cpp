/*********** SocketServer.cpp : �������TCP/IPЭ���Socketͨ��--�����Socket ***********/


//#include "stdafx.h"
#include <stdio.h>
#include "conio.h"
#include "windows.h"

#include "winsock.h" //socketͷ�ļ�
#pragma comment(lib,"ws2_32.lib") //socket���lib

void TCPServer()
{
	//�������������׽���socket������TCPЭ��
	SOCKET socksvr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == socksvr)
	{
		return;
	}

	//�������������׽��ֵ�ַ
	struct sockaddr_in svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(5678);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	//�����������׽�������������׽��ֵ�ַ��
	bind(socksvr, (struct sockaddr *)&svraddr, sizeof(svraddr));
																
	//����˼���
	listen(socksvr, SOMAXCONN);						   
	printf("Server:�Ⱥ�ͻ���.......\n");

	//�����ͻ����׽��ֵ�ַ
	struct sockaddr_in clientaddr = { 0 };
	int nLen = sizeof(clientaddr);

	//�������Ӻ���
	SOCKET sockclient = accept(socksvr, (struct sockaddr*)&clientaddr, &nLen);
	printf("Server:�ͻ���������\n");
	
	//����˽�������
	CHAR szText[100] = { 0 };
	recv(sockclient, szText, 100, 0); 
	printf("Server���յ���%s\n", szText);

	//����˷���
	CHAR szSend[100] = "Hello! I am Server.";
	send(sockclient, szSend, sizeof(szSend), 0);
												
	closesocket(sockclient);
	closesocket(socksvr);

}


int main(int argc, char* argv[])
{
	//��ʼ��socket��
	WSADATA wsa = { 0 }; 
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	TCPServer();
	
	WSACleanup();
	getch();

	return 0;
}