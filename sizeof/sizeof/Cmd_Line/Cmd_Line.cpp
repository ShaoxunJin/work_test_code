// Cmd_Line.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <istream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

//int _tmain(int argc, _TCHAR* argv[])
//char* argv[];ָ���ַ�����ָ������ ֱ��argv[i]�������Ǳ��ַ���������

int _tmain(int argc, char* argv[])
{
	cout<<"argc = "<<argc<<endl;
	for (int i = 0; i < argc; ++i)
	{
		cout<<"argc["<<i<<"] :"<<argv[i]<<endl;
	}
	return 0;
}

