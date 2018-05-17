#include "stdafx.h"
#include "ROBOT_API.h"

namespace WRH
{
	ROBOT_API::ROBOT_API()
	{
		this->m_robot.reset(new ROBOT_MODEL_CLASS());
		this->m_station_controller.reset(new STATION_CONTROLLER_CLASS());
	}

	ROBOT_API::~ROBOT_API()
	{

	}
	
	void ROBOT_API::initialize()
	{
		this->m_station_controller->create_all_models();
		this->m_station_controller->initialize_models();
	}

	void ROBOT_API::terminate()
	{

	}

	void ROBOT_API::get_wafer(WR4T_ARM_ID_ENUM arm_id,
								WR4T_STATION_MODEL_ENUM from_station,
								int from_slot,
								WR4T_STATION_MODEL_ENUM to_station,
								SMEE_BOOL *present)
	{
		boost::shared_ptr<EXCHANGE_INTERFACE> get_model(new GET_MODEL_CLASS());

		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from;
		try
		{
			from = boost::bind(&STATION_CONTROLLER_CLASS::get_station_mode, boost::ref(this->m_station_controller), _1)(from_station);

		}
		catch (WR_EXCEPTION_CLASS& e)
		{
			cout<<boost::diagnostic_information(e)<<endl;
			cout<<e.error_msg()<<endl;
		}
		boost::bind(&STATION_MODEL_ABSTRACT_INTERFACE::set_current_arm_id, boost::ref(from), _1)(arm_id);
		boost::bind(&STATION_MODEL_ABSTRACT_INTERFACE::set_current_slot, boost::ref(from), _1)(from_slot);
		
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to;
		try
		{
			to = boost::bind(&STATION_CONTROLLER_CLASS::get_station_mode, boost::ref(this->m_station_controller), _1)(to_station);

		}
		catch (WR_EXCEPTION_CLASS& e)
		{
			cout<<boost::diagnostic_information(e)<<endl;
			cout<<e.error_msg()<<endl;
		}
		boost::bind(&STATION_MODEL_ABSTRACT_INTERFACE::set_current_arm_id, boost::ref(to), _1)(arm_id);
		boost::bind(&STATION_MODEL_ABSTRACT_INTERFACE::set_current_slot, boost::ref(to), _1)(0);

		time_t cur_time;
		time(&cur_time);
		boost::shared_ptr<MATERIAL_MODEL> material(new MATERIAL_MODEL(123, cur_time, WZ4A_2_INCH));
		WR_POINT_EXCEPTION_CHECK(-1, 0, "material model creater failed ....", NULL)(material);
		boost::bind(&MATERIAL_INTERFACE::reset_model, boost::ref(material))();
		boost::bind(&MATERIAL_INTERFACE::set_current_exchange, boost::ref(material), _1)(get_model);
		try
		{
			boost::bind(&ROBOT_MODEL_CLASS::get_material, boost::ref(this->m_robot), _1, _2, _3)(from, to, material);
		}
		catch(WR_EXCEPTION_CLASS& msg)
		{
			cerr<<boost::diagnostic_information(msg)<<endl;
			cerr<<msg.error_msg()<<endl;
		}
	}

	void ROBOT_API::put_wafer(WR4T_ARM_ID_ENUM arm_id,
							WR4T_STATION_MODEL_ENUM from_station,
							int slot,
							WR4T_STATION_MODEL_ENUM to_station)
	{
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from = this->m_station_controller->get_station_mode(from_station);
		if (NULL != from)
		{
			from->set_current_arm_id(arm_id);
			from->set_current_slot(slot);
			cout<< "create first route success..."<<std::endl;
		}
		else
		{
			cout<< "create first route failed..."<<std::endl;
		}

		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to = this->m_station_controller->get_station_mode(to_station);
		if (NULL != to)
		{
			to->set_current_arm_id(arm_id);
			to->set_current_slot(slot);
			cout<<"creat next route success ..."<<endl;
		}
		else
		{
			cout<<"creat next route failed ..."<<endl;
		}

		boost::shared_ptr<MATERIAL_INTERFACE> material = boost::bind(&ROBOT_INTERFACE::get_material, this->m_robot, _1)(arm_id);
		material->set_material_size(WZ4A_2_INCH);

		try
		{
			boost::bind(&ROBOT_MODEL_CLASS::put_material, boost::ref(this->m_robot), _1, _2, _3)(from, to, material);
		}
		catch(WR_EXCEPTION_CLASS &msg)
		{
			cerr<<msg.error_msg()<<endl;
		}
	}

	void ROBOT_API::swap_wafer(int swap_method, WR4T_STATION_MODEL_ENUM swap_station, WR4T_ARM_ID_ENUM start_arm_id, WR4T_ARM_ID_ENUM end_arm_id, int slot, WR4T_STATION_MODEL_ENUM to_station)
	{

	}

	void ROBOT_API::clamp_wafer(WR4T_ARM_ID_ENUM arm_id, SMEE_BOOL *present)
	{
		
	}

	void ROBOT_API::unclamp_wafer(WR4T_ARM_ID_ENUM arm_id, SMEE_BOOL *present)
	{

	}

	void ROBOT_API::set_wafer_size(WZ4A_WAFER_SIZE_ENUM wafer_size)
	{

	}
}