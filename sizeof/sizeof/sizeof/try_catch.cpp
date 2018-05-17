#include "stdafx.h"
#include "try_catch.h"

void try_catch()
{
	try
	{
		if(true)
		{
			throw "try_trigger";
		}
	}
	catch (const char *s)
	{
		cout<<s<<endl;
		cout<<"catch success!"<<endl;
	}
}

void throw_int(int i_throw_nbr) throw(int)
{
	//如果throw的是int 则会正常进行捕捉
	//函数后面的申明只是为了说明 实际上是根据throw中的内容而定
	//throw(i_throw_nbr);
	
	throw("jin");
}