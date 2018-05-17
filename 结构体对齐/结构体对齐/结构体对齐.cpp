// 结构体对齐.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//定义结构体
struct example_1
{
	char a;
	int b;
	char c;
};
struct example_2
{
	char a;
	//int filler;
	short int b;
	struct example_1 test;
	//double c;	
};
int _tmain(int argc, _TCHAR* argv[])
{	
	char a1;
	int b1;
	double c1;
	printf("The sizeof char is %d\n",sizeof(a1));
	printf("The sizeof int is %d\n",sizeof(b1));
	printf("The sizeof double is %d\n",sizeof(c1));
	//printf("The sizeof example_1 is %d",sizeof(b));
	//printf("The sizeof example_1 is %d",sizeof(c));
	printf("The sizeof example_1 is %d\n",sizeof(example_1));
	printf("The sizeof example_2 is %d",sizeof(example_2));
	return 0;
}

