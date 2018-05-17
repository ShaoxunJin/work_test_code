/**************************************************************************
 * Copyright (C) 2010, �Ϻ�΢����װ�����޹�˾
 * All rights reserved.
 * ��Ʒ�ţ�  SSA800/10
 * ���������WH
 * �ļ����ƣ�WR_tc.h
 * ��Ҫ������
 * ��ʷ��¼��
 * �汾       ��  ��      ��  ��          ��    ��
 * V1.0     2013-12-18    sunlf            ����
 * V1.1     2014-6-30     sunlf            ��������޸�
 *************************************************************************/
#ifndef WR4A_TC_H
#define WR4A_TC_H
#include"smee.h"
//#include"WRMC_tc.h"


//��������붨��
#define WR4A_BASE_ERROR             (0x57520000 + 0x100) //"WR" ģ��������ַ
/*<ErrBegin>*/
#define WR4A_SYSTEM_ERROR           (WR4A_BASE_ERROR + 0x01)// �������󣬳���ʱͨ����ζ��Ҫ���³�ʼ���豸
#define WR4A_PARAMETER_ERROR        (WR4A_BASE_ERROR + 0x02)// �������󣬱�������Խ��
#define WR4A_ILLEGAL_CALL_ERROR     (WR4A_BASE_ERROR + 0x03)// ״̬���󣬱�����ǰ�ӿڲ����ڵ�ǰ״̬�µ���
/*<ErrEnd>*/


/***��е����ö�ٶ���***/
typedef enum
{
    WR4A_AXIS_MIN =0,
    WR4A_AXIS_T,       //����milara��˳��
    WR4A_AXIS_R,
    WR4A_AXIS_Z,
    WR4A_AXIS_MAX
} WR4A_AXIS_ENUM;


/***��е�ֹ�λö��***/
typedef enum
{
    WR4A_STATION_MIN = 0,
	WR4A_STATION_UNKNOWN,
	WR4A_STATION_HOME,                 //home ��λ
	WR4A_STATION_PREALIGNER_AT,        //Ԥ��׼����λ
	WR4A_STATION_CARRIER_AT,           //Ƭ��λ
	WR4A_STATION_WAFER_STAGE_LOAD,     //����̨load��
	WR4A_STATION_WAFER_STAGE_UNLOAD,   //����̨unload��
    WR4A_STATION_DISCHARGE,            //��Ƭ̨
    WR4A_STATION_MAX

} WR4A_STATION_ENUM;

/***��е���豸״̬ö��***/
typedef enum
{
    WR4A_PE_ST_MIN = 0,
    WR4A_PE_ST_UNKNOWN,
    WR4A_PE_ST_TERMINATED,
    WR4A_PE_ST_INITIALIZED,        //��ʼ��
    WR4A_PE_ST_BUSY,              //�豸æ
    WR4A_PE_ST_MAX
} WR4A_PE_STATE_ENUM;

/***��е�ְ�ȫ����ö��***/
typedef enum
{
    WR4A_AREA_ST_MIN = 0,
    WR4A_AREA_ST_SAFE,            //��е���ڰ�ȫ����
    WR4A_AREA_ST_UNSAFE,          //��е���ڲ���ȫ����  ����Ƭ����Ƭ������
    WR4A_AREA_ST_MAX
} WR4A_AREA_STATE_ENUM;

/***��е��pickup λ��ö��***/
typedef enum
{
    WR4A_STATION_UP_DOWN_MIN=0,
	WR4A_STATION_ABOVE,          //���Ӹ�λ
	WR4A_STATION_EXCHANGE,       //����λ
	WR4A_STATION_BELOW,          //���ӵ�λ
	WR4A_STATION_UP_DOWN_MAX
} WR4A_STATION_UP_DOWN_ENUM;


/***��е��������������ṹ��***/
typedef struct
{
    WR4A_AREA_STATE_ENUM carrier_area;
	WR4A_AREA_STATE_ENUM prealigner_area;
	WR4A_AREA_STATE_ENUM wafer_stage_area;
	WR4A_AREA_STATE_ENUM discharge_area;
	WR4A_AREA_STATE_ENUM robot_area;
	SMEE_BOOL            filler;
} WR4A_AREA_STRUCT;


/*****��е����״̬****/
typedef struct
{
    SMEE_BOOL homed;            //�Ƿ�home
	SMEE_INT32 position;        //λ��

} WR4A_AXIS_STRUCT;

/***��е��quadcell�ṹ��***/
typedef struct
{
    SMEE_INT32 raw_a;			//������ԭʼ(����)ֵ
    SMEE_INT32 raw_b;
    SMEE_INT32 raw_c;
    SMEE_INT32 raw_d;
} WR4A_QUADCELL_RAW_DATA_STRUCT;

/***��е��quadcell�ṹ��***/
typedef struct
{
    SMEE_DOUBLE convert_a;		//������ת��(���)ֵ
    SMEE_DOUBLE convert_b;
    SMEE_DOUBLE convert_c;
    SMEE_DOUBLE convert_d;
} WR4A_QUADCELL_CONVERT_DATA_STRUCT;


/***��е���豸quadcell״̬***/
typedef struct
{
    WR4A_QUADCELL_RAW_DATA_STRUCT      segment;			//quadcell ԭʼֵ
	WR4A_QUADCELL_CONVERT_DATA_STRUCT  segment_convert;	// ת��ֵ
    xy_vect       displacement;							//
    SMEE_BOOL     out_of_range;							//�Ƿ񳬳���Χ
	SMEE_BOOL     docked_ok;
	SMEE_BOOL     z_sensor;
	SMEE_BOOL     filler;
} WR4A_QUAD_CELL_STRUCT;


/***��е��״���ṹ��***/
typedef struct
{
    WR4A_PE_STATE_ENUM state;   			//��е���豸״̬��
    WR4A_STATION_ENUM station;  			//��е�ֹ�λ
	WR4A_QUAD_CELL_STRUCT dock_state;  		//DOCK״̬
	WR4A_AXIS_STRUCT  axis[WR4A_AXIS_MAX];	//������λ��
	WR4A_AREA_STRUCT  area;       			//��е����������
    SMEE_BOOL wafer_present;
    SMEE_INT32 filler;

} WR4A_STATUS_STRUCT;

/***��е�ֶ��Ľṹ��***/
typedef struct
{
   WR4A_PE_STATE_ENUM state;   //��е���豸״̬��
   WR4A_STATION_ENUM station;  //��е�ֹ�λ
   SMEE_BOOL wafer_present;
   SMEE_INT32 filler;

} WR4A_SUBSCRIBE_STATUS_STRUCT;


#endif

