#include "stdafx.h"
#include "ascci_convert.h"

int ascci_to_int(const char t)
{
	return (int)t;
}

void int_to_asccit(int i)
{
	cout<<__FUNCTION__<<":"<<(char)i<<endl;
}


void ascci_operation_main()
{
	cout<<"ascci_to_int : "<<ascci_to_int('H')<<endl;
	int tt = ascci_to_int('H');
	//tt += (tt<<8);
	cout<<"ascci_to_int : "<<tt<<endl;

	int_to_asccit(tt);

}