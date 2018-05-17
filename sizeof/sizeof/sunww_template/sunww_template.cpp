// sunww_template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS.h"
#include "CENTERING_SYSTEM_CLASS.h"

int _tmain(int argc, _TCHAR* argv[])
{

	using namespace _WU;
	CENTERING_SYSTEM_CLASS<int,int> *xx = new CENTERING_SYSTEM_CLASS<int,int>("Prealign!");
	std::cout<<xx->get_name()<<std::endl;

	system("pause");
	return 0;
}

