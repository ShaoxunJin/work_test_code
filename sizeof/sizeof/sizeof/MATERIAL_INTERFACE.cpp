#include "stdafx.h"
#include "MATERIAL_INTERFACE.h"

namespace WRH
{
	MATERIAL_INTERFACE::MATERIAL_INTERFACE()
	{

	}

	MATERIAL_INTERFACE::~MATERIAL_INTERFACE()
	{

	}

	void MATERIAL_INTERFACE::reset_model()
	{
		this->m_current_exchange.reset();
		this->m_next_exchange.reset();
		this->m_current_route.reset();
		this->m_previous_route.reset();
	}

	void MATERIAL_INTERFACE::set_current_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route )
	{
		this->m_current_route = route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> MATERIAL_INTERFACE::get_current_route()
	{
		return this->m_current_route;
	}

	void MATERIAL_INTERFACE::set_previous_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route )
	{
		this->m_previous_route = route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> MATERIAL_INTERFACE::get_previous_route()
	{
		return this->m_previous_route;
	}

	void MATERIAL_INTERFACE::set_current_exchange( boost::shared_ptr<EXCHANGE_INTERFACE> exchange )
	{
		this->m_current_exchange = exchange;
	}

	boost::shared_ptr<EXCHANGE_INTERFACE> MATERIAL_INTERFACE::get_current_exchange()
	{
		return this->m_current_exchange;
	}

	void MATERIAL_INTERFACE::set_next_exchange( boost::shared_ptr<EXCHANGE_INTERFACE> exchange )
	{
		this->m_next_exchange = exchange;
	}

	boost::shared_ptr<EXCHANGE_INTERFACE> MATERIAL_INTERFACE::get_next_exchange()
	{
		return this->m_next_exchange;
	}

	void MATERIAL_INTERFACE::set_material_size( WZ4A_WAFER_SIZE_ENUM material_size )
	{
		this->m_material_size = m_material_size;
	}

	WZ4A_WAFER_SIZE_ENUM MATERIAL_INTERFACE::get_material_size()
	{
		return this->m_material_size;
	}
}