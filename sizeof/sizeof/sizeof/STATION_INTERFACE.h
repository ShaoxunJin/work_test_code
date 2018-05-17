#ifndef _STATION_INTERFACE_H
#define _STATION_INTERFACE_H

#include "head_file.h"
#include "ENUM_TO_STRING.h"
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

/******************************************************************
1、当前槽号；
2、下一轮槽号；
3、交接类型；
4、工位名字
******************************************************************/

namespace WRH
{
	class STATION_INTERFACE
	{
	public:
		STATION_INTERFACE();
		~STATION_INTERFACE();
		
		void reset_mode();
		void set_current_slot(int slot);
		int get_current_slot();

		void set_next_slot(int slot);
		int get_next_slot();

		void set_next_arm_id(WR4T_ARM_ID_ENUM arm_id);
		WR4T_ARM_ID_ENUM get_next_arm_id();

		void set_current_arm_id(WR4T_ARM_ID_ENUM arm_id);
		WR4T_ARM_ID_ENUM get_current_arm_id();
		
		void register_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type);
		void delete_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type);
		void delete_all_exchange_type();

		void register_station_name(WZ4A_WAFER_SIZE_ENUM wafer_size, WR4T_ARM_STATION_ENUM station);
		WR4T_ARM_STATION_ENUM get_station_name(WZ4A_WAFER_SIZE_ENUM wafer_size);

		bool can_invoke_route(WR4T_EXCHANGE_TYPE_ENUM type);

		void tt_show_m_exchange_vector();
		void tt_show_exchange_nbr();

	private:
		int m_current_slot;
		int m_next_slot;
		int m_exchange_nbr;	
		WR4T_ARM_ID_ENUM m_next_arm_id;
		WR4T_ARM_ID_ENUM m_current_arm_id;
	
		typedef boost::tuple<WZ4A_WAFER_SIZE_ENUM, WR4T_ARM_STATION_ENUM> m_tuple;
		vector<WR4T_EXCHANGE_TYPE_ENUM> m_exchange_vector;
		vector<m_tuple> m_tuple_station_name_vector;
		
	};
}

#endif