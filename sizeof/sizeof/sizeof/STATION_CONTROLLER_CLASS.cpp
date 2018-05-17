#include "stdafx.h"

#include "STATION_CONTROLLER_CLASS.h"


namespace WRH
{
	STATION_CONTROLLER_CLASS::STATION_CONTROLLER_CLASS()
	{

	}

	STATION_CONTROLLER_CLASS::~STATION_CONTROLLER_CLASS()
	{

	}

	//对station_interface和station_parameter reset
	//重新配置 WRMC中的一些机器常数
	//先create then initialize 因此这里的m_station_model_map会在前面一步骤中进行处理
	void STATION_CONTROLLER_CLASS::initialize_models()
	{
		MACHINE_CONSTANT_CLASS* config = MACHINE_CONSTANT_CLASS::get_instance();
		WRMC_STATION_PARAMTER_STRUCT station_mc = WRMC_STATION_PARAMTER_STRUCT();
		map<WR4T_STATION_MODEL_ENUM, boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>>::iterator iter = this->m_station_model_map.begin();
		while (iter != this->m_station_model_map.end())
		{
			if (config->get_station_config(iter->first) != NULL)
			{
				//从机器常数中获取机器常数
				memcpy((void*)&station_mc, config->get_station_config(iter->first), sizeof(WRMC_STATION_PARAMTER_STRUCT));
				//iter->second->reset_model();
				iter->second->reset_configuration(station_mc);
				try
				{
					iter->second->register_station_name(WZ4A_2_INCH, this->convert(station_mc.station_name.size_2.upper_arm_name));
					iter->second->register_station_name(WZ4A_3_INCH, this->convert(station_mc.station_name.size_3.upper_arm_name));
					iter->second->register_station_name(WZ4A_4_INCH, this->convert(station_mc.station_name.size_4.upper_arm_name));
					iter->second->register_station_name(WZ4A_5_INCH, this->convert(station_mc.station_name.size_5.upper_arm_name));
				}
				catch (char* e)
				{
					
				}
				if (station_mc.parameters.get.use_get_mode)
				{
					iter->second->register_exchange_type(WR4T_EXCHANGE_TYPE_GET);
				}
				if (station_mc.parameters.put.use_put_mode)
				{
					iter->second->register_exchange_type(WR4T_EXCHANGE_TYPE_PUT);
				}
				if (station_mc.parameters.pickup.use_pickup_mode)
				{
					iter->second->register_exchange_type(WR4T_EXCHANGE_TYPE_MOVE_TO_EXCHANGE);
				}
				if (station_mc.parameters.swap_putget.use_swap_putget_mode)
				{
					iter->second->register_exchange_type(WR4T_EXCHANGE_TYPE_SWAP_PUT_GET);
				}
				if (station_mc.parameters.swap_pickup.use_swap_pickup_mode)
				{
					iter->second->register_exchange_type(WR4T_EXCHANGE_TYPE_SWAP_PICKUP);
				}
			}

			iter++;
		}

	}

	void STATION_CONTROLLER_CLASS::reset_models()
	{
		this->m_station_model_map.clear();
	}

	void STATION_CONTROLLER_CLASS::create_all_models()
	{
		cout<<"STATION_CONTROLLER_CLASS::create_all_models() >>>>"<<endl;
		MACHINE_CONSTANT_CLASS* config = MACHINE_CONSTANT_CLASS::get_instance();
		if (config->get_mc()->station.wg.is_valid)
		{
			this->create_station_model(WR4T_STATION_MODEL_WG);
		}
		if (config->get_mc()->station.wt.is_valid)
		{
			this->create_station_model(WR4T_STATION_MODEL_WT);
		}
		cout<<"STATION_CONTROLLER_CLASS::create_all_models() <<<<"<<endl;
	}

	void STATION_CONTROLLER_CLASS::delete_all_models()
	{
		this->m_station_model_map.clear();
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> STATION_CONTROLLER_CLASS::get_station_mode( WR4T_STATION_MODEL_ENUM station )
	{
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> station_mode;
		map<WR4T_STATION_MODEL_ENUM, boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>>::iterator iter = this->m_station_model_map.find(station);
		if (iter != m_station_model_map.end())
		{
			station_mode = iter->second;
		}
		return station_mode;
	}

	void STATION_CONTROLLER_CLASS::create_station_model( WR4T_STATION_MODEL_ENUM station )
	{
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> model;
		switch(station)
		{
		case WR4T_STATION_MODEL_WG:
			model.reset(new STATION_MODEL_ABSTRACT_INTERFACE());
			break;
		case WR4T_STATION_MODEL_WT:
			model.reset(new STATION_MODEL_ABSTRACT_INTERFACE());
			break;
		default:
			break;
		}
	}

	WR4T_ARM_STATION_ENUM STATION_CONTROLLER_CLASS::convert( char name )
	{
		WR4T_ARM_STATION_ENUM stn = WR4T_ARM_STATION_MIM;
		if ((name >= 'A' && name <= 'Z') || (name >= 'a' && name <= 'z'))
		{
			stn = (WR4T_ARM_STATION_ENUM)name;
		}
		else
		{
			//BOOST_THROW_EXCEPTION(WR_PARAMETER_EXCEPTION_CLASS("no such station exist ...",NULL)<<",__FUNCTION__ :"<<__FUNCTION__<<",__FILE__:"<<__FILE__);
			BOOST_THROW_EXCEPTION(WR_PARAMETER_EXCEPTION_CLASS("WR_PARAMETER_EXCEPTION_CLASS",NULL));
			//throw boost::enable_error_info(WR_EXCEPTION_CLASS(111,0,"WR_EXCEPTION_CLASS", NULL))<<__FILE__<<__FUNCTION__;
		}

		return stn;
	}
}