/********************************************************************
	Copyright (C) 2015, �Ϻ�΢����װ�����޹�˾
    All rights reserved.
	created:	2016/05/23
	created:	23:5:2016   15:33
	filename: 	e:\ROBOT_WORKFLOW\ROBOT\ROBOT\WR_ENUM_TO_STRING.h
	file path:	e:\ROBOT_WORKFLOW\ROBOT\ROBOT
	file base:	WR_ENUM_TO_STRING
	file ext:	h
	author:		sunww
	purpose:	
	��Ʒ�ţ�     SSB509
	���������   WU
    ��ʷ��¼��
    �汾       ��  ��      ��  ��           ��    ��
	1.0.0    23/5/2016    sunww            �½�.
*********************************************************************/
#ifndef WR_ENUM_TO_STRING_H_
#define WR_ENUM_TO_STRING_H_

#include "STRING_REGISTER_CLASS.h"
#include "WR4A_tc.h"
namespace WRH
{
	namespace WR
	{
		REGISTER_ENUM_BEGIN(WR4T_ARM_STATION_ENUM)
		{
			REGISTER_ENUM(WR4T_ARM_STATION_A);
			REGISTER_ENUM(WR4T_ARM_STATION_B);
		}
		REGISTER_ENUM_END;
	}
}
#endif // WR_ENUM_TO_STRING_H_