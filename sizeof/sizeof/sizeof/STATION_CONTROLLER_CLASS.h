#ifndef _STATION_CONTROLLER_CLASS_H_
#define _STATION_CONTROLLER_CLASS_H_

#include "boost/make_shared.hpp"
#include "MACHINE_CONSTANT_CLASS.h"
#include "EXCEPTION_CLASS.h"

/******************************************************************
工位控制类：
工位的交接方式的控制？？？
******************************************************************/
namespace WRH
{
	class STATION_CONTROLLER_CLASS
	{
	public:
		STATION_CONTROLLER_CLASS();
		~STATION_CONTROLLER_CLASS();

	public:
		void initialize_models();
		void reset_models();
		void create_all_models();
		void delete_all_models();
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_station_mode(WR4T_STATION_MODEL_ENUM station);

		WR4T_ARM_STATION_ENUM convert(char name);

	private:
		void create_station_model(WR4T_STATION_MODEL_ENUM station);

		map<WR4T_STATION_MODEL_ENUM, boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>> m_station_model_map;
	};
}

#endif