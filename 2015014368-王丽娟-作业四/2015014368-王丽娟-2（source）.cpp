#include "stdafx.h"
#pragma once  
#include<iostream>  
#include<vector>  
#include<io.h>  
#include<string>  
#include"source.h"  
using namespace std;
void Source::GetFiles(string path, string ext, vector<string> &files)
{
	long hFile = 0;    //�ļ����  
	_finddata_t fileInfo; //�ļ���Ϣ  
	string pathName;
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) != -1) //�ж�·���Ƿ���Ч����ȡ��һ���ļ�  
	{
		do
		{
			if (fileInfo.attrib & _A_SUBDIR)   //��������ļ���  
			{
				if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
				{
					GetFiles(pathName.assign(path).append("\\").append(fileInfo.name), ext, files);
				}
			}
			else
			{
				string filePath;
				filePath = pathName.assign(path).append("\\").append(fileInfo.name);
				char fileDrive[_MAX_DRIVE];
				char fileDir[_MAX_DIR];
				char fileName[_MAX_FNAME];
				char fileExt[_MAX_EXT];
				_splitpath(filePath.c_str(), fileDrive, fileDir, fileName, fileExt);  //�ֽ�·����ȡ������·���ļ�����׺  
				if (strcmp(fileExt, ext.c_str()) == 0)
				{
					files.push_back(filePath);
				}
			}
		} while (_findnext(hFile, &fileInfo) == 0);
		_findclose(hFile);
	}
}