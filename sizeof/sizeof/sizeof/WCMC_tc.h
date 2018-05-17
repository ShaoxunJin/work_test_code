/**************************************************************
* Copyright (C) 2006, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS A800/10
* ������� :WH
* ģ������ :WCMC
* �ļ����� :WCMC_tc.h
* ��Ҫ���� :Ƭ����������ṹ����
* ��ʷ��¼ :
* �汾      ����         ����    ����
* V1.0    2013-12-20   sunlf
***************************************************************/
#ifndef WCMC_TC_H
#define WCMC_TC_H

#include "smee.h"


typedef struct
{
    SMEE_DOUBLE normal_inserted_area_low;        			//<default>0<unit>m<range><description>�������ù�Ƭ��ռ���������pitch�İٷֱ����ޣ�
    SMEE_DOUBLE normal_inserted_area_high;		 			//<default>0<unit>m<range><description>�������ù�Ƭ��ռ���������pitch�İٷֱ����ޣ�
    SMEE_INT32 doubled_min;                  	 			//<default>0<unit>m<range><description>��Ƭ����С��ֵ/��Ƭ�������ֵ��
    SMEE_INT32 update_rate;                  	 			//<default>0<unit>Hz<range><description>���ݲɼ�Ƶ�ʣ�
    SMEE_DOUBLE scan_velocity;                	 			//<default>0<unit>m/s<range><description>ɨ���ٶȣ�
    SMEE_DOUBLE scan_to_exchange_distance;   	 			//<default>0<unit>m<range><description>��е�ֽ��Ӹ߶���ɨ��߶�ƫ��ֵ��
    SMEE_DOUBLE pitch;                       	 			//<default>0<unit>m<range><description>��֮��ĸ߶Ȳ
} WCMC_ALG_PARAMETER_STRUCT;

typedef struct
{
	SMEE_DOUBLE dock;                	//<default>0<unit>m<range><description>����dock�ĸ߶ȣ�
    SMEE_DOUBLE swing;               	//<default>0<unit>m<range><description>����swing�ĸ߶ȣ�
    SMEE_DOUBLE latch;              	//<default>0<unit>m<range><description>����latch�ĸ߶ȣ�
	SMEE_DOUBLE exchange;            	//<default>0<unit>m<range><description>ȡ��Ƭ�и߶ȣ�
    SMEE_DOUBLE top_slot;            	//<default>0<unit>m<range><description>ɨ�赽25th��Ƭ�м�ʱ������ֵ��
} WCMC_Z_STATION_STRUCT;

typedef struct
{
    SMEE_DOUBLE lock;    				//<default>0<unit>m<range><description>������
    SMEE_DOUBLE unlock;  				//<default>0<unit>m<range><description>������
}WCMC_LOCK_AND_LATCH_KEY_STATION_PARAMETER_STRUCT;

typedef struct
{
    SMEE_DOUBLE extend;  				//<default>0<unit>m<range><description>���ֵ��
    SMEE_DOUBLE retract; 				//<default>0<unit>m<range><description>����ֵ��
} WCMC_STATION_PARAMETER_STRUCT;



typedef struct
{
    SMEE_DOUBLE swing_in;				//<default>0<unit>rad<range><description>ת�룻
    SMEE_DOUBLE swing_out;  			//<default>0<unit>rad<range><description>ת����
}WCMC_SWING_STATION_PARAMETER_STRUCT;


typedef struct
{
    WCMC_Z_STATION_STRUCT z;                   					// Z��λ����
    WCMC_SWING_STATION_PARAMETER_STRUCT swing;       			// swing��λ����
	WCMC_STATION_PARAMETER_STRUCT dock;        					// Dock��λ����
    WCMC_STATION_PARAMETER_STRUCT latch_h;       				// Latch��λ����
    WCMC_LOCK_AND_LATCH_KEY_STATION_PARAMETER_STRUCT latch_r;   // Latch r��λ����
    WCMC_STATION_PARAMETER_STRUCT mapper;          				// Mapper��λ����
} WCMC_STATION_STRUCT;

/***Ƭ���������***/
typedef struct
{
    WCMC_STATION_STRUCT station;
    WCMC_ALG_PARAMETER_STRUCT alg;   // �㷨����
    //SMEE_BOOL auto_unload;  //<default>0<unit><range>[0,1]<description>�Ƿ��Զ�unload������ͨ����ť��unload
} WCMC_FILE_STRUCT;
#endif

