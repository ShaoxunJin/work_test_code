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
	//���throw����int ����������в�׽
	//�������������ֻ��Ϊ��˵�� ʵ�����Ǹ���throw�е����ݶ���
	//throw(i_throw_nbr);
	
	throw("jin");
}