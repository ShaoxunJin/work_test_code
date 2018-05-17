/********************************************************************
	Copyright (C) 2015, 上海微电子装备有限公司
    All rights reserved.
	created:	2016/05/23
	created:	23:5:2016   15:33
	filename: 	e:\ROBOT_WORKFLOW\ROBOT\ROBOT\WR_ENUM_TO_STRING.h
	file path:	e:\ROBOT_WORKFLOW\ROBOT\ROBOT
	file base:	WR_ENUM_TO_STRING
	file ext:	h
	author:		sunww
	purpose:	
	产品号：     SSB509
	所属组件：   WU
    历史记录：
    版本       日  期      作  者           内    容
	1.0.0    23/5/2016    sunww            新建.
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