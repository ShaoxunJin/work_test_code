#include "stdafx.h"
#include "ROBOT_HARDWARE_SERVICE_CLASS.h"

#include "boost/shared_ptr.hpp"
#include "head_file.h"

namespace WRH
{
	ROBOT_HARDWARE_SERVICE_CLASS::ROBOT_HARDWARE_SERVICE_CLASS()
	{
		cout<<"Construct : "<<typeid(ROBOT_HARDWARE_SERVICE_CLASS()).name()<<endl;
	}
	ROBOT_HARDWARE_SERVICE_CLASS::~ROBOT_HARDWARE_SERVICE_CLASS()
	{
		cout<<"Destruct : "<<typeid(ROBOT_HARDWARE_SERVICE_CLASS()).name()<<endl;
	}

	void ROBOT_HARDWARE_SERVICE_CLASS::get_wafer(int station, int slot, bool *present)
	{
		*present = SMEE_TRUE;
		cout<<"ROBOT_HARDWARE_SERVICE_CLASS::get_wafer......"<<endl;
	}

	void ROBOT_HARDWARE_SERVICE_CLASS::move_to_retract(int station, int slot)
	{
		cout<<"move_to_retract....."<<endl;
	}
	
	void ROBOT_HARDWARE_SERVICE_CLASS::put_wafer(int station, int slot, bool *present)
	{
		cout<<"ROBOT_HARDWARE_SERVICE_CLASS::put_wafer......"<<endl;
	}

	void ROBOT_HARDWARE_SERVICE_CLASS::swap_pin(int station, int first_arm, int next_arm, int slot)
	{
		cout<<"ROBOT_HARDWARE_SERVICE_CLASS::swap_pin......"<<endl;
	}

	void ROBOT_HARDWARE_SERVICE_CLASS::swap_pickup(int station, int first_arm, int next_arm, int slot)
	{
		cout<<"ROBOT_HARDWARE_SERVICE_CLASS::swap_pickup......"<<endl;
	}

}