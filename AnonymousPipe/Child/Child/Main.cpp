#include "child_head.h"

int main(void)
{
	ChildView cv;
	cv.InitPipe();
	printf("\n*******\nabcd\n");    // ������������ܵ�
	int n = 10;
	while (n--)
	{
		cv.Read_pipe();

		cv.Write_pipe();
	}
	system("pause");
	return 0;
}