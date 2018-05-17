#include "stdafx.h"
#include "count_if.h"
#include <math.h>
#include <algorithm>
#include <functional>

void count_if_test(void)
{
	int A[] = {2,0,4,6,0,3,1,-7};
	const int N = sizeof(A)/sizeof(int);
	cout<<"sizeof Arrary A = "<<sizeof(A)<<endl;
	int count_if_num = 0;
	count_if_num = count_if(A, A+N, bind2nd(greater<int>(), 2));
	cout<<"count_if_num"<<count_if_num<<endl;
	return;
}