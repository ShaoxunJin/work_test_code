#include "stdafx.h"
#include "macro_test.h"

void macro_test_if_function()
{
	cout<<"This is for #if..."<<endl;
#if OK
	cout<<"Macro define OK is valid!"<<endl;
#else
	cout<<"Macro define OK is invalid !"<<endl;
#endif

//
//这里说明下：
//1、#ifdef 和 #if defined(xxx)是相同的，只不过后者可以采用&&多条件进行判断；
//2、#if 后面必须跟上常量，当#if后面是1则编译，如果不是1则不编译；
//3、一些设置是在编译选项中进行处理的；

	return;

}