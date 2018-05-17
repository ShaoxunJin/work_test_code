#include "stdafx.h"
#include "STATION_INTERFACE.h"

namespace WRH
{
	STATION_INTERFACE::STATION_INTERFACE()
	{
		cout<<"This is station interface class construction ...."<<endl;
		m_current_slot = -1;
		m_next_slot = -1;
		m_exchange_nbr = 0;
	}

	STATION_INTERFACE::~STATION_INTERFACE()
	{
	}

	void STATION_INTERFACE::set_current_slot(int slot)
	{
		m_current_slot = slot;
	}

	int STATION_INTERFACE::get_current_slot()
	{
		return m_current_slot;
	}

	void STATION_INTERFACE::set_next_slot(int slot)
	{
		m_next_slot = slot;
	}
	int STATION_INTERFACE::get_next_slot()
	{
		return m_next_slot;
	}

	void STATION_INTERFACE::set_next_arm_id(WR4T_ARM_ID_ENUM arm_id)
	{
		this->m_next_arm_id = arm_id;
	}

	WR4T_ARM_ID_ENUM STATION_INTERFACE::get_next_arm_id()
	{
		return m_next_arm_id;	
	}

	void STATION_INTERFACE::set_current_arm_id(WR4T_ARM_ID_ENUM arm_id)
	{
		this->m_current_arm_id = arm_id;
	}

	WR4T_ARM_ID_ENUM STATION_INTERFACE::get_current_arm_id()
	{
		return this->m_current_arm_id;
	}

	void STATION_INTERFACE::register_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type)
	{
		m_exchange_vector.push_back(type);
		m_exchange_nbr++;
	}

	void STATION_INTERFACE::delete_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type)
	{
		//先查找是否存在 根据实际情况进行delete
		vector<WR4T_EXCHANGE_TYPE_ENUM>::iterator iter_exchange_type = m_exchange_vector.begin();
		while (iter_exchange_type != m_exchange_vector.end())
		{
			if (type == *iter_exchange_type)
			{
				m_exchange_vector.erase(iter_exchange_type);
			}
			iter_exchange_type++;
		}
	}

	void STATION_INTERFACE::tt_show_m_exchange_vector()
	{
		vector<WR4T_EXCHANGE_TYPE_ENUM>::iterator iter = m_exchange_vector.begin();
		int nbr = 0;
		for (;
			iter != m_exchange_vector.end();
			++iter, ++nbr)
		{
			//cout<<"m_exchange_vector["<<nbr<<"] = "<<str_WR4T_EXCHANGE_TYPE_ENUM.to_string(*iter)<<endl;
		}
	}
	
	void STATION_INTERFACE::tt_show_exchange_nbr()
	{
		cout<<"exchange_number : "<<m_exchange_vector.size()<<endl;
		cout<<"m_exchange_nbr :"<<m_exchange_nbr<<endl;
	}

	void STATION_INTERFACE::register_station_name( WZ4A_WAFER_SIZE_ENUM wafer_size, WR4T_ARM_STATION_ENUM station )
	{
		m_tuple_station_name_vector.push_back(boost::make_tuple(wafer_size, station));
	}

	WR4T_ARM_STATION_ENUM STATION_INTERFACE::get_station_name( WZ4A_WAFER_SIZE_ENUM wafer_size )
	{
		WR4T_ARM_STATION_ENUM station_rtn = WR4T_ARM_STATION_MIM;
		vector<m_tuple>::iterator iter = m_tuple_station_name_vector.begin();
		while (iter != m_tuple_station_name_vector.end())
		{
			if (iter->get<0>() == wafer_size)
			{
				station_rtn = iter->get<1>();
				break;
			}
			iter++;
		}
		return station_rtn;
	}

	bool STATION_INTERFACE::can_invoke_route(WR4T_EXCHANGE_TYPE_ENUM type)
	{
		bool result = false;
		std::vector<WR4T_EXCHANGE_TYPE_ENUM>::iterator ps = this->m_exchange_vector.begin();
		while (ps != this->m_exchange_vector.end())
		{
			if (*ps == type)
			{
				result = true;
				break;
			}
			ps++;
		}
		return result;
	}

	void STATION_INTERFACE::reset_mode()
	{
		this->m_current_slot = -1;
		this->m_next_slot = -1;
		this->m_exchange_nbr = 0;
		this->m_exchange_vector.clear();
		this->m_tuple_station_name_vector.clear();
	}
}