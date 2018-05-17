// ptr_function.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "compare.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	double a;
	double b;
	cin>>a;
	cin>>b;
	compare_function(&a,&b);
	return 0;
}

