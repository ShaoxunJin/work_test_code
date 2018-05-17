#ifndef MATERIAL_MODEL_H
#define MATERIAL_MODEL_H

#include <ctime>
#include "MATERIAL_INTERFACE.h"
#include "WR4T_WORKFLOW_tc.h"

namespace WRH
{
	class MATERIAL_MODEL : public MATERIAL_INTERFACE
	{
	public:
		MATERIAL_MODEL(int material_id, time_t create_time, WZ4A_WAFER_SIZE_ENUM size);
		~MATERIAL_MODEL();

		void set_material_id(int id);
		int get_material_id();

		void set_material_created_time(time_t time);
		time_t get_material_created_time();
		
		void set_material_finishe_time();
		time_t get_material_finish_time(time_t time);
		
		time_t get_material_elapse_time();

	private:
		int m_material_id;
		time_t m_created_time;
		time_t m_finish_time;

	};
}

#endif