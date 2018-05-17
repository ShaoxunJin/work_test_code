/**************************************************************
* Copyright (C) 2006, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A800/10
* 所属组件 :WH
* 模块名称 :WCMC
* 文件名称 :WCMC_tc.h
* 概要描述 :片库机器常数结构定义
* 历史记录 :
* 版本      日期         作者    内容
* V1.0    2013-12-20   sunlf
***************************************************************/
#ifndef WCMC_TC_H
#define WCMC_TC_H

#include "smee.h"


typedef struct
{
    SMEE_DOUBLE normal_inserted_area_low;        			//<default>0<unit>m<range><description>正常放置硅片所占区域相对于pitch的百分比下限；
    SMEE_DOUBLE normal_inserted_area_high;		 			//<default>0<unit>m<range><description>正常放置硅片所占区域相对于pitch的百分比上限；
    SMEE_INT32 doubled_min;                  	 			//<default>0<unit>m<range><description>叠片的最小阈值/有片的最大阈值；
    SMEE_INT32 update_rate;                  	 			//<default>0<unit>Hz<range><description>数据采集频率；
    SMEE_DOUBLE scan_velocity;                	 			//<default>0<unit>m/s<range><description>扫描速度；
    SMEE_DOUBLE scan_to_exchange_distance;   	 			//<default>0<unit>m<range><description>机械手交接高度与扫描高度偏移值；
    SMEE_DOUBLE pitch;                       	 			//<default>0<unit>m<range><description>槽之间的高度差；
} WCMC_ALG_PARAMETER_STRUCT;

typedef struct
{
	SMEE_DOUBLE dock;                	//<default>0<unit>m<range><description>允许dock的高度；
    SMEE_DOUBLE swing;               	//<default>0<unit>m<range><description>允许swing的高度；
    SMEE_DOUBLE latch;              	//<default>0<unit>m<range><description>允许latch的高度；
	SMEE_DOUBLE exchange;            	//<default>0<unit>m<range><description>取放片盒高度；
    SMEE_DOUBLE top_slot;            	//<default>0<unit>m<range><description>扫描到25th硅片中间时编码器值；
} WCMC_Z_STATION_STRUCT;

typedef struct
{
    SMEE_DOUBLE lock;    				//<default>0<unit>m<range><description>锁定；
    SMEE_DOUBLE unlock;  				//<default>0<unit>m<range><description>解锁；
}WCMC_LOCK_AND_LATCH_KEY_STATION_PARAMETER_STRUCT;

typedef struct
{
    SMEE_DOUBLE extend;  				//<default>0<unit>m<range><description>伸出值；
    SMEE_DOUBLE retract; 				//<default>0<unit>m<range><description>缩回值；
} WCMC_STATION_PARAMETER_STRUCT;



typedef struct
{
    SMEE_DOUBLE swing_in;				//<default>0<unit>rad<range><description>转入；
    SMEE_DOUBLE swing_out;  			//<default>0<unit>rad<range><description>转出；
}WCMC_SWING_STATION_PARAMETER_STRUCT;


typedef struct
{
    WCMC_Z_STATION_STRUCT z;                   					// Z工位坐标
    WCMC_SWING_STATION_PARAMETER_STRUCT swing;       			// swing工位坐标
	WCMC_STATION_PARAMETER_STRUCT dock;        					// Dock工位坐标
    WCMC_STATION_PARAMETER_STRUCT latch_h;       				// Latch工位坐标
    WCMC_LOCK_AND_LATCH_KEY_STATION_PARAMETER_STRUCT latch_r;   // Latch r工位坐标
    WCMC_STATION_PARAMETER_STRUCT mapper;          				// Mapper工位坐标
} WCMC_STATION_STRUCT;

/***片库机器常数***/
typedef struct
{
    WCMC_STATION_STRUCT station;
    WCMC_ALG_PARAMETER_STRUCT alg;   // 算法参数
    //SMEE_BOOL auto_unload;  //<default>0<unit><range>[0,1]<description>是否自动unload而不是通过按钮来unload
} WCMC_FILE_STRUCT;
#endif

