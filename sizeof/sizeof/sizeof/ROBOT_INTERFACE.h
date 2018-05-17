#ifndef ROBOT_INTERFACE_H
#define ROBOT_INTERFACE_H

#include "boost/shared_ptr.hpp"
#include "head_file.h"
#include "MATERIAL_INTERFACE.h"

namespace WRH
{
	class ROBOT_INTERFACE
	{
	public:
		ROBOT_INTERFACE();
		virtual ~ROBOT_INTERFACE();
	
	public:
		void reset_model();
		void set_current_active_arm(WR4T_ARM_ID_ENUM arm_id);
		WR4T_ARM_ID_ENUM get_current_active_arm();

		void set_next_active_arm(WR4T_ARM_ID_ENUM arm_id);
		WR4T_ARM_ID_ENUM get_next_active_arm();

		void set_in_pickup(SMEE_BOOL in_pickup);
		SMEE_BOOL get_in_pickup();

		void set_material(WR4T_ARM_ID_ENUM arm_id, boost::shared_ptr<MATERIAL_INTERFACE> material);
		void reset_material(WR4T_ARM_ID_ENUM arm_id);
		boost::shared_ptr<MATERIAL_INTERFACE> get_material(WR4T_ARM_ID_ENUM arm_id);

		void set_current_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route);
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_current_route();
		void set_next_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route);
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> get_next_route();

	private:
		WR4T_ARM_ID_ENUM m_current_arm_id;
		WR4T_ARM_ID_ENUM m_next_arm_id;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_current_route;
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> m_next_route;
		SMEE_BOOL m_in_pickup;

		map<WR4T_ARM_ID_ENUM, boost::shared_ptr<MATERIAL_INTERFACE>> m_arm_material;
	};
}




#endif