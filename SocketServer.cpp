/*********** SocketServer.cpp : 定义基于TCP/IP协议的Socket通信--服务端Socket ***********/


//#include "stdafx.h"
#include <stdio.h>
#include "conio.h"
#include "windows.h"

#include "winsock.h" //socket头文件
#pragma comment(lib,"ws2_32.lib") //socket库的lib

void TCPServer()
{
	//创建服务器端套接字socket，基于TCP协议
	SOCKET socksvr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == socksvr)
	{
		return;
	}

	//建立服务器端套接字地址
	struct sockaddr_in svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(5678);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	//将服务器端套接字与服务器端套接字地址绑定
	bind(socksvr, (struct sockaddr *)&svraddr, sizeof(svraddr));
																
	//服务端监听
	listen(socksvr, SOMAXCONN);						   
	printf("Server:等候客户端.......\n");

	//建立客户端套接字地址
	struct sockaddr_in clientaddr = { 0 };
	int nLen = sizeof(clientaddr);

	//建立连接函数
	SOCKET sockclient = accept(socksvr, (struct sockaddr*)&clientaddr, &nLen);
	printf("Server:客户端已连接\n");
	
	//服务端接收内容
	CHAR szText[100] = { 0 };
	recv(sockclient, szText, 100, 0); 
	printf("Server接收到：%s\n", szText);

	//服务端发送
	CHAR szSend[100] = "Hello! I am Server.";
	send(sockclient, szSend, sizeof(szSend), 0);
												
	closesocket(sockclient);
	closesocket(socksvr);

}


int main(int argc, char* argv[])
{
	//初始化socket库
	WSADATA wsa = { 0 }; 
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	TCPServer();
	
	WSACleanup();
	getch();

	return 0;
}