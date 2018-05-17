/********************************************************************
	Copyright (C) 2015, 上海微电子装备有限公司
    All rights reserved.
	created:	2015/09/18
	created:	18:9:2015   12:46
	filename: 	e:\205C\WU_workflow\WU\WU\STATE_CHART_BASE_CLASS.h
	file path:	e:\205C\WU_workflow\WU\WU
	file base:	STATE_CHART_BASE_CLASS
	file ext:	h
	author:		sunww
	purpose:
	产品号：     SSB509
	所属组件：   WU
    历史记录：
    版本       日  期      作  者           内    容
	1.0.0    18/9/2015    sunww            新建.
*********************************************************************/
//#ifndef STATE_CHART_BASE_CLASS_HPP__
//#define STATE_CHART_BASE_CLASS_HPP__
#include "stdafx.h"
#include <map>
#include <iostream>
#include <string>

namespace UNIT_WU {

    /*
    * @ brief driver state enum define
    */

    typedef enum{
    	DRIVER_STATE_MIN = 0,
    	DRIVER_STATE_UNKNOWN,
    	DRIVER_STATE_TERMINATE,
    	DRIVER_STATE_INITIATE,
    	DRIVER_STATE_BUSY,
    	DRIVER_STATE_MAX
    }DRIVER_STATE_ENUM;


#define STATE_CHART_BEGIN(name)       \
                                class name##_state_chart:public state_chart_f<name>\
								{\
								public: \
								static name##_state_chart* instance()\
								{\
								    static name##_state_chart* state = new name##_state_chart();\
								    return state;\
								}\
								~name##_state_chart(){}\
								name##_state_chart()

#define REGISTER_STATE_CHART(id,state,permit)    \
								this->pair_func(id,state,permit)

#define STATE_CHART_END               \
							    }

#define STATE_MACHINE_INIT()          \
                            this->initialize_state_chart()

#define STATE_CHART_INSTANCE(name)    \
							name##_state_chart::instance()

#define STATE_CHART_CLASS(name)       \
							name##_state_chart

	template <typename FUNC_ID>
	class state_chart_f : public std::map<FUNC_ID,std::map<UNIT_WU::DRIVER_STATE_ENUM,bool> >
	{
	public:
		/*
		* @brief deconstructor
		*/
		virtual ~state_chart_f(){}

		/*
		* @brief constructor
		*/
		state_chart_f(){}

		/************************************
		*@ Method:    pair_func
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::pair_func
		*@ Access:    virtual public
		*@ Returns:   void
		*@ Qualifier:
		*@ Parameter: const FUNC_ID key
		*@ Parameter: const DRIVER_STATE_ENUM value
		*@ Parameter: const bool premit
		*@ Description:
		*************************************/
		virtual void pair_func(const FUNC_ID & key,const DRIVER_STATE_ENUM & value,const bool & premit)
		{

			this->m_state_map.insert(make_pair(value,premit));
			if (this->m_state_map.size() >= (DRIVER_STATE_MAX - DRIVER_STATE_MIN - 1))
			{
				this->insert(make_pair(key,this->m_state_map));
				this->m_state_map.clear();
			}
		}

		/************************************
		*@ Method:    is_func_permit
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::is_func_permit
		*@ Access:    virtual public
		*@ Returns:   bool
		*@ Qualifier:
		*@ Parameter: const FUNC_ID & func_id
		*@ Parameter: const DRIVER_STATE_ENUM & state
		*@ Description:
		*************************************/
		virtual bool is_func_permit(const FUNC_ID & func_id)
		{
			assert(this->m_state > DRIVER_STATE_MIN && this->m_state < DRIVER_STATE_MAX);
			typename std::map<FUNC_ID,std::map<DRIVER_STATE_ENUM,bool> >::iterator i = this->find(func_id);
			if (i != this->end())
			{
				return i->second.operator[](this->m_state);
			}
			return false;
		}

		/************************************
		*@ Method:    initialize_state_chart
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::initialize_state_chart
		*@ Access:    virtual public
		*@ Returns:   void
		*@ Qualifier:
		*@ Description: 初始化状态机
		*************************************/
        virtual void initialize_state_chart()
        {
            this->m_state = DRIVER_STATE_TERMINATE;
        }

		/************************************
		*@ Method:    initiate
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::initiate
		*@ Access:    virtual public
		*@ Returns:   void
		*@ Qualifier:
		*@ Description: 设置状态为INITIATE
		*************************************/
		virtual void initiate()
		{
			this->m_state = DRIVER_STATE_INITIATE;
		}

		/************************************
		*@ Method:    terminate
		*@ FullName:  std<FUNC_ID>::terminate
		*@ Access:    public
		*@ Returns:   void
		*@ Qualifier:
		*@ Description: 设置状态为TERMINATE
		*************************************/
		virtual void terminate()
		{
			this->m_state = DRIVER_STATE_TERMINATE;
		}

		/************************************
		*@ Method:    unknown
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::unknown
		*@ Access:    virtual public
		*@ Returns:   void
		*@ Qualifier:
		*@ Description: 设置状态为UNKNOWN
		*************************************/
		virtual void unknown()
		{
			this->m_state = DRIVER_STATE_UNKNOWN;
		}

		/************************************
		*@ Method:    busy
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::busy
		*@ Access:    virtual public
		*@ Returns:   void
		*@ Qualifier:
		*@ Description: 设置状态为BUSY
		*************************************/
		virtual void busy()
		{
			this->m_state = DRIVER_STATE_BUSY;
		}

		/************************************
		*@ Method:    terminated
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::terminated
		*@ Access:    virtual public
		*@ Returns:   bool
		*@ Qualifier: const
		*@ Description: 是否终止
		*************************************/
		virtual bool terminated()const
		{
			return this->m_state == DRIVER_STATE_TERMINATE;
		}

		/************************************
		*@ Method:    current_state
		*@ FullName:  UNIT_WU::state_chart_f<FUNC_ID>::current_state
		*@ Access:    virtual public
		*@ Returns:   UNIT_WU::DRIVER_STATE_ENUM
		*@ Qualifier: const
		*@ Description: 获取状态机状态/更新状态机状态
		*************************************/
		virtual DRIVER_STATE_ENUM get_state()const
		{
			return this->m_state;
		}

 		virtual void update_state(const DRIVER_STATE_ENUM & state)
		{
			this->m_state = state;
		}
	private:
		/*
		* @brief map
		*/
		std::map<DRIVER_STATE_ENUM,bool> m_state_map;

		/*
		* @brief state
		*/
		DRIVER_STATE_ENUM m_state;
	};

}
//#endif // STATE_CHART_BASE_CLASS_H__