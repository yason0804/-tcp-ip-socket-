/*********** SocketServer.cpp : 定义基于TCP/IP协议的Socket通信--客户端Socket ***********/


//#include "stdafx.h"
#include <stdio.h>
#include "conio.h"
#include "windows.h"

#include "winsock.h"
#pragma comment(lib,"ws2_32.lib")

void TCPClient()
{
	//创建socket
	SOCKET sockclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sockclient)
	{
		return;
	}

	//建立服务器端套接字地址
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5678);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.6.1");//本机ip10.120.43.144

	int iRetVal = connect(sockclient, (struct sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == iRetVal)
	{
		printf("Client:服务器连接失败！");
		closesocket(sockclient);
		return;
	}
	printf("Client:服务器连接成功！\n");

	//发送数据
	CHAR szSend[100] = "hello！I am client.";   
	send(sockclient, szSend, sizeof(szSend), 0);  

	//接收数据											
	CHAR szRecv[100] = { 0 };
	recv(sockclient, szRecv, 100, 0); 
	printf("Client接收到：%s\n", szRecv);

	closesocket(sockclient);
}


int main(int argc, char* argv[])
{
	//初始化socket库
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	TCPClient();
	
	WSACleanup();
	getch();

	return 0;
}