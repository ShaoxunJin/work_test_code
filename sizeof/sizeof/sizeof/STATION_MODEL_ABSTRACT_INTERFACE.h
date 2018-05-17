#ifndef STATION_MODEL_ABSTRACT_INTERFACE_H
#define STATION_MODEL_ABSTRACT_INTERFACE_H

#include "STATION_INTERFACE.h"
#include "WR4T_WORKFLOW_tc.h"
#include "WRMC_WORKFLOW_tc.h"

/*
工位抽象模型：
包括不同工位中的一些公有属性：机器常数配置、速度、工位名字；
后续不同工位继承于该类；
但是该类中的一些成员函数中的形参和机器常数重叠；
*/
namespace WRH
{

	class STATION_MODEL_ABSTRACT_INTERFACE : public STATION_INTERFACE
	{
	public:
		STATION_MODEL_ABSTRACT_INTERFACE();
		virtual ~STATION_MODEL_ABSTRACT_INTERFACE();

		void reset_configuration(WRMC_STATION_PARAMTER_STRUCT configuration);
		void set_config_slot(int slot);
		int get_config_slot();
		void set_work_speed(WRMC_SPEED_LEVEL_ENUM speed);
		WRMC_SPEED_LEVEL_ENUM get_work_speed();
		
		//void set_station_name(WR4T_STATION_MODEL_ENUM t);
		//WR4T_STATION_MODEL_ENUM get_station_name();

	protected:
		//WR4T_STATION_MODEL_ENUM m_station_name;
		WRMC_STATION_PARAMTER_STRUCT* m_configurations;
	private:
		int m_slot;
		WRMC_SPEED_LEVEL_ENUM m_work_speed;

	};
}


#endif