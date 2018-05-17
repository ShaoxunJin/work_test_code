// abs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include<iostream>
using namespace std;

static int is_equal(double a, double b)
{
	if(abs(a-b)< 4.450147717014403e-308)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	double a,b;
	cin>>a;
	cin>>b;
	cout<<is_equal(a,b)<<endl;
	cout<<"Power = "<<pow(a,b)<<endl;
	system("pause");
	return 0;
}

