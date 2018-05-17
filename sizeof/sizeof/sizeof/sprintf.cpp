#include "stdafx.h"
#include "sprintf.h"

void sprintf_test()
{
	char sprintf_buffer[50];
	//类似于printf，将数据以设定的format形式存储在sprint_buffer中，返回的值是存储的字符数；
	int rtn_num = sprintf(sprintf_buffer, "%d", 123456);

	cout<<"Sprintf = "<<rtn_num<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[0]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[1]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[2]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[3]<<endl;
	cout<<"Sprintf = "<<sprintf_buffer[4]<<endl;

	if(-1)
	{
		cout<<"if -1也能执行"<<endl;
	}
	if(0)
	{
		cout<<"if 0也能执行"<<endl;
	}

	return ;
}