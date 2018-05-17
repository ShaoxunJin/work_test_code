#include "stdafx.h"
#include "STATION_MODEL_ABSTRACT_INTERFACE.h"

namespace WRH
{
	STATION_MODEL_ABSTRACT_INTERFACE::STATION_MODEL_ABSTRACT_INTERFACE()
	{
		this->m_configurations = new WRMC_STATION_PARAMTER_STRUCT();
	}

	STATION_MODEL_ABSTRACT_INTERFACE::~STATION_MODEL_ABSTRACT_INTERFACE()
	{
		delete this->m_configurations;
	}
	
	void STATION_MODEL_ABSTRACT_INTERFACE::reset_configuration(WRMC_STATION_PARAMTER_STRUCT configuration)
	{
		memcpy(this->m_configurations, &configuration, sizeof(WRMC_STATION_PARAMTER_STRUCT));
		this->m_slot = configuration.max_slot;
		this->m_work_speed = configuration.speed;
	}

	void STATION_MODEL_ABSTRACT_INTERFACE::set_config_slot(int slot)
	{
		this->m_slot = slot;
	}
	int STATION_MODEL_ABSTRACT_INTERFACE::get_config_slot()
	{
		return this->m_slot;
	}

	void STATION_MODEL_ABSTRACT_INTERFACE::set_work_speed(WRMC_SPEED_LEVEL_ENUM speed)
	{
		this->m_work_speed = speed;
	}
	WRMC_SPEED_LEVEL_ENUM STATION_MODEL_ABSTRACT_INTERFACE::get_work_speed()
	{
		return this->m_work_speed;
	}

	//void STATION_MODEL_ABSTRACT_INTERFACE::set_station_name(WR4T_STATION_MODEL_ENUM t)
	//{
	//	this->m_station_name = t;
	//}

	//WR4T_STATION_MODEL_ENUM STATION_MODEL_ABSTRACT_INTERFACE::get_station_name()
	//{
	//	return this->m_station_name;
	//}
}