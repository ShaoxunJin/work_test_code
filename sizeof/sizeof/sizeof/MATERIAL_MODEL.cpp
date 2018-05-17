#include "stdafx.h"
#include "MATERIAL_MODEL.h"

namespace WRH
{
	MATERIAL_MODEL::MATERIAL_MODEL(int material_id, time_t create_time, WZ4A_WAFER_SIZE_ENUM size)
		:m_material_id(material_id)
		,m_created_time(create_time)
	{
		MATERIAL_INTERFACE::set_material_size(size);
	}

	MATERIAL_MODEL::~MATERIAL_MODEL()
	{

	}

	void MATERIAL_MODEL::set_material_id( int id )
	{

	}

	int MATERIAL_MODEL::get_material_id()
	{
		return m_material_id;
	}

	void MATERIAL_MODEL::set_material_created_time( time_t time )
	{

	}

	time_t MATERIAL_MODEL::get_material_created_time()
	{
		return m_created_time;
	}

	void MATERIAL_MODEL::set_material_finishe_time()
	{

	}

	time_t MATERIAL_MODEL::get_material_finish_time( time_t time )
	{
		return m_finish_time;
	}

	time_t MATERIAL_MODEL::get_material_elapse_time()
	{
		time_t elapse_time = 0;
		elapse_time = this->m_finish_time - this->m_created_time;
		return elapse_time;
	}
}