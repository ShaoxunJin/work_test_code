#include "stdafx.h"
#include "format_test.h"

void Difference_r_n()
{
	cout<<"测试回车和回车换行的区别"<<endl;
	cout<<"这是回车换行\n"<<endl;	//回车换行之后下面会空一行
	cout<<"这是回车\r"<<endl;
	cout<<"end"<<endl;
}