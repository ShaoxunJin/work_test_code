/**************************************************************************
 * Copyright (C) 2010, 上海微电子装备有限公司
 * All rights reserved.
 * 产品号：  SSA800/10
 * 所属组件：WC
 * 文件名称：WC4A_tc.h
 * 概要描述：
 * 历史记录：
 * 版本       日  期      作  者          内    容
 * V1.0    2014-5-20     sunlf             创建文件
 *************************************************************************/
#ifndef WC4A_TC_H
#define WC4A_TC_H
#include "smee.h"
#include "WCMC_tc.h"
//#include "WRH_BASE.h"


//对外错误码定义
#define WC4A_BASE_ERROR             (0x57430000) 			//"WC" 模块错误码基址

/*<ErrBegin>*/
#define WC4A_SYSTEM_ERROR           (WC4A_BASE_ERROR + 0x01)//致命错误，出现时通常意味着要重新初始化
#define WC4A_PARAMETER_ERROR        (WC4A_BASE_ERROR + 0x02)//参数错误，表明参数越界
#define WC4A_ILLEGAL_CALL_ERROR     (WC4A_BASE_ERROR + 0x03)//状态错误，表明当前接口不能在当前状态下调用
#define WC4A_INVALID_STATE_ERROR    (WC4A_BASE_ERROR + 0x04)//超时错误，表明接口调用超时
/*<ErrEnd>*/

//定义槽号数
#define WC4A_MAX_SLOT_NBR 25

//定义carrier id 字符串长度
#define WC4A_MAX_CARRIER_ID_SIZE 30

//定义cassette id 长度


// 片库设备状态
typedef enum
{
    WC4A_PE_ST_MIN = 0,
    WC4A_PE_ST_UNKNOWN,
    WC4A_PE_ST_TERMINATED,
    WC4A_PE_ST_INITIALIZED,
    WC4A_PE_ST_BUSY,
    WC4A_PE_ST_MAX
} WC4A_PE_STATE_ENUM;


// Carrier状态
typedef enum
{
    WC4A_CARRIER_STATE_MIN = 0,
    WC4A_CARRIER_NOT_PRESENT,
    WC4A_CARRIER_PRESENT,           // 片盒存在
    WC4A_CARRIER_LOCKED,            // 片盒存在并且被锁定，尚未扫描
    WC4A_CARRIER_MAPPED,            // 片盒存在且锁定且扫描
    WC4A_CARRIER_BUSY,              // 正在执行装载或卸载动作
    WC4A_CARRIER_STATE_MAX
} WC4A_CARRIER_STATE_ENUM;

// 片库垂向工位定义
typedef enum
{
    WC4A_Z_STATION_MIN = 0,
    WC4A_Z_DOCK,         // dock轴水平运动高度
    WC4A_Z_SWING_IN,     //旋转轴转入的高度
    WC4A_Z_END_SCAN,     // 结束扫描的高度
    WC4A_Z_START_SCAN,   // 开始扫描的高度
    WC4A_Z_LATCH,        // 开合片盒门的垂向高度
    WC4A_Z_EXCHANGE,       // 人机交界高度
    WC4A_Z_TOP_SLOT,
    WC4A_Z_UNKNOWN,
    WC4A_Z_STATION_MAX
} WC4A_Z_STATION_ENUM;

// 片库轴定义
//typedef enum
//{
//    WC4A_AX_MIN = 0,
//    WC4A_Z,            // 升降轴
//    WC4A_SWING,    //片库旋转轴
//    WC4A_DOCK,         // DOCK轴?
//    WC4A_LATCH_H,        // LATCH轴，开合片盒门
//    WC4A_LATCH_R,     // LATCH旋转轴
//    WC4A_MAPPER,       // 片库mapper轴
//    WC4A_AX_MAX
//} WC4A_AX_ENUM;

// 片库指示灯定义
typedef enum
{
    WC4A_LED_MIN = 0,
    WC4A_LED_LOAD,     //load按钮指示灯绿色
    WC4A_LED_UNLOAD,   //unload按钮指示灯绿色
    WC4A_LED_CARRIER_PRESENT,   //片盒存在
    WC4A_LED_FOUP_ERROR, //片盒有问题如放置问题，突片问题  红色
    WC4A_LED_LOAD_UNLOAD_READY, //绿色
    WC4A_LED_MAX
} WC4A_INDICATOR_ENUM;

//定义id 类型 carrier id cassette id
typedef enum
{
    WC4A_ID_TYPE_MIN=0,
	WC4A_ID_TYPE_CARRIER_ID,  //片盒id
	WC4A_ID_TYPE_CASSETTE_ID, //OCA cassette id
	WC4A_ID_TYPE_MAX

} WC4A_ID_TYPE_ENUM;


// 硅片扫描结果枚举
typedef enum
{
    WC4A_SLOT_INFO_MIN=0,
    WC4A_NO_WAFER,               // 槽内无硅片
    WC4A_NORMALLY_INSERT,        // 正确插入
    WC4A_CROSS_SLOT,             // 跨槽
    WC4A_DOUBLE_SLOT,            // 叠片
    WC4A_SLOT_INFO_MAX
} WC4A_SLOT_INFO_ENUM;


// 片库状态信息
typedef struct
{
    WC4A_PE_STATE_ENUM state;        //pe state
    WC4A_CARRIER_STATE_ENUM carrier_state; //carrier state
    WC4A_Z_STATION_ENUM  z_station;
    WC4A_SLOT_INFO_ENUM slot_info[WC4A_MAX_SLOT_NBR];
	SMEE_BOOL filler;
} WC4A_STATUS_STRUCT;
#endif

