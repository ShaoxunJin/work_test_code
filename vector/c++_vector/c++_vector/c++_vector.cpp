// c++_vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//int i

int _tmain(int argc, _TCHAR* argv[])
{
	//int a[10];
	//vector<int> vec(ia, ia+10);
	/*
	const int element_size = 10;
	int a[element_size] = {1,5,100,9,65,32,68,51,26,32};
	vector<int> ivector(a,a+10);
	int ia[element_size];

	for(int ix =0; ix < element_size; ix++)
	{
		ia[ix] = ivector[ix];
		cout<<"ia["<<ix<<"] = "<<ia[ix]<<endl;
	}
	cout<<"ivector.begin = "<<*ivector.begin()<<endl;
	cout<<"ivector.end = "<<*(ivector.end()-1)<<endl;

	cout<<"ivector.size = "<<ivector.size()<<endl;
	cout<<"ivector.capacity = "<<ivector.capacity()<<endl;
	*/


	vector<int> ivec;
	cout<<"ivec_size = "<<ivec.size()<<"   ivec_capacity = "<<ivec.capacity()<<endl;

	for(int ix = 0; ix < 24 ; ix++)
	{
		ivec.push_back(ix);
		cout<<"ivec_size = "<<ivec.size()<<"  ivec_capacity = "<<ivec.capacity()<<endl;
	}


	return 0;
}

