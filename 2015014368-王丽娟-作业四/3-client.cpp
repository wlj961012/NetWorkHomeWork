#include "stdafx.h"  
#include <WinSock2.h> //windows socket的头文件  
#include <Windows.h>  
#include <iostream>  
#include <thread>  
#include <process.h>  
#pragma comment(lib, "ws2_32.lib") //连接winsock2.h的静态库文件  
using namespace std;

int main()
{
	//加载winsock库  
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 3), &wsadata);

	//客户端socket  
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//初始化socket信息  
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(2017);
	//建立连接  
	connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));

	cout << "已建立连接。" << endl;
	while (true) {
		char* s = new char[100];
		cout << "请输入你要发送的文字消息: ";
		cin >> s;
		send(clientSock, s, strlen(s) * sizeof(char) + 1, NULL);
		cout << "已发送:" << s << endl;
		char Buffer[MAXBYTE] = { 0 };
		recv(clientSock, Buffer, MAXBYTE, 0);
		cout << "通过端口:" << ntohs(clientAddr.sin_port) << "接收到:" << Buffer << endl;
	}
	closesocket(clientSock);
	WSACleanup();
	cout << "客户端连接已关闭。" << endl;
	system("pause");
	return 0;
}

