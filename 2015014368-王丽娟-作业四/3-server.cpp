#include "stdafx.h"  
#include <WinSock2.h> //windows socket的头文件  
#include <Windows.h>  
#include <iostream>  
#include <thread>  
#include <mutex>  
#include <process.h> 
#include<cstring>
#include<string>
#pragma comment(lib, "ws2_32.lib") //连接winsock2.h的静态库文件  
using namespace std;  
typedef struct my_file
{
	SOCKET clientSocket; //文件内部包含了一个SOCKET 用于和客户端进行通信  
	sockaddr_in clientAddr; //用于保存客户端的socket地址  
	int id; //文件块的序号  
}F;
string buf1="", buf2="";
HANDLE hsem1, hsem2;
DWORD WINAPI transmmit1(const LPVOID arg)
{ 
	while (true) {
		F *temp = (F*)arg;
		std::cout << "测试开始,等待客户端发送消息..." << endl;
		char Buffer[MAXBYTE] = { 0 }; //缓冲区  
		recv(temp->clientSocket, Buffer, MAXBYTE, 0); //recv方法 从客户端通过clientScocket接收  
		std::cout << "线程" << temp->id << "从客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口收到:" << Buffer << endl;  
		WaitForSingleObject(hsem1, INFINITE);
		buf1 = Buffer;
		if (buf2 != "") {
			const char* s = buf2.c_str();
			send(temp->clientSocket, s, strlen(s) * sizeof(char) + 1, NULL);
			std::cout << "线程" << temp->id << "通过客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口发送:" << s << endl;
		}
		else {
			const char* s = "";
			send(temp->clientSocket, s, strlen(s) * sizeof(char) + 1, NULL);
			std::cout << "线程" << temp->id << "通过客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口发送:" << s << endl;
		}
		buf2 = "";
		ReleaseSemaphore(hsem2, 1, NULL);
	}
	return 0;
}
DWORD WINAPI transmmit2(const LPVOID arg)
{
	while (true) {
		F *temp = (F*)arg;
		std::cout << "测试开始,等待客户端发送消息..." << endl;
		char Buffer[MAXBYTE] = { 0 }; //缓冲区  
		recv(temp->clientSocket, Buffer, MAXBYTE, 0); //recv方法 从客户端通过clientScocket接收  
		std::cout << "线程" << temp->id << "从客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口收到:" << Buffer << endl;
		WaitForSingleObject(hsem2, INFINITE);
		buf2 = Buffer;
		if (buf1 != "") {
			const char* s = buf1.c_str();
			send(temp->clientSocket, s, strlen(s) * sizeof(char) + 1, NULL);
			std::cout << "线程" << temp->id << "通过客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口发送:" << s << endl;
		}
		else {
			const char* s ="";
			send(temp->clientSocket, s, strlen(s) * sizeof(char) + 1, NULL);
			std::cout << "线程" << temp->id << "通过客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口发送:" << s << endl;
		}
		buf1 = "";
		ReleaseSemaphore(hsem1, 1, NULL);
	}
	return 0;
}
int main()
{
	WSADATA wsaData;  
	WSAStartup(MAKEWORD(2, 3), &wsaData);  
	SOCKET servSocket = socket(AF_INET, SOCK_STREAM, 0); 
	sockaddr_in servAddr;  
	memset(&servAddr, 0, sizeof(SOCKADDR));   
	servAddr.sin_family = PF_INET;   
	servAddr.sin_port = htons(2017); 
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	::bind(servSocket, (SOCKADDR *)&servAddr, sizeof(SOCKADDR));  
	HANDLE hThread[2];   
	listen(servSocket, 20);
	int i = 0;
	F* temp1;
	F* temp2;
	hsem1 = CreateSemaphore(NULL, 1, 1, NULL);
	hsem2 = CreateSemaphore(NULL, 0, 1, NULL);
	while(true)
	{
		if (i == 0) {
			temp1 = new F;
			sockaddr_in clntAddr;
			int nSize = sizeof(SOCKADDR);
			SOCKET clientSock = accept(servSocket, (SOCKADDR*)&clntAddr, &nSize);
			temp1->clientSocket = clientSock;
			temp1->id = i + 1;
			temp1->clientAddr = clntAddr;
			hThread[i] = CreateThread(NULL, 0, &transmmit1, temp1, 0, NULL);
		}
		if(i==1){
			temp2 = new F;
			sockaddr_in clntAddr;
			int nSize = sizeof(SOCKADDR);
			SOCKET clientSock = accept(servSocket, (SOCKADDR*)&clntAddr, &nSize);
			temp2->clientSocket = clientSock;
			temp2->id = i + 1;
			temp2->clientAddr = clntAddr;
			hThread[i] = CreateThread(NULL, 0, &transmmit2, temp2, 0, NULL);
		}
		i++;
		
	} 
	WaitForMultipleObjects(20, hThread, TRUE, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hsem1);
	CloseHandle(hsem2);
	std::cout << WSAGetLastError() << endl; 
	closesocket(servSocket);
	WSACleanup();
	std::cout << "服务器连接已关闭。" << endl;
	std::system("pause");
	return 0;
}

