#include "stdafx.h"
#include "limit_value_test.h"

void limit_value_test()
{
	//short int
	short int num_short_int_min = 0x7fff;
	short int num_short_int_mid = 0x0000;
	short int num_short_int_max = 0x8000;
	unsigned short int num_unsigned_short_int_max = 0xffff;
	cout<<"num_short_int_min = "<<num_short_int_min<<endl;
	cout<<"num_short_int_mid = "<<num_short_int_mid<<endl;
	cout<<"num_short_int_max = "<<num_short_int_max<<endl;
	cout<<"num_unsigned_short_int_max = "<<num_unsigned_short_int_max<<endl;
	
	//int
	int num_int_min = 0x7fffffff;
	int num_int_mid = 0;
	int num_int_max = 0x80000000;
	unsigned int num_unsigned_int_max = 0xffffffff;
	cout<<"num_int_min = "<<num_int_min<<endl;
	cout<<"num_int_mid = "<<num_int_mid<<endl;
	cout<<"num_int_max = "<<num_int_max<<endl;
	cout<<"num_unsigned_int_max = "<<num_unsigned_int_max<<endl;

	//
	return;
}