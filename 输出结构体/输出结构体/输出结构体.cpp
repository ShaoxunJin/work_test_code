// 输出结构体.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct
{
	char *name;
	int age;
}stu;


int _tmain(int argc, _TCHAR* argv[])
{
	stu a;
	a.age = 19;
	a.name = "jinsahoxun";
	printf("name=%s age=%d",a.name,a.age);
	return 0;
}

