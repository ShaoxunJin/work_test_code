/**************************************************************************
 * Copyright (C) 2010, 上海微电子装备有限公司
 * All rights reserved.
 * 产品号：  SSA800/10
 * 所属组件：WH
 * 文件名称：WR_tc.h
 * 概要描述：
 * 历史记录：
 * 版本       日  期      作  者          内    容
 * V1.0     2013-12-18    sunlf            创建
 * V1.1     2014-6-30     sunlf            按照意见修改
 *************************************************************************/
#ifndef WR4A_TC_H
#define WR4A_TC_H
#include"smee.h"
//#include"WRMC_tc.h"


//对外错误码定义
#define WR4A_BASE_ERROR             (0x57520000 + 0x100) //"WR" 模块错误码基址
/*<ErrBegin>*/
#define WR4A_SYSTEM_ERROR           (WR4A_BASE_ERROR + 0x01)// 致命错误，出现时通常意味着要重新初始化设备
#define WR4A_PARAMETER_ERROR        (WR4A_BASE_ERROR + 0x02)// 参数错误，表明参数越界
#define WR4A_ILLEGAL_CALL_ERROR     (WR4A_BASE_ERROR + 0x03)// 状态错误，表明当前接口不能在当前状态下调用
/*<ErrEnd>*/


/***机械手轴枚举定义***/
typedef enum
{
    WR4A_AXIS_MIN =0,
    WR4A_AXIS_T,       //按照milara手顺序
    WR4A_AXIS_R,
    WR4A_AXIS_Z,
    WR4A_AXIS_MAX
} WR4A_AXIS_ENUM;


/***机械手工位枚举***/
typedef enum
{
    WR4A_STATION_MIN = 0,
	WR4A_STATION_UNKNOWN,
	WR4A_STATION_HOME,                 //home 工位
	WR4A_STATION_PREALIGNER_AT,        //预对准交接位
	WR4A_STATION_CARRIER_AT,           //片库位
	WR4A_STATION_WAFER_STAGE_LOAD,     //工件台load侧
	WR4A_STATION_WAFER_STAGE_UNLOAD,   //工件台unload侧
    WR4A_STATION_DISCHARGE,            //下片台
    WR4A_STATION_MAX

} WR4A_STATION_ENUM;

/***机械手设备状态枚举***/
typedef enum
{
    WR4A_PE_ST_MIN = 0,
    WR4A_PE_ST_UNKNOWN,
    WR4A_PE_ST_TERMINATED,
    WR4A_PE_ST_INITIALIZED,        //初始化
    WR4A_PE_ST_BUSY,              //设备忙
    WR4A_PE_ST_MAX
} WR4A_PE_STATE_ENUM;

/***机械手安全区域枚举***/
typedef enum
{
    WR4A_AREA_ST_MIN = 0,
    WR4A_AREA_ST_SAFE,            //机械手在安全区域
    WR4A_AREA_ST_UNSAFE,          //机械手在不安全区域  比如片叉在片库里面
    WR4A_AREA_ST_MAX
} WR4A_AREA_STATE_ENUM;

/***机械手pickup 位置枚举***/
typedef enum
{
    WR4A_STATION_UP_DOWN_MIN=0,
	WR4A_STATION_ABOVE,          //交接高位
	WR4A_STATION_EXCHANGE,       //交接位
	WR4A_STATION_BELOW,          //交接低位
	WR4A_STATION_UP_DOWN_MAX
} WR4A_STATION_UP_DOWN_ENUM;


/***机械手所处区域区域结构体***/
typedef struct
{
    WR4A_AREA_STATE_ENUM carrier_area;
	WR4A_AREA_STATE_ENUM prealigner_area;
	WR4A_AREA_STATE_ENUM wafer_stage_area;
	WR4A_AREA_STATE_ENUM discharge_area;
	WR4A_AREA_STATE_ENUM robot_area;
	SMEE_BOOL            filler;
} WR4A_AREA_STRUCT;


/*****机械手轴状态****/
typedef struct
{
    SMEE_BOOL homed;            //是否home
	SMEE_INT32 position;        //位置

} WR4A_AXIS_STRUCT;

/***机械手quadcell结构体***/
typedef struct
{
    SMEE_INT32 raw_a;			//四象限原始(测量)值
    SMEE_INT32 raw_b;
    SMEE_INT32 raw_c;
    SMEE_INT32 raw_d;
} WR4A_QUADCELL_RAW_DATA_STRUCT;

/***机械手quadcell结构体***/
typedef struct
{
    SMEE_DOUBLE convert_a;		//四象限转换(标称)值
    SMEE_DOUBLE convert_b;
    SMEE_DOUBLE convert_c;
    SMEE_DOUBLE convert_d;
} WR4A_QUADCELL_CONVERT_DATA_STRUCT;


/***机械手设备quadcell状态***/
typedef struct
{
    WR4A_QUADCELL_RAW_DATA_STRUCT      segment;			//quadcell 原始值
	WR4A_QUADCELL_CONVERT_DATA_STRUCT  segment_convert;	// 转换值
    xy_vect       displacement;							//
    SMEE_BOOL     out_of_range;							//是否超出范围
	SMEE_BOOL     docked_ok;
	SMEE_BOOL     z_sensor;
	SMEE_BOOL     filler;
} WR4A_QUAD_CELL_STRUCT;


/***机械手状况结构体***/
typedef struct
{
    WR4A_PE_STATE_ENUM state;   			//机械手设备状态机
    WR4A_STATION_ENUM station;  			//机械手工位
	WR4A_QUAD_CELL_STRUCT dock_state;  		//DOCK状态
	WR4A_AXIS_STRUCT  axis[WR4A_AXIS_MAX];	//轴所在位置
	WR4A_AREA_STRUCT  area;       			//机械手所处区域
    SMEE_BOOL wafer_present;
    SMEE_INT32 filler;

} WR4A_STATUS_STRUCT;

/***机械手订阅结构体***/
typedef struct
{
   WR4A_PE_STATE_ENUM state;   //机械手设备状态机
   WR4A_STATION_ENUM station;  //机械手工位
   SMEE_BOOL wafer_present;
   SMEE_INT32 filler;

} WR4A_SUBSCRIBE_STATUS_STRUCT;


#endif

