#include "stdafx.h"
#include "ROBOT_INTERFACE.h"

namespace WRH
{
	ROBOT_INTERFACE::ROBOT_INTERFACE()
	{
		cout<<"Construction : "<<typeid(ROBOT_INTERFACE()).name()<<endl;
	}
	ROBOT_INTERFACE::~ROBOT_INTERFACE()
	{
		cout<<"Destruction : "<<typeid(ROBOT_INTERFACE()).name()<<endl;
	}

	void ROBOT_INTERFACE::reset_model()
	{
		this->m_current_route.reset();
		this->m_next_route.reset();
		for (map<WR4T_ARM_ID_ENUM, boost::shared_ptr<MATERIAL_INTERFACE>>::iterator iter = m_arm_material.begin();
			iter != m_arm_material.end();
			iter++)
		{
			iter->second->reset_model();
		}
	}

	void ROBOT_INTERFACE::set_current_active_arm( WR4T_ARM_ID_ENUM arm_id )
	{
		this->m_current_arm_id = arm_id;
	}

	WR4T_ARM_ID_ENUM ROBOT_INTERFACE::get_current_active_arm()
	{
		return this->m_current_arm_id;
	}

	void ROBOT_INTERFACE::set_next_active_arm( WR4T_ARM_ID_ENUM arm_id )
	{
		this->m_next_arm_id = arm_id;
	}

	WR4T_ARM_ID_ENUM ROBOT_INTERFACE::get_next_active_arm()
	{
		return this->m_next_arm_id;
	}

	void ROBOT_INTERFACE::set_in_pickup( SMEE_BOOL in_pickup )
	{
		this->m_in_pickup = in_pickup;
	}

	SMEE_BOOL ROBOT_INTERFACE::get_in_pickup()
	{
		return this->m_in_pickup;
	}

	void ROBOT_INTERFACE::set_material( WR4T_ARM_ID_ENUM arm_id, boost::shared_ptr<MATERIAL_INTERFACE> material )
	{
		this->m_arm_material[arm_id] = material;
	}

	void ROBOT_INTERFACE::reset_material(WR4T_ARM_ID_ENUM arm_id)
	{
		map<WR4T_ARM_ID_ENUM, boost::shared_ptr<MATERIAL_INTERFACE>>::iterator iter = this->m_arm_material.find(arm_id);
		if (iter != this->m_arm_material.end())
		{
			this->m_arm_material.erase(iter);
		}
	}


	boost::shared_ptr<MATERIAL_INTERFACE> ROBOT_INTERFACE::get_material( WR4T_ARM_ID_ENUM arm_id )
	{
		boost::shared_ptr<MATERIAL_INTERFACE> material;
		map<WR4T_ARM_ID_ENUM, boost::shared_ptr<MATERIAL_INTERFACE>>::iterator iter = this->m_arm_material.find(arm_id);
		if(iter != m_arm_material.end())
		{
			material = iter->second;
			if (material == NULL)
			{
				try
				{
					EXIT_FAILURE;
				}
				catch (const char* e)
				{
				}
			}
		}
		return material;
	}

	void ROBOT_INTERFACE::set_current_route( boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route )
	{
		this->m_current_route = route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> ROBOT_INTERFACE::get_current_route()
	{
		return this->m_current_route;
	}

	void ROBOT_INTERFACE::set_next_route(boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> route)
	{
		this->m_next_route = route;
	}

	boost::shared_ptr<STATION_MODEL_ABSTRACT_INTERFACE> ROBOT_INTERFACE::get_next_route()
	{
		return this->m_next_route;
	}
	

}