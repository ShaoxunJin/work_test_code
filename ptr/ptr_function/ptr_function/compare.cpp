#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

int compare_function(double *a, double *b)
{
	double result;
	result = *a > *b ? *a:*b;
	cout<<"The result = "<<result<<endl;
	return 0;
}