#include "stdafx.h"
#include "sprintf.h"

void sprintf_test()
{
	char sprintf_buffer[50];
	//������printf�����������趨��format��ʽ�洢��sprint_buffer�У����ص�ֵ�Ǵ洢���ַ�����
	int rtn_num = sprintf(sprintf_buffer, "%d", 123456);

	cout<<"Sprintf = "<<rtn_num<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[0]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[1]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[2]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[3]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[4]<<endl;

	if(-1)
	{
		cout<<"if -1Ҳ��ִ��"<<endl;
	}
	if(0)
	{
		cout<<"if 0Ҳ��ִ��"<<endl;
	}

	return ;
}