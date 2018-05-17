// 1到5阶乘.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

int func(int n)
{
	static int f = 1;
	f = f*n;
	return(f);
}

int calculate_pow(double a,double b)
{
	int result;
	result = int(pow(a,b));
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double a,b;
	printf("Please input the parameter of a & b\n");
	scanf("%lf%lf",&a,&b);

	printf("result = %d",calculate_pow(a,b));
	return 0;
}
//注意在写程序过程中输入和输出的变量一定要保持一致；