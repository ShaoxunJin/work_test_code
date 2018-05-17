// template_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <typename type>
type min_calculate(type a, type b)
{
	return a < b ? a : b;
}

typedef struct
{}xxx;

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<min(10,20)<<endl;
	cout<<min(10.0,20.0)<<endl;
	cout<<"XXX_size = "<<sizeof(xxx)<<endl;
	system("pause");
	return 0;
}

