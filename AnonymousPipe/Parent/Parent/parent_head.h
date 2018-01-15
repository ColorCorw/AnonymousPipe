#pragma once

#include <iostream>
#include <windows.h>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;


class ParentView
{
public:
	ParentView()   // ���캯����ʼ�����
	{
		read1 = NULL;
		read2 = NULL;
		write1 = NULL;
		write2 = NULL;
		std_write = NULL;
	}
	void CreateATTRIBUTES(); // ������ȫ����
	void PipeCreate();   // �����ܵ�
	void Pipe_Read();    // д�ܵ�
	void Pipe_Write();	 // ���ܵ�
						 // ������������
	char Writes[4096];  // д��ȥ
	char Reads[4096];   // ������
private:
	HANDLE read1;    // �ܵ�1 �����
	HANDLE read2;    // �ܵ�2 �����
	HANDLE write1;   // �ܵ�1 д���
	HANDLE write2;   // �ܵ�2 д���
	HANDLE std_write;
	SECURITY_ATTRIBUTES sa; // �ܵ��İ�ȫ����
};

