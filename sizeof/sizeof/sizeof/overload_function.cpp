#include "stdafx.h"
#include "overload_function.h"
#include "head_file.h"

int overload_function_test(int i /* = 0 */)
{
	if(i != 0)
	{
		cout<<"success"<<endl;
		return 1;
	}
	else if(i == 0)
	{
		cout<<"failed"<<endl;
		return 0;
	}
	else
	{

	}
}