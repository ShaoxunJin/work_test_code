#ifndef MATERIAL_INTERFACE_H
#define MATERIAL_INTERFACE_H

#include "EXCHANGE_INTERFACE.h"
#include "STATION_MODEL_ABSTRACT_INTERFACE.h"
#include "boost/shared_ptr.hpp"

namespace WRH
{
	class MATERIAL_INTERFACE
	{
	public:
		MATERIAL_INTERFACE();
		virtual ~MATERIAL_INTERFACE();

	public:
		void reset_model();
		
		void set_current_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route);
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_current_route();

		void set_previous_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route);
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_previous_route();
		
		void set_current_exchange(boost::shared_ptr<EXCHANGE_INTERFACE> exchange);
		boost::shared_ptr<EXCHANGE_INTERFACE> get_current_exchange();

		void set_next_exchange(boost::shared_ptr<EXCHANGE_INTERFACE> exchange);
		boost::shared_ptr<EXCHANGE_INTERFACE> get_next_exchange();
	
		void set_material_size(WZ4A_WAFER_SIZE_ENUM material_size);
		WZ4A_WAFER_SIZE_ENUM get_material_size();

	private:
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_current_route;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_previous_route;
		boost::shared_ptr<EXCHANGE_INTERFACE> m_current_exchange;
		boost::shared_ptr<EXCHANGE_INTERFACE> m_next_exchange;
		WZ4A_WAFER_SIZE_ENUM m_material_size;

	};
}



#endif