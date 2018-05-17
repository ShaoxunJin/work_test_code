// calculate_arrary_length.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {1,2,3};
	char *b = "jinshaoxun";
	cout<<"The size of a = "<<sizeof(a)<<endl;
	cout<<"The size of int = "<<sizeof(int)<<endl;
	cout<<"The length of a[] = "<<sizeof(a)/sizeof(int)<<endl;
	cout<<b<<endl;
	cout<<"The length of string "<<b<<" = "<<strlen(b)<<endl;
	return 0;
}

