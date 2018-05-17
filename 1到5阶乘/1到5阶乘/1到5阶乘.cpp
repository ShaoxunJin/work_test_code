// 1µ½5½×³Ë.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

int func(int n)
{
	static int f = 1;
	f = f*n;
	return(f);
}
double calculate_pow(double m)
{
	double result;
	result = pow(2,(m));
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double i;
	for(i=1;i<5;i++)
	{
		printf("%d!=%d\n",i,func(i));
	}
	return 0;
}

