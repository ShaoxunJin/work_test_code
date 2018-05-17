#include "stdafx.h"
#include "endian_test.h"
//extern int g_int;

//little: 高字节放置在低地址 
//低字节放在高地址
//0x1234 0x12放置在低地址，因为这里的0x12是高字节
//注意这里是short int
void endian_test()
{
	printf("Begin to test little or big endian\n");
	
	UNOIN_TEST union_test;
	union_test.b = 1;

	if(1 == (int)union_test.a)
	{
		cout<<"Little Endian"<<endl;
	}
	else
	{
		cout<<"Big Endian"<<endl;
	}

	cout<<"End to test endian"<<endl;
	cout<<"global_int = "<<g_int<<endl;
	return;
}

//大小端测试
void endian_test_1(void)
{
	short int endian_i = 0x1122;	
	//char lower_byte = ((char*)&endian_i)[0];//先取址 通过指针类型将int型转换为char
	//char high_byte = ((char*)&endian_i)[1];
	char *lower_byte = (char *)&endian_i;
	char *high_byte = (char *)(&endian_i + 1);
	if(0x22 == *lower_byte)
	{
		cout<<"lower_byte = "<<*lower_byte<<endl;
		cout<<"Little Endian"<<endl;
	}
	else
	{
		cout<<"high_byte = "<<*high_byte<<endl;
		cout<<"Big Endian"<<endl;
	}

	return;
}