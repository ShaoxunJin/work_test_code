#include "stdafx.h"
#include "MACHINE_CONSTANT_CLASS.h"
#include "ENUM_TO_STRING.h"

namespace WRH
{
	t_WRMC_INFO_MODE_ENUM_str str_WRMC_INFO_MODE_ENUM;
	ostream& operator<<(ostream& os, const WRMC_ROBOT_STRUCT mc)
	{
		os<<"info_mode = "<<str_WRMC_INFO_MODE_ENUM.to_string(mc.info_mode)<<endl
		  <<"on_line = "<<mc.on_line;
		return os;
	}

	MACHINE_CONSTANT_CLASS::MACHINE_CONSTANT_CLASS()
		:m_mc(new WRMC_ROBOT_STRUCT())
	{
		cout<<"This is construction for class : "<<typeid(MACHINE_CONSTANT_CLASS).name()<<endl;
	}

	MACHINE_CONSTANT_CLASS::~MACHINE_CONSTANT_CLASS()
	{

	}

	void MACHINE_CONSTANT_CLASS::download_mc()
	{

	}

	void MACHINE_CONSTANT_CLASS::update_mc()
	{

	}

	void MACHINE_CONSTANT_CLASS::set_mc( WRMC_ROBOT_STRUCT mc )
	{
		if (NULL != this->m_mc)
		{
			//memcpy((void*)this->m_mc, (void*)&mc, sizeof(WRMC_ROBOT_STRUCT));
			this->m_mc = &mc;
			cout<<"this->m_mc->info_mode = "<<str_WRMC_INFO_MODE_ENUM.to_string(this->m_mc->info_mode)<<endl;
		}
		else
		{
			cout<<"this->m_mc is NULL !"<<endl;
		}
	}

	WRMC_ROBOT_STRUCT* MACHINE_CONSTANT_CLASS::get_mc()
	{
		return this->m_mc;
	}

	const WRMC_STATION_PARAMTER_STRUCT* MACHINE_CONSTANT_CLASS::get_station_config( WR4T_STATION_MODEL_ENUM station )
	{
		static WRMC_STATION_PARAMTER_STRUCT* station_parameter = NULL;
		if (NULL != this->m_mc)
		{
			switch(station)
			{
			case WR4T_STATION_MODEL_WT:
				station_parameter = &this->m_mc->station.wt;
				break;
			case WR4T_STATION_MODEL_WU1:
				station_parameter = &this->m_mc->station.wu1;
				break;
			case WR4T_STATION_MODEL_WU2:
				station_parameter = &this->m_mc->station.wu2;
				break;
			case WR4T_STATION_MODEL_OC:
				station_parameter = &this->m_mc->station.oc;
				break;
			case WR4T_STATION_MODEL_IC:
				station_parameter = &this->m_mc->station.ic;
				break;
			case WR4T_STATION_MODEL_WG:
				station_parameter = &this->m_mc->station.wg;
				break;
			case WR4T_STATION_MODEL_WC1:
				station_parameter = &this->m_mc->station.wc1;
				break;
			case WR4T_STATION_MODEL_WC2:
				station_parameter = &this->m_mc->station.wc2;
				break;
			case WR4T_STATION_MODEL_WC3:
				station_parameter = &this->m_mc->station.wc3;
				break;
			default:
				break;
			}
		}
		else
		{
			cout<<"this->m_mc = null !"<<endl;
		}
		return station_parameter;
	}

	void MACHINE_CONSTANT_CLASS::verify_mc( const WRMC_ROBOT_STRUCT& mc )
	{

	}

	void MACHINE_CONSTANT_CLASS::print_mc()
	{
		if(NULL != m_mc)
		{
			//���ز����� ע�����ز������е����������ָ�뻹�����ã�
			cout<<*m_mc<<endl;
		}
		else
		{
			cout<<"m_mc is NULL !"<<endl;
		}
	}
	//��̬����һ��Ҫ���г�ʼ������ ������ʱ��һ���ͺ�������һ���������ͺ�����
	MACHINE_CONSTANT_CLASS* MACHINE_CONSTANT_CLASS::m_instance = NULL;
	MACHINE_CONSTANT_CLASS *MACHINE_CONSTANT_CLASS::get_instance()
	{
		if (NULL == m_instance)
		{
			m_instance = new MACHINE_CONSTANT_CLASS();
		}
		
			return m_instance;
	}
}

