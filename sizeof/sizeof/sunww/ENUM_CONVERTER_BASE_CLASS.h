/********************************************************************
	Copyright (C) 2015, �Ϻ�΢����װ�����޹�˾
    All rights reserved.
	created:	2015/09/18
	created:	18:9:2015   16:47
	filename: 	e:\205C\WU_workflow\WU\WU\ENUM_CONVERTER_BASE_CLASS.h
	file path:	e:\205C\WU_workflow\WU\WU
	file base:	ENUM_CONVERTER_BASE_CLASS
	file ext:	h
	author:		sunww
	purpose:
	��Ʒ�ţ�     SSB509
	���������   WU
    ��ʷ��¼��
    �汾       ��  ��      ��  ��           ��    ��
	1.0.0    18/9/2015    sunww            �½�.
*********************************************************************/
#ifndef ENUM_CONVERTER_BASE_CLASS_H_
#define ENUM_CONVERTER_BASE_CLASS_H_

/*##########################################################################*
Header File
*###########################################################################*/
#include <iostream>
#include <string>
#include <map>

/*##########################################################################*
Function Declaration
*###########################################################################*/
#define REGISTER_ENUM_BEGIN(name)   class ENUM_##name :public ENUM_BASE_CONVERTER_CLASS<name>\
									{\
									public: \
									static ENUM_##name* instance()\
									{\
										static ENUM_##name* conv = new ENUM_##name();\
										return conv;\
									}\
									~ENUM_##name(){}\
									ENUM_##name()


#define REGISTER_ENUM(item)                 this->operator[](#item) = item

#define REGISTER_ENUM_END           }

#define ENUM_CONVERTER(name)        		ENUM_##name

#define ENUM_CONVERTER_INSTANCE(name)       ENUM_##name::instance()

#define ENUM_CONVERTER_STR(type_t,id)     	ENUM_##type_t::instance()->to_string(id)

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
		for (typename std::map<const char*, E>::iterator i = this->begin(); i != this->end(); i++)
		{
			if (i->second == value)
			{
				return i->first;
			}
		}
		return "";
	}
};

#endif /* ENUM_BASE_CONVERTER_CLASS_H_ */

