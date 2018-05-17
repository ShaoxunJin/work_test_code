#ifndef ROUTE_PLANNING_CLASS_H
#define ROUTE_PLANNING_CLASS_H

#include "STATION_MODEL_ABSTRACT_INTERFACE.h"
#include <list>

namespace WRH
{
	class ROUTE_PLANNING_CLASS
	{
	public:
		ROUTE_PLANNING_CLASS();
		virtual ~ROUTE_PLANNING_CLASS();

		void plan_routes(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> first_destination,
			boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> next_destination);
		list<boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>> get_routes();
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_first_route();
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_next_route();
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_last_route();

		void set_first_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> first_route);
		void set_next_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> next_route);
		void set_last_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> last_route);

		void add_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route);
		void clear_routes();
		void delete_routes(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> current_route);

	private:
		void plan_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> point);
		list<boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>> m_route_list;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_fisrt_route;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_next_route;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_last_route;

	};
}

#endif