#include "parent_head.h"


void ParentView::CreateATTRIBUTES()  // ���ùܵ���ȫ����
{
	sa.bInheritHandle = TRUE; // TRUEΪ�ܵ����Ա��ӽ������̳�  
	sa.lpSecurityDescriptor = NULL; // Ĭ��ΪNULL
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
}

void ParentView::PipeCreate()  // �����ܵ�
{
	// �����ܵ���д�������ȫ���ԡ����ܵ�����ֵ
	if (!CreatePipe(&read1, &write1, &sa, 0)) //�����ܵ�1,�˴�0����ܵ���������ΪϵͳĬ��ֵ
	{
		cout << "�������ܵ�ʧ�ܣ�" << endl;
		return;
	}
	/*
	if (!SetHandleInformation(read1, HANDLE_FLAG_INHERIT, 0))
	{
	cout << "read1���̳�" << endl;
	}*/
	if (!CreatePipe(&read2, &write2, &sa, 0)) //�����ܵ�2
	{
		cout << "�������ܵ�ʧ�ܣ�" << endl;
		return;
	}
	/*
	if (!SetHandleInformation(write2, HANDLE_FLAG_INHERIT, 0))
	{
	cout << "write2���̳�" << endl;
	}
	*/
	TCHAR szCmdline[] = TEXT("../../child/Debug/child.exe"); // �����ӽ���·��
	PROCESS_INFORMATION pi;  // ���������½��̵�ʶ����Ϣ
	STARTUPINFO si;  // ���ھ����½��̵������������ʾ
	BOOL bSuccess = FALSE;

	// ����PROCESS_INFORMATION
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));  // ��0����ڴ�����
												   // ����STARTUPINFO
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);  // �ṹ��С
								  //*************** ����̳�����******************
								  // �����������ܵ�
								  // �ܵ�1�ɸ����̶����ӽ���д
								  // �ܵ�2�ɸ�����д���ӽ��̶�
	si.hStdError = write1;        // ����������(��д�����д�ظ�����)
	si.hStdOutput = write1;       // �ӽ��̼̳йܵ�1д���
	si.hStdInput = read2;		  // �ӽ��̼̳йܵ�2�����
								  //*************** ����̳�����******************
	si.dwFlags |= STARTF_USESTDHANDLES;  // ʹ��hStdInput ��hStdOutput ��hStdError ��Ա   

										 // �����ӽ���
										 // ժ��msdn:
										 // If lpApplicationName is NULL, 
										 // the first white space�Cdelimited token of the command line specifies the module name. 
	bSuccess = CreateProcess(
		NULL,          // lpApplicationName
		szCmdline,     // command line 
					   // ���������ֶζ����Դ���Ŀ���ӽ���
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // bInheritHandles:ָʾ�½����Ƿ�ӵ��ý��̴��̳��˾��
		CREATE_NEW_CONSOLE,             // creation flags:ָ�����ӵġ���������������ͽ��̵Ĵ����ı�־��
					   // ����Ϊ CREATE_NEW_CONSOLE ����ʾ�Ӵ���
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&si,		   // STARTUPINFO :ָ��һ�����ھ����½��̵������������ʾ��STARTUPINFO�ṹ��
		&pi			   // PROCESS_INFORMATION :ָ��һ�����������½��̵�ʶ����Ϣ��PROCESS_INFORMATION�ṹ��
	);

	// If an error occurs, exit the application. 
	if (!bSuccess)
		cout << "�����ӳ���ʧ��" << endl;
	else
	{
		// �ر�һЩ�ӽ����õľ��
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(write1);
		CloseHandle(read2);
	}

}

void ParentView::Pipe_Read()
{

	DWORD dwRead, dwWrite;
	bool rsuccess = false;
	// ��ȡ��׼����������Ϊ���ý����dos������ʾ
	std_write = GetStdHandle(STD_OUTPUT_HANDLE);

	// ���������ȡ���顢������(�������С)��ʵ�ʶ�ȡ�ֽ�����OVERLAPPED:���һ�������˴�����ΪNULL
	rsuccess = ReadFile(read1, Reads, strlen(Writes), &dwRead, NULL);

	if (!rsuccess || dwRead == 0)cout << "���ܵ�ʧ��" << endl;
	rsuccess = WriteFile(std_write, Reads, dwRead, &dwWrite, NULL); // д����׼�������dos����
	if (!rsuccess)cout << "���ʧ��" << endl;

}

void ParentView::Pipe_Write()
{
	DWORD dwWrite; // ��¼DWORD��
	bool wsuccess = false;
	wsuccess = WriteFile(write2, Writes, strlen(Writes), &dwWrite, NULL);
	if (!wsuccess || dwWrite == 0)cout << "д�ܵ�ʧ��" << endl; // ���������ܵ���д����ӹܵ���д������  
}