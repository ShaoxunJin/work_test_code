/********************************************************************
	Copyright (C) 2015, 上海微电子装备有限公司
    All rights reserved.
	created:	2015/09/19
	created:	19:9:2015   15:55
	filename: 	e:\205C\WU_workflow\WU\WU\IO_SENSORS_BASE_CLASS.h
	file path:	e:\205C\WU_workflow\WU\WU
	file base:	IO_SENSORS_BASE_CLASS
	file ext:	h
	author:		sunww
	purpose:
	产品号：     SSB509
	所属组件：   WU
    历史记录：
    版本       日  期      作  者           内    容
	1.0.0    19/9/2015    sunww            新建.
*********************************************************************/
//#ifndef IO_SENSOR_BASE_CLASS_HPP__
//#define IO_SENSOR_BASE_CLASS_HPP__


/*##########################################################################*
Header File
*###########################################################################*/
#include "stdafx.h"
#include <map>
#include <iostream>


//using namespace std;

extern "C"
{
	#include <TR4A_if.h>
}

#define  IO_SENSOR_BASE_ERR (WUIO_LOYER_BASE + 0X00)

namespace UNIT_WU
{

    extern const char* COMPONENT_ID;

/*##########################################################################*
Function Declaration
*###########################################################################*/
#define REGISTER_SENSORS_BEGIN(name,item)   class name##_sensor_class : public IO_SENSORS_BASE_CLASS<name,item>\
										{\
										public: \
											static name##_sensor_class* instance()\
										{\
												static name##_sensor_class* mysensor = new name##_sensor_class();\
												return mysensor;\
										}\
										~name##_sensor_class(){}\
										name##_sensor_class():IO_SENSORS_BASE_CLASS<name,item>((int)IO_SENSOR_BASE_ERR)

#define REGISTER_SENSORS(item,inst)    this->pair_sensor(item,inst)

#define REGISTER_SENSORS_END			}


#define IO_SENSORS(name)      name##_sensor_class
#define IO_SENSORS_INST(name) name##_sensor_class::instance()


	template<typename SENSOR_TYPE,typename W>
	class IO_SENSORS_BASE_CLASS : public std::map<SENSOR_TYPE,W*>
	{
	public:
		/*
		* @brief constructor
		* @input parameter: base error[int]
		*/
		IO_SENSORS_BASE_CLASS(int error_code):m_base_error_code(error_code){}

		/*
		* @brief deconstructor
		*/
		virtual ~IO_SENSORS_BASE_CLASS(){}

		/************************************
		*@ Method:    pair_sensor
		*@ FullName:  IO_SENSORS_BASE_CLASS<SENSOR_TYPE>::pair_sensor
		*@ Access:    public
		*@ Returns:   void
		*@ Qualifier:
		*@ Parameter: const SENSOR_TYPE & id
		*@ Parameter: const IO_SENSORS & instance
		*@ Description:
		*************************************/
		void pair_sensor(const SENSOR_TYPE & id, W * instance)
		{
			this->insert(make_pair(id,instance));
		}

		/************************************
		*@ Method:    read
		*@ FullName:  IO_SENSORS_BASE_CLASS<T>::read
		*@ Access:    virtual public
		*@ Returns:   int
		*@ Qualifier:
		*@ Parameter: T * present
		*@ Description:
		*************************************/
		template<typename T>
		int read(T * value)
		{
            const char* func_name = "read";
            TR4A_trace(COMPONENT_ID,
                TR4A_TRACE_INT,
                func_name,
                " > ()");

			if(this->find(this->m_id) != this->end())
			{
				if (0 != this->operator [](this->m_id)->read(value))
				{
					return this->m_base_error_code;
				}
			}
			else
			{
				return this->m_base_error_code;
			}

            TR4A_trace(COMPONENT_ID,
                            TR4A_TRACE_INT,
                            func_name,
                            " < ()");

			return 0;
		}

		/************************************
		*@ Method:    set_sensor_id
		*@ FullName:  IO_SENSORS_BASE_CLASS<SENSOR_TYPE>::set_sensor_id
		*@ Access:    public
		*@ Returns:   void
		*@ Qualifier:
		*@ Parameter: const SENSOR_TYPE & id
		*@ Description:
		*************************************/
		void set_sensor_id(const SENSOR_TYPE & id)
		{
			this->m_id = id;
		}

		/************************************
		*@ Method:    get_sensor_id
		*@ FullName:  IO_SENSORS_BASE_CLASS<SENSOR_TYPE, D>::get_sensor_id
		*@ Access:    public
		*@ Returns:   SENSOR_TYPE
		*@ Qualifier: const
		*@ Description:
		*************************************/
		SENSOR_TYPE get_sensor_id() const
		{
			return this->m_id;
		}

	protected:
	private:
		/*
		* @brief sensor type
		*/
		SENSOR_TYPE m_id;

		/*
		* @brief base error code
		*/
		int m_base_error_code;
		//enum{ m_error_code = IO_SENSOR_BASE_ERR};
	};
}
//#endif // IO_SENSORS_CLASS_HPP__

