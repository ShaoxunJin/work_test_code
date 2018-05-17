/********************************************************************
	Copyright (C) 2015, 上海微电子装备有限公司
    All rights reserved.
	created:	2016/05/23
	created:	23:5:2016   14:49
	filename: 	e:\ROBOT_WORKFLOW\ROBOT\ROBOT\STRING_REGISTER_CLASS.h
	file path:	e:\ROBOT_WORKFLOW\ROBOT\ROBOT
	file base:	STRING_REGISTER_CLASS
	file ext:	h
	author:		sunww
	purpose:	
	产品号：     SSB509
	所属组件：   WU
    历史记录：
    版本       日  期      作  者           内    容
	1.0.0    23/5/2016    sunww            新建.
*********************************************************************/
#ifndef STRING_REGISTER_CLASS_H_
#define STRING_REGISTER_CLASS_H_

#include <map>
namespace WRH
{
	namespace WR
	{
/*##########################################################################*
Function Declaration
*###########################################################################*/
#define REGISTER_ENUM_BEGIN(name)   class t_##_str :public ENUM_BASE_CONVERTER_CLASS<name>\
		{\
		public: \
			~t_##_str(){}\
			t_##_str(){

#define REGISTER_ENUM(item)                 this->operator[](#item) = item

#define REGISTER_ENUM_END           }

		template<typename E>
		class ENUM_BASE_CONVERTER_CLASS : public std::map<const char*, E>
		{
		public:
			/**
			* Convert from string to enum
			* @param value is output enum value
			* @param text is enum string
			* @return TRUE if found enum, otherwise return FALSE
			*/
			bool to_enum(E& value, const char* str)
			{
				for (typename std::map<const char*, E>::iterator i = this->begin(); i != this->end(); i++)
				{
					if (strcmp(i->first, str) == 0)
					{
						value = i->second;
						return true;
					}
				}
				return false;
			}

			/**
			* Convert from enum to string
			* @param value is enum value
			* @return string of enum
			*/
			const char* to_string(E value)
			{
				const char* result = NULL;
				typename std::map<const char*, E>::iterator i = this->begin();
				while ( i != this->end())
				{
					if (i->second == value)
					{
						 result = i->first;
						 break;
					}
					i++; 
				}

				if (i == this->end())
				{
					throw ("enum not exist in the data base");
				}

				return result;
			}
		};
	}
}
#endif // STRING_REGISTER_CLASS_H_