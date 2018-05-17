#ifndef ROBOT_MODEL_CLASS_H
#define ROBOT_MODEL_CLASS_H

#include "ROBOT_INTERFACE.h"
#include "EXCEPTION_CLASS.h"
#include "boost/shared_ptr.hpp"
#include "boost/bind.hpp"
#include "boost/exception/all.hpp"
#include "boost/throw_exception.hpp"
#include "boost/exception/enable_error_info.hpp"
#include "head_file.h"
#include "ROBOT_HARDWARE_SERVICE_CLASS.h"

namespace WRH
{
	class ROBOT_MODEL_CLASS : public ROBOT_INTERFACE
	{
	public:
		ROBOT_MODEL_CLASS();
		~ROBOT_MODEL_CLASS();

	public:
		void get_material(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from,
			boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to,
			boost::shared_ptr<MATERIAL_INTERFACE> material);

		void put_material(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from,
			boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to,
			boost::shared_ptr<MATERIAL_INTERFACE> material);

		void swap_material(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from,
			boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to,
			boost::shared_ptr<MATERIAL_INTERFACE> material);

		void move_robot(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> station,
			boost::shared_ptr<EXCHANGE_INTERFACE> exchange);

		void move_to_exchange(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> station);
		void check_material_present(SMEE_BOOL *present);
		void check_material_present(WR4T_ARM_ID_ENUM arm_id, SMEE_BOOL *present);

	private:
		boost::shared_ptr<ROBOT_HARDWARE_SERVICE_CLASS> m_robot_hardware;
	};
}


#endif