#include "stdafx.h"
#include "CENTERING_SYSTEM_CLASS.h"

namespace _WU
{
	EXPORT template<typename M_TYPE,typename A_ENUM>
	CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::CENTERING_SYSTEM_CLASS( std::string subset_name )
	{
		this->m_size = new M_TYPE;
		this->m_station = new std::map<A_ENUM,std::list<void*> >;
		this->m_subset_name = subset_name;
		this->m_material_present = false;
		this->m_do_switch = false;
		this->m_initialized = false;
		this->m_is_interfered = false;

	};

	EXPORT template<typename M_TYPE,typename A_ENUM>
	CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::~CENTERING_SYSTEM_CLASS()
	{

	};

	EXPORT template<typename M_TYPE,typename A_ENUM>
	std::map<A_ENUM,std::list<void*>>* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_station_list()
	{
		return this->m_station;

	};

	EXPORT template<typename M_TYPE,typename A_ENUM>
	void CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::set_station_list( std::map<A_ENUM,std::list<void*>>* station )
	{
		this->m_station = station;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_material_present()
	{
		return &this->m_material_present;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::switch_station()
	{
		int error_code = 0;
		return error_code;

	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_do_switch()
	{
		return &this->m_do_switch;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::initialize()
	{
		int error_code = 0;
		return error_code;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_initialized()
	{
		return &this->m_initialized;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::interference_handle()
	{
		int error_code = 0;
		return error_code;	
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_interfered()
	{
		return &this->m_is_interfered;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	M_TYPE* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_material_size() const
	{
		return this->m_size;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	void CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::set_material_size( M_TYPE* size )
	{
		this->m_size = size;
	}

	EXPORT template<typename M_TYPE,typename A_ENUM>
	std::string CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_name() const
	{
		return this->m_subset_name;
	}
}