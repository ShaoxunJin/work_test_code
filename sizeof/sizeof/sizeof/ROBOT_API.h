#ifndef ROBOT_API_H
#define ROBOT_API_H

#include "head_file.h"
#include "WR4T_WORKFLOW_tc.h"
#include "ROBOT_MODEL_CLASS.h"
#include "STATION_CONTROLLER_CLASS.h"
#include "GET_MODEL_CLASS.h"
#include "MATERIAL_MODEL.h"
#include "boost/bind/bind.hpp"

namespace WRH
{
	class ROBOT_API
	{
	public:
		ROBOT_API();
		~ROBOT_API();

	public:
		void initialize();
		void terminate();
		void get_wafer(WR4T_ARM_ID_ENUM arm_id,
					WR4T_STATION_MODEL_ENUM from_station,
					int from_slot,
					WR4T_STATION_MODEL_ENUM to_station,
					SMEE_BOOL *present);

		void put_wafer(WR4T_ARM_ID_ENUM arm_id,
						WR4T_STATION_MODEL_ENUM from_station,
						int slot,
						WR4T_STATION_MODEL_ENUM to_station);

		void swap_wafer(int swap_method,
						WR4T_STATION_MODEL_ENUM swap_station,
						WR4T_ARM_ID_ENUM start_arm_id,
						WR4T_ARM_ID_ENUM end_arm_id,
						int slot,
						WR4T_STATION_MODEL_ENUM to_station);
		void clamp_wafer(WR4T_ARM_ID_ENUM arm_id, SMEE_BOOL *present);
		void unclamp_wafer(WR4T_ARM_ID_ENUM arm_id, SMEE_BOOL *present);
		void set_wafer_size(WZ4A_WAFER_SIZE_ENUM wafer_size);

	private:
		boost::shared_ptr<ROBOT_MODEL_CLASS> m_robot;
		boost::shared_ptr<STATION_CONTROLLER_CLASS> m_station_controller;
	};
}


#endif