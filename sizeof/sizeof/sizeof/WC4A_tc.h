/**************************************************************************
 * Copyright (C) 2010, �Ϻ�΢����װ�����޹�˾
 * All rights reserved.
 * ��Ʒ�ţ�  SSA800/10
 * ���������WC
 * �ļ����ƣ�WC4A_tc.h
 * ��Ҫ������
 * ��ʷ��¼��
 * �汾       ��  ��      ��  ��          ��    ��
 * V1.0    2014-5-20     sunlf             �����ļ�
 *************************************************************************/
#ifndef WC4A_TC_H
#define WC4A_TC_H
#include "smee.h"
#include "WCMC_tc.h"
//#include "WRH_BASE.h"


//��������붨��
#define WC4A_BASE_ERROR             (0x57430000) 			//"WC" ģ��������ַ

/*<ErrBegin>*/
#define WC4A_SYSTEM_ERROR           (WC4A_BASE_ERROR + 0x01)//�������󣬳���ʱͨ����ζ��Ҫ���³�ʼ��
#define WC4A_PARAMETER_ERROR        (WC4A_BASE_ERROR + 0x02)//�������󣬱�������Խ��
#define WC4A_ILLEGAL_CALL_ERROR     (WC4A_BASE_ERROR + 0x03)//״̬���󣬱�����ǰ�ӿڲ����ڵ�ǰ״̬�µ���
#define WC4A_INVALID_STATE_ERROR    (WC4A_BASE_ERROR + 0x04)//��ʱ���󣬱����ӿڵ��ó�ʱ
/*<ErrEnd>*/

//����ۺ���
#define WC4A_MAX_SLOT_NBR 25

//����carrier id �ַ�������
#define WC4A_MAX_CARRIER_ID_SIZE 30

//����cassette id ����


// Ƭ���豸״̬
typedef enum
{
    WC4A_PE_ST_MIN = 0,
    WC4A_PE_ST_UNKNOWN,
    WC4A_PE_ST_TERMINATED,
    WC4A_PE_ST_INITIALIZED,
    WC4A_PE_ST_BUSY,
    WC4A_PE_ST_MAX
} WC4A_PE_STATE_ENUM;


// Carrier״̬
typedef enum
{
    WC4A_CARRIER_STATE_MIN = 0,
    WC4A_CARRIER_NOT_PRESENT,
    WC4A_CARRIER_PRESENT,           // Ƭ�д���
    WC4A_CARRIER_LOCKED,            // Ƭ�д��ڲ��ұ���������δɨ��
    WC4A_CARRIER_MAPPED,            // Ƭ�д�����������ɨ��
    WC4A_CARRIER_BUSY,              // ����ִ��װ�ػ�ж�ض���
    WC4A_CARRIER_STATE_MAX
} WC4A_CARRIER_STATE_ENUM;

// Ƭ�ⴹ��λ����
typedef enum
{
    WC4A_Z_STATION_MIN = 0,
    WC4A_Z_DOCK,         // dock��ˮƽ�˶��߶�
    WC4A_Z_SWING_IN,     //��ת��ת��ĸ߶�
    WC4A_Z_END_SCAN,     // ����ɨ��ĸ߶�
    WC4A_Z_START_SCAN,   // ��ʼɨ��ĸ߶�
    WC4A_Z_LATCH,        // ����Ƭ���ŵĴ���߶�
    WC4A_Z_EXCHANGE,       // �˻�����߶�
    WC4A_Z_TOP_SLOT,
    WC4A_Z_UNKNOWN,
    WC4A_Z_STATION_MAX
} WC4A_Z_STATION_ENUM;

// Ƭ���ᶨ��
//typedef enum
//{
//    WC4A_AX_MIN = 0,
//    WC4A_Z,            // ������
//    WC4A_SWING,    //Ƭ����ת��
//    WC4A_DOCK,         // DOCK��?
//    WC4A_LATCH_H,        // LATCH�ᣬ����Ƭ����
//    WC4A_LATCH_R,     // LATCH��ת��
//    WC4A_MAPPER,       // Ƭ��mapper��
//    WC4A_AX_MAX
//} WC4A_AX_ENUM;

// Ƭ��ָʾ�ƶ���
typedef enum
{
    WC4A_LED_MIN = 0,
    WC4A_LED_LOAD,     //load��ťָʾ����ɫ
    WC4A_LED_UNLOAD,   //unload��ťָʾ����ɫ
    WC4A_LED_CARRIER_PRESENT,   //Ƭ�д���
    WC4A_LED_FOUP_ERROR, //Ƭ����������������⣬ͻƬ����  ��ɫ
    WC4A_LED_LOAD_UNLOAD_READY, //��ɫ
    WC4A_LED_MAX
} WC4A_INDICATOR_ENUM;

//����id ���� carrier id cassette id
typedef enum
{
    WC4A_ID_TYPE_MIN=0,
	WC4A_ID_TYPE_CARRIER_ID,  //Ƭ��id
	WC4A_ID_TYPE_CASSETTE_ID, //OCA cassette id
	WC4A_ID_TYPE_MAX

} WC4A_ID_TYPE_ENUM;


// ��Ƭɨ����ö��
typedef enum
{
    WC4A_SLOT_INFO_MIN=0,
    WC4A_NO_WAFER,               // �����޹�Ƭ
    WC4A_NORMALLY_INSERT,        // ��ȷ����
    WC4A_CROSS_SLOT,             // ���
    WC4A_DOUBLE_SLOT,            // ��Ƭ
    WC4A_SLOT_INFO_MAX
} WC4A_SLOT_INFO_ENUM;


// Ƭ��״̬��Ϣ
typedef struct
{
    WC4A_PE_STATE_ENUM state;        //pe state
    WC4A_CARRIER_STATE_ENUM carrier_state; //carrier state
    WC4A_Z_STATION_ENUM  z_station;
    WC4A_SLOT_INFO_ENUM slot_info[WC4A_MAX_SLOT_NBR];
	SMEE_BOOL filler;
} WC4A_STATUS_STRUCT;
#endif

