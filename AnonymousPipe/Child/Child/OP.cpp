#include "child_head.h"

void ChildView::InitPipe()
{
	read = GetStdHandle(STD_INPUT_HANDLE); // �̳о��
	write = GetStdHandle(STD_OUTPUT_HANDLE);
	if ((read == INVALID_HANDLE_VALUE) || (write == INVALID_HANDLE_VALUE))
		cout << "�̳о����Ч" << endl;
}

void ChildView::Read_pipe()
{
	DWORD dwRead;
	bool rsuccess = false;
	rsuccess = ReadFile(read, Readss, sizeof(Readss), &dwRead, NULL);	//ʹ�ñ�׼������(�������ܵ������)��ȡ����  
	int sum = 0;
	int k = 0;
	k = Bitadd(Readss, Writess, dwRead - 2, k);  // ��2ԭ��  ȥ��ĩβ'/','0'
	Writess[k++] = '\n';
	Writess[k++] = '\r';
	Writess[k] = '\0';
}

void ChildView::Write_pipe()
{
	DWORD dwWrite;
	bool wsuccess = false;
	wsuccess = WriteFile(write, Writess, strlen(Writess), &dwWrite, NULL);
	if (!wsuccess)cout << "���ʧ��" << endl;//ʹ�ñ�׼������(�������ܵ�д���)д������  
}
