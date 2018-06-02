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
	bool InitSock();    //��ʼwinsocket  
	SOCKET BindListen();  //�󶨼����׽���  
	SOCKET AcceptConnection(SOCKET sd);  //���տͻ���  
	bool ProcessConnection(SOCKET sd);  //��������  
	bool ReceiveFile(SOCKET sd);     //�����ļ�����  
	bool RecvFileName(SOCKET sd);     //�����ļ���  
	bool GetAndSendFileLength(SOCKET sd);    //��ȡ�ļ�����  
	bool SendFileName(SOCKET sd);    //�����ļ���  
	bool SendFile(SOCKET sd);      //�����ļ�  
	void CloseSocket();   //�ر��׽���  
};
