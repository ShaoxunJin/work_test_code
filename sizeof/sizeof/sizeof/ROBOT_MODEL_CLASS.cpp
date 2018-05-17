#include "stdafx.h"
#include "ROBOT_MODEL_CLASS.h"


namespace WRH
{
	ROBOT_MODEL_CLASS::ROBOT_MODEL_CLASS()
	{

	}

	ROBOT_MODEL_CLASS::~ROBOT_MODEL_CLASS()
	{

	}

	void ROBOT_MODEL_CLASS::get_material(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from,
								boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to,
								boost::shared_ptr<MATERIAL_INTERFACE> material)
	{
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR, 0, "from station model not present", NULL)(from);
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR, 0, "to station model not present", NULL)(to);
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR, 0, "material model not present", NULL)(material);
		cout<< "ROBOT_MODEL_CLASS::get_material size = " << material->get_material_size() <<std::endl;
		WR4T_ARM_ID_ENUM cur_arm_id = from->get_current_arm_id();
		WR4T_ARM_ID_ENUM next_arm_id = to->get_current_arm_id();
		int cur_slot = from->get_current_slot();
		int next_slot = to->get_current_slot();
		
		//交接方式是否允许
		if (!from->can_invoke_route(WR4T_EXCHANGE_TYPE_GET))
		{
			BOOST_THROW_EXCEPTION(WR_ILLEGAL_EXCEPTION_CLASS("invoke_route failed ,exchange type[PUT] is not permitted...",NULL));
		}
		//
		if (ROBOT_INTERFACE::get_material(cur_arm_id) == NULL)
		{
			throw boost::enable_error_info(WR_ILLEGAL_EXCEPTION_CLASS("can_invoke_route failed ...",NULL));
				//<<__FILE__
				//<<__FUNCTION__;
		}

		boost::bind(&ROBOT_INTERFACE::set_current_route,boost::ref(*this),_1)(from);
		boost::bind(&ROBOT_INTERFACE::set_next_route,boost::ref(*this),_1)(to);

		int current_expect_station = 0;
		int next_expect_station = 0;
		
		try
		{
			current_expect_station = from->get_station_name(material->get_material_size());
			next_expect_station = to->get_station_name(material->get_material_size());
		}
		catch (WR_EXCEPTION_CLASS & e)
		{
			std::cout << e.error_msg() << std::endl;
		}
		bool present = false;
		try
		{
			boost::bind(&ROBOT_HARDWARE_SERVICE_CLASS::get_wafer,boost::ref(this->m_robot_hardware),_1,_2,_3)(current_expect_station,cur_slot,&present);
		}
		catch (WR_EXCEPTION_CLASS & e)
		{
			std::cout <<e.error_msg()<< std::endl;
		}

		boost::bind(&ROBOT_INTERFACE::set_current_active_arm,boost::ref(*this),_1)(cur_arm_id);
		/*
		* @brief update material ...
		*/
		if (present)
		{
			boost::bind(&ROBOT_INTERFACE::set_material,boost::ref(*this),_1,_2)(cur_arm_id,material);
			boost::bind(&ROBOT_INTERFACE::set_next_active_arm,boost::ref(*this),_1)(next_arm_id);
			try
			{
				boost::bind(&ROBOT_HARDWARE_SERVICE_CLASS::move_to_retract,boost::ref(this->m_robot_hardware),next_expect_station,next_slot)();
			}
			catch (WR_EXCEPTION_CLASS & e)
			{
				std::cout << e.error_msg() << std::endl;
			}				
			boost::bind(&ROBOT_INTERFACE::set_current_active_arm,boost::ref(*this),_1)(next_arm_id);
		}
		else
		{
			/*
			* @brief 删除手臂物料
			*/
			boost::bind(&ROBOT_INTERFACE::reset_material,boost::ref(*this),_1)(cur_arm_id);
		}
		std::cout<< "ROBOT_MODEL_CLASS::get_material <..."<<std::endl;
	}


	void ROBOT_MODEL_CLASS::put_material(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> from,
		boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> to,
		boost::shared_ptr<MATERIAL_INTERFACE> material)
	{
		std::cout<< "ROBOT_MODEL_CLASS::put_material >..."<<std::endl;
		
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR,0,"dest1 station_model not present",NULL)(from);
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR,0,"dest2 station_model not present",NULL)(to);
		WR_POINT_EXCEPTION_CHECK(WR_POINTER_NULL_ERROR,0,"material_model not present",NULL)(material);

		std::cout<< "ROBOT_MODEL_CLASS::put_material size = " << material->get_material_size() <<std::endl;
		WR4T_ARM_ID_ENUM cur_arm_id = from->get_current_arm_id();
		WR4T_ARM_ID_ENUM next_arm_id = to->get_current_arm_id();
		int cur_slot = from->get_current_slot();
		int next_slot = to->get_current_slot();

		/*
		* @brief 交接方式检查
		*/
		if (!from->can_invoke_route(WR4T_EXCHANGE_TYPE_PUT))
		{
			BOOST_THROW_EXCEPTION(WR_ILLEGAL_EXCEPTION_CLASS("invoke_route failed ,exchange type[PUT] is not permitted...",NULL));
		}

		/*
		* @brief 物料前置检查,NULL表示没有
		*/
		if (ROBOT_INTERFACE::get_material(cur_arm_id) == NULL)
		{
			throw boost::enable_error_info(WR_ILLEGAL_EXCEPTION_CLASS("invoke_route failed ,material is not present on arm",NULL))<<boost::errinfo_api_function("jin")<<boost::errinfo_errno(100);
		}

		this->set_current_route(from);
		this->set_next_route(to);

		/*
		* @brief 
		*/
		int current_expect_station = 0;
		int next_expect_station = 0;
		try
		{
			//while(1);
			current_expect_station = from->get_station_name(material->get_material_size());
			next_expect_station = to->get_station_name(material->get_material_size());
		}
		catch (WR_EXCEPTION_CLASS & e)
		{
			std::cout << e.error_msg() << std::endl;
		}

		bool present = false;
		try
		{
			boost::bind(&ROBOT_HARDWARE_SERVICE_CLASS::put_wafer,boost::ref(this->m_robot_hardware),_1,_2,_3)(current_expect_station,cur_slot,&present);
		}
		catch (WR_EXCEPTION_CLASS & e)
		{
			std::cout << e.error_msg() << std::endl;
		}

		this->set_current_active_arm(cur_arm_id);
		/*
		* @brief update material ...
		*/
		if (!present)
		{
			/*
			* @brief 删除手臂物料
			*/
			//ROBOT_INTERFACE::reset_material(cur_arm_id);
			this->reset_material(cur_arm_id);
			this->set_next_active_arm(next_arm_id);
			try
			{
				boost::bind(&ROBOT_HARDWARE_SERVICE_CLASS::move_to_retract,boost::ref(this->m_robot_hardware),next_expect_station,next_slot)();
			}
			catch (WR_EXCEPTION_CLASS & e)
			{
				std::cout << e.error_msg() << std::endl;
			}				
			this->set_current_active_arm(next_arm_id);
		}
		else
		{
			throw boost::enable_error_info(WR_SYSTEM_EXCEPTION_CLASS("put failed ,material still on arm",NULL));
		}
		std::cout<< "ROBOT_MODEL_CLASS::put_material <..."<<std::endl;
	}
}