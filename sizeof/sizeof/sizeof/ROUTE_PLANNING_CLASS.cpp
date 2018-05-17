#include "stdafx.h"
#include "ROUTE_PLANNING_CLASS.h"

namespace WRH
{
	ROUTE_PLANNING_CLASS::ROUTE_PLANNING_CLASS()
	{

	}

	ROUTE_PLANNING_CLASS::~ROUTE_PLANNING_CLASS()
	{

	}

	void ROUTE_PLANNING_CLASS::plan_routes(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> first_destination,
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> next_destination)
	{
		this->plan_route(first_destination);
		this->plan_route(next_destination);
	}

	list<boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>> ROUTE_PLANNING_CLASS::get_routes()
	{
		return this->m_route_list;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> ROUTE_PLANNING_CLASS::get_first_route()
	{
		return this->m_fisrt_route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> ROUTE_PLANNING_CLASS::get_next_route()
	{
		return this->m_next_route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> ROUTE_PLANNING_CLASS::get_last_route()
	{
		return this->m_last_route;
	}

	void ROUTE_PLANNING_CLASS::set_first_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> first_route )
	{
		this->m_fisrt_route = first_route;
	}

	void ROUTE_PLANNING_CLASS::set_next_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> next_route )
	{
		this->m_next_route = next_route;
	}

	void ROUTE_PLANNING_CLASS::set_last_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> last_route )
	{
		this->m_last_route = last_route;
	}

	void ROUTE_PLANNING_CLASS::add_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route )
	{
		plan_route(route);
	}

	void ROUTE_PLANNING_CLASS::clear_routes()
	{
		this->m_route_list.clear();
	}

	void ROUTE_PLANNING_CLASS::delete_routes( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> current_route )
	{
		list<boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE>>::iterator iter = this->m_route_list.begin();
		while (iter != m_route_list.end())
		{
			if (*iter == current_route)
			{
				this->m_route_list.erase(iter);
			}
			iter++;
		}
	}

	void ROUTE_PLANNING_CLASS::plan_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> point)
	{
		this->m_route_list.push_back(point);
	}
}