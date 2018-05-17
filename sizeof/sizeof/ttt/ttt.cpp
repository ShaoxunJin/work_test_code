// ttt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CENTERING_SYSTEM_CLASS.h"
#include "SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS.h"
#include "smee.h"
#include "smee_station.h"
#include "smee_type.h"
#include "smee_unit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace _WU;
	/*CENTERING_SYSTEM_CLASS<int,int> *xx = new CENTERING_SYSTEM_CLASS<int,int>("");*/
	CENTERING_SYSTEM_CLASS<int,int> *xx = new CENTERING_SYSTEM_CLASS<int,int>("prealinger");
	std::cout<<xx->get_name()<<std::endl;

	system("pause");
	return 0;
}

