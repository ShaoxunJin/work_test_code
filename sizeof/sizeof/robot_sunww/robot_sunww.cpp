// robot_sunww.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "exchange_class.h"
#include "any_class.h"

using namespace _SUNWW;
using namespace std;

void any_function(any any_num);

int _tmain(int argc, _TCHAR* argv[])
{

	int error_code = 0;

	_WU::EXCHANGE_CLASS* exchange = new _WU::EXCHANGE_CLASS();
	error_code = exchange->prepare_exchange(_WU::EXCHANGE_MODE_PICKUP);

	SMEE_BOOL end = true;
	try
	{
		do
		{
			std::cout << "step continue\n"<<std::endl;

		}while (end != exchange->handle_exchange());
	}
	catch (const char* e)
	{
		std::cout << e <<std::endl;
	}

	//any any_num_int = 10;

	//cout<<"any_num_int = "<< <<any_cast<double>(any_num_int)<<endl;
	char *name = "jisahoxun";
	//int name[3] = {1,2,3};

	any_function(name);

	system("pause");
	return error_code;

}

void any_function(any any_num)
{
	char* num;
	num = any_cast<char *>(any_num);
	cout<<"num = "<<num<<endl;
}