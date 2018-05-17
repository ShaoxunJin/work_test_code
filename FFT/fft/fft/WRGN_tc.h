/*******************************************************************************
* Copyright (C) 2005, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS B500/10M
* 所属组件 : RH,WH
* 模块名称 : WRGN
* 文件名称 : WRGN_tc.h
* 概要描述 :本模块用于WH,RH公共库头文件
* 历史记录 :
* 版本   日期    作者   内容
* 1.0    2011-2-16 zhengjz 建立    …     …
******************************************************************************/
#ifndef _WRGN_TC_H_
#define _WRGN_TC_H_

#include "ss600.h"
#include "smee.h"
#include <stdio.h>

//#include <poll.h>
//#include <QTableWidget>

//#include "HWGN4T_if.h"
//#include "math.h"
//#include "HWVPSP.h"

//#include "EH4A_if.h"
//#include "TR4A_if.h"
//#include "MF4A_if.h"
#include "GNMA.h"

#define IN
#define OUT
#define IO

/*ERROR CODE*/
#define WRGN_BASE_ERROR 0x57520000

/*功能函数出错*/
#define WRGN_CAL_STABLE_ERROR (WRGN_BASE_ERROR +0x10)
#define WRGN_NORM_RANDOM_ERROR_FAILED (WRGN_BASE_ERROR +0x11)
#define WRGN_MEASURED_MASS_ERROR (WRGN_BASE_ERROR +0x12)
#define WRGN_BODE_ERROR (WRGN_BASE_ERROR +0x13)
#define WRGN_SPECTRUM_ERROR (WRGN_BASE_ERROR +0x14)
#define WRGN_CAL_OPENLOOP_ERROR (WRGN_BASE_ERROR +0x15)
//#define WRGN_HR_CAL_TF_ERROR (WRGN_BASE_ERROR +0x16)
#define WRGN_HW_CAL_TF_ERROR (WRGN_BASE_ERROR +0x17)
//#define WRGN_HR_TRACE_TF_ERROR  (WRGN_BASE_ERROR +0x18)
#define WRGN_HW_TRACE_TF_ERROR (WRGN_BASE_ERROR +0x19)
#define WRGN_CAL_SETTLING_TIME_ERROR (WRGN_BASE_ERROR +0x1A)
/**/
#define WRGN_PARAM_ERROR	(WRGN_BASE_ERROR +0x40)	//计算NRE的输入参数出错
#define WRGN_MEASURED_MASS_IS_ZERO_ERROR (WRGN_BASE_ERROR +0x41)	//计算质量时分母为0；
#define WRGN_BANDWIDTH_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x42)	//带宽未找到出错
#define WRGN_AMPLTITUDE_MARGIN_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x43)	//幅值裕度未找到
#define WRGN_PHASE_MARGIN_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x44)	//相位裕度未找到
#define WRGN_NRE_LESS_THAN_ZERO	(WRGN_BASE_ERROR +0x45)	//计算得到的NRE小于0
#define WRGN_STABLE_TIME_TOO_LONG_ERROR	(WRGN_BASE_ERROR +0x46)	//计算得到的NRE小于0
#define WRGN_REACH_SET_ERR_WINDOW_FAILED	(WRGN_BASE_ERROR +0x47)


#define WRGN_TRACE_DATA_NUMBER 2048
#define WRGN_MAX_TRANSFER_TYPE 6
#define WRGN_PI 3.14159265

typedef enum
{
    WRGN_MECHANICS,          //测试机械传函
    WRGN_CONTROLLER,         //测试控制传函
    WRGN_OPENTOTAL,          //测试开环总传函
    WRGN_CLOSEDLOOP,         //测试闭环传函
    WRGN_SENSITIVITY,        // 测试敏感度传函
    WRGN_PROCESSSENSITIVITY //测试过程敏感度传函
}WRGN_TRANSFER_TYPE_ENUM;

typedef struct
{
    double freq[WRGN_TRACE_DATA_NUMBER];
    double mag[WRGN_TRACE_DATA_NUMBER];
    double phase[WRGN_TRACE_DATA_NUMBER];
    double cohere[WRGN_TRACE_DATA_NUMBER];
}WRGN_BODE_STRUCT;

typedef struct
{
    double Pxx[WRGN_TRACE_DATA_NUMBER];
    double Pyy[WRGN_TRACE_DATA_NUMBER];
    GNMA_complex_type Pxy[WRGN_TRACE_DATA_NUMBER];
}WRGN_SPECTRUM_STRUCT;

typedef struct
{
  double dBandwidth;   //传函带宽；
  double dMagnt_margin;  //传函幅值裕度
  double dPhase_margin;   //传函相位裕度
}WRGN_OPEN_LOOP_RESULT_STRUCT;

typedef struct{

	SMEE_BOOL bMechanical;   //测试机械传函
	SMEE_BOOL bController;     //测试控制传函
	SMEE_BOOL bOpenTotal;    //测试开环总传函
	SMEE_BOOL bClosedLoop;   //测试闭环传函
	SMEE_BOOL bSensity;      // 测试敏感度传函
	SMEE_BOOL bProcessSensity; //测试过程敏感度传函

}WRGN_TRANSFER_TYPE_STRUCT;

typedef struct{

	WRGN_BODE_STRUCT sMechanical;    //机械传函的Bode图输出
	WRGN_BODE_STRUCT sControl;      //控制器传函的Bode图输出
	WRGN_BODE_STRUCT sOpenTotal;     //开环总传函的Bode图输出
	WRGN_BODE_STRUCT sClosedLoop;    //闭环传函的Bode图输出
	WRGN_BODE_STRUCT sSensity;        //敏感度传函传函的Bode图输出
	WRGN_BODE_STRUCT sProcessSensity;//过程敏感度传函的Bode图输出

} WRGN_TF_STRUCT;
//typedef struct
//{
//	SMEE_BOOL b0dbTooMany;	//SMEE_TRUE表示0分贝点太多了，总数超过5个
//	int i0dbNbr;			//0分贝点的个数
//	double d0db[5];			//0分贝点的位置，从低频往高频排列，共i0dbNbr个
//	SMEE_BOOL b180TooMany;	//SMEE_TRUE表示－180度点太多了，总数超过5个
//	int i180Nbr;			//－180度点的个数
//	double d180[5];			//－180度点的位置，从低频往高频排列，共i180Nbr个
//}WRGN_HIGH_STRUCT;
#endif


