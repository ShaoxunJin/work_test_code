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
//����˵���£�
//1��#ifdef �� #if defined(xxx)����ͬ�ģ�ֻ�������߿��Բ���&&�����������жϣ�
//2��#if ���������ϳ�������#if������1����룬�������1�򲻱��룻
//3��һЩ�������ڱ���ѡ���н��д���ģ�

	return;

}