#pragma once  
#include<iostream>  
#include<WinSock2.h>  
#include"message.h"  
#pragma comment(lib,"Ws2_32.lib")  
#define PORT 10000  
using namespace std;
class Server
{
public:
	SOCKET sd;
	_int64 fileLength;
	char fileName[MAX_FILE_NAME_LENGTH];
	bool InitSock();    //初始winsocket  
	SOCKET BindListen();  //绑定监听套接字  
	SOCKET AcceptConnection(SOCKET sd);  //接收客户端  
	bool ProcessConnection(SOCKET sd);  //传送数据  
	bool ReceiveFile(SOCKET sd);     //接收文件内容  
	bool RecvFileName(SOCKET sd);     //接收文件名  
	bool GetAndSendFileLength(SOCKET sd);    //获取文件长度  
	bool SendFileName(SOCKET sd);    //发送文件名  
	bool SendFile(SOCKET sd);      //发送文件  
	void CloseSocket();   //关闭套接字  
};
