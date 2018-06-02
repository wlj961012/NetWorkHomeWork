#pragma once  
#include<iostream>  
using namespace std;
#define MAX_PACK_SIZE  10240   //���ݰ��ĳ���  
#define MAX_FILE_NAME_LENGTH 256  //�ļ����ĳ���  
#define INVALID_MSG -1       //��Ч����Ϣ  
#define MSG_FILE_LENGTH 1    //�ļ�����  
#define MSG_FILE_NAME 2    //�ļ���  
#define MSG_FILE   4     //�ļ�����  
#define MSG_READY   3     //׼������Ϣ  
#define MSG_SEND_FILE 5  //�����ļ�  
#define MSG_DOWNLOAD_FILE 6  //�����ļ�  
#define MSG_COMPLETE 7     //�����Ϣ  
class Message
{
public:
	struct MsgHead     //ͷ��Ϣ  
	{
		int msgId;    //��Ϣ��ʶ  
		MsgHead(int msg = INVALID_MSG) :msgId(msg) {};
	};
	struct MsgFileLength :public MsgHead
	{
		_int64 fileLength;   //�ļ�����  
		MsgFileLength() :MsgHead(MSG_FILE_LENGTH) {}
	};
	struct MsgFileName :public MsgHead
	{
		char fileName[MAX_FILE_NAME_LENGTH];
		MsgFileName() :MsgHead(MSG_FILE_NAME) {}
	};
	struct MsgFile :public MsgHead
	{
		MsgFile() :MsgHead(MSG_FILE) {}
	};
	struct MsgReady :public MsgHead        //׼������Ϣ  
	{
		MsgReady() :MsgHead(MSG_READY) {}
	};
	struct MsgSendFile :public MsgHead  //�����ļ���Ϣ  
	{
		MsgSendFile() :MsgHead(MSG_SEND_FILE) {}
	};
	struct MsgDownLoadFile :public MsgHead     //�����ļ���Ϣ  
	{
		MsgDownLoadFile() :MsgHead(MSG_DOWNLOAD_FILE) {}
	};
	struct MsgComplete :public MsgHead
	{
		MsgComplete() :MsgHead(MSG_COMPLETE) {}
	};
};