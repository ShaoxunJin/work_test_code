// 20140731_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int Add(int a,int b)
{
	return a+b;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int a,b,num;
	printf("hello\n");
	a = 1;
	b = 2;
	printf("%d+%d=%d\n",a,b,Add(a,b));
	printf("sizeof_int=%d Byte\n",sizeof(int));
	printf("sizeof_char=%d Byte\n",sizeof(char));
	printf("sizeof_float=%d Byte\n",sizeof(float));
	printf("sizeof_double=%d Byte\n",sizeof(double));
	return 0;
}

