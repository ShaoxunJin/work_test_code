/**************************************************************************
 * Copyright (C) 2016, �Ϻ�΢����װ�����޹�˾
 * All rights reserved.
 * ��Ʒ�� : GCS
 * ���������WR
 * �ļ����ƣ�WRMC_tc.h
 * ��Ҫ��������е�ֻ�������ͷ�ļ����ݶ���
 * ��ʷ��¼��
 * �汾       ��  ��      ��  ��          ��    ��
 *1.0                     sunww
 *************************************************************************/

#ifndef WRMC_WORKFLOW_TC_H
#define WRMC_WORKFLOW_TC_H
//��е������ɨ��ṹ��
typedef struct
{
	char ip_address[20];
	unsigned int  port_id;
}WRMC_SOCKER_CONFIG_STRUCT;
//����ͨѶɨ��ṹ��
typedef enum
{
	WRMC_SERIAL_DEVS_MIN = 0,
	WRMC_SERIAL_DEVS_PPC_COM,
	WRMC_SERIAL_DEVS_TTY_4_COM,
	WRMC_SERIAL_DEVS_TTY_16_COM,
	WRMC_SERIAL_DEVS_MAX,
} WRMC_SERIAL_DEVS_ENUM;

typedef struct
{
	char port_name[64];
	unsigned int baudrate;
	unsigned int stop_bit;
	unsigned int data_bit;
	unsigned int even_odd_bit;
}WRMC_PORT_PARAMETER_STRUCT;

typedef struct
{
	unsigned int filler;
	WRMC_SERIAL_DEVS_ENUM serial_devices;//PPCΪPPC�Դ�����,TTY_4Ϊ�Ŀڶമ�ڿ�,TTY_16Ϊ16�ڶമ�ڿ�
	WRMC_PORT_PARAMETER_STRUCT port; //PPC��Χ��0-3,TTY_4��Χ��1-4,TTY_16��Χ��0-15
}WRMC_SERIAL_CONFIG_STRUCT;

//ͨѶ��ʽ�Ǵ��ڻ�������
typedef enum
{
	WRMC_COM_DEVICE_MIN = 0,
	WRMC_COM_DEVICE_SERIAL,
	WRMC_COM_DEVICE_NET,
	WRMC_COM_DEVICE_MAX
}WRMC_COM_DEVICE_ENUM;

typedef enum
{
	WRMC_INFO_MODE_MIN = -2,
	WRMC_INFO_MODE_N = -1,
	WRMC_INFO_MODE_0 = 0,
	WRMC_INFO_MODE_1 = 1,
	WRMC_INFO_MODE_2 = 2,
	WRMC_INFO_MODE_3 = 3,
	WRMC_INFO_MODE_MAX
}WRMC_INFO_MODE_ENUM;

typedef struct
{
	unsigned int  filler;
	WRMC_COM_DEVICE_ENUM config;
	WRMC_SOCKER_CONFIG_STRUCT serial_config;
	WRMC_SERIAL_CONFIG_STRUCT socket_config;
}WRMC_COMMUNICATION_CONFIG_STRUCT;

typedef enum
{
	WRMC_SPEED_LEVEL_MIN = 0,
	WRMC_SPEED_LEVEL_HOME,
	WRMC_SPEED_LEVEL_1,
	WRMC_SPEED_LEVEL_2,
	WRMC_SPEED_LEVEL_3,
	WRMC_SPEED_LEVEL_4,
	WRMC_SPEED_LEVEL_5,
	WRMC_SPEED_LEVEL_6,
	WRMC_SPEED_LEVEL_7,
	WRMC_SPEED_LEVEL_8,
	WRMC_SPEED_LEVEL_9,
	WRMC_SPEED_LEVEL_MAX
}WRMC_SPEED_LEVEL_ENUM;

typedef struct
{
	unsigned int use_swap_pickup_mode;//ʹ�ø�ģʽ
	unsigned int swap_z_move_first;//z���˶���SWAP
	unsigned int  swap_z_distance;//��ֻ�ֱ���ͬһ����λ�Ĵ���߶Ȳ�
	unsigned int open_cda_after_release_vac;//�ͷ�����ʱ����ѹ������ѹ
	unsigned int  material_release_vac_delay;// vac delay
	unsigned int  material_release_cda_delay;// cda delay
}WRMC_SWAP_PICKUP_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_swap_putget_mode;//ʹ�ø�ģʽ
	unsigned int swap_putget_vac_mode_priority;
	unsigned int swap_z_distance;//��ֻ�ֱ���ͬһ����λ�Ĵ���߶Ȳ�
	unsigned int open_cda_after_release_vac;//�ͷ�����ʱ����ѹ������ѹ
	unsigned int material_release_vac_delay;// vac delay
	unsigned int material_release_cda_delay;// cda delay
}WRMC_SWAP_PUTGET_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_put_mode;//ʹ�ø�ģʽ
	unsigned int do_put_retry;//put����Ĭ��1��
	unsigned int material_release_vac_delay;//put vac delay
	unsigned int material_release_cda_delay;//put cda delay
}WRMC_PUT_PARAMTER_STRUCT;

typedef enum
{
	WRMC_GET_MOTION_TYPE_MIN = 0,
	WRMC_GET_MOTION_TYPE_NO_SEARCH,           //0
	WRMC_GET_MOTION_TYPE_CONTINUOUS_SEARCH,   //1
	WRMC_GET_MOTION_TYPE_RESERVED2,
	WRMC_GET_MOTION_TYPE_FOUND_NO_WAFER_STOP, //3
	WRMC_GET_MOTION_TYPE_RESERVED4,
	WRMC_GET_MOTION_TYPE_MAX
}WRMC_GET_MOTION_TYPE_ENUM;//

typedef struct
{
	unsigned int use_get_mode;//ʹ�ø�ģʽ
	unsigned int do_get_retry;//get����Ĭ��1��
	unsigned int material_release_vac_delay;//get vac delay
	unsigned int material_release_cda_delay;//get cda delay
	WRMC_GET_MOTION_TYPE_ENUM get_motion_type; //ָ��get�˶����ͣ���е������֧�ָ�ģʽ
}WRMC_GET_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_pickup_mode;//ʹ�ø�ģʽ
	unsigned int filler;
}WRMC_PICKUP_PARAMTER_STRUCT;

typedef struct
{ 
	WRMC_PICKUP_PARAMTER_STRUCT pickup;//pickup����
	WRMC_GET_PARAMTER_STRUCT get;//get����
	WRMC_PUT_PARAMTER_STRUCT put;//put����
	WRMC_SWAP_PICKUP_PARAMTER_STRUCT swap_pickup;//swap_pickup����
	WRMC_SWAP_PUTGET_PARAMTER_STRUCT swap_putget;//swap_putget����
}WRMC_EXCHANGE_PARAMETER_STRUCT;


typedef struct
{
	char lower_arm_name;//�±۹�λ����
	char upper_arm_name;//�ϱ۹�λ����
	char filler[6];
}WRMC_ARM_STATION_STRUCT;

typedef struct
{
	WRMC_ARM_STATION_STRUCT size_2;
	WRMC_ARM_STATION_STRUCT size_3;
	WRMC_ARM_STATION_STRUCT size_4;
	WRMC_ARM_STATION_STRUCT size_5;
	WRMC_ARM_STATION_STRUCT size_6;
	WRMC_ARM_STATION_STRUCT size_8;
	WRMC_ARM_STATION_STRUCT size_12;
	WRMC_ARM_STATION_STRUCT size_9;
	WRMC_ARM_STATION_STRUCT size_13;
	WRMC_ARM_STATION_STRUCT size_18;
}WRMC_SIZE_STATION_STRUCT;
typedef struct
{
	unsigned int is_valid;//��ǰ�Ĺ�λ�Ƿ���Ч
	unsigned int max_slot;
	unsigned int do_mateial_verify_before_exchange;
	unsigned int do_mateial_verify_after_exchange;
	WRMC_SIZE_STATION_STRUCT station_name;
	WRMC_SPEED_LEVEL_ENUM speed;//ָ��put �ٶ�
	WRMC_EXCHANGE_PARAMETER_STRUCT parameters;//����
}WRMC_STATION_PARAMTER_STRUCT;

typedef struct
{
	WRMC_STATION_PARAMTER_STRUCT wu1;
	WRMC_STATION_PARAMTER_STRUCT wu2;
	WRMC_STATION_PARAMTER_STRUCT wc1;
	WRMC_STATION_PARAMTER_STRUCT wc2;
	WRMC_STATION_PARAMTER_STRUCT wc3;
	WRMC_STATION_PARAMTER_STRUCT wg;
	WRMC_STATION_PARAMTER_STRUCT wt;
	WRMC_STATION_PARAMTER_STRUCT ic;
	WRMC_STATION_PARAMTER_STRUCT oc;
}WRMC_STATION_STRUCT;

typedef struct
{
	WRMC_SPEED_LEVEL_ENUM size_2_speed;
	WRMC_SPEED_LEVEL_ENUM size_3_speed;
	WRMC_SPEED_LEVEL_ENUM size_4_speed;
	WRMC_SPEED_LEVEL_ENUM size_5_speed;
	WRMC_SPEED_LEVEL_ENUM size_6_speed;
	WRMC_SPEED_LEVEL_ENUM size_8_speed;
	WRMC_SPEED_LEVEL_ENUM size_9_speed;
	WRMC_SPEED_LEVEL_ENUM size_12_speed;
	WRMC_SPEED_LEVEL_ENUM size_13_speed;
	WRMC_SPEED_LEVEL_ENUM size_18_speed;
}WRMC_SIZE_SPEED_FACTOR_STRUCT;

typedef struct
{
	int on_line;//������
	int use_one_arm;
	WRMC_INFO_MODE_ENUM info_mode; //��е��ͨ��ģʽ
	WRMC_STATION_STRUCT station;  //<default>1<>
	WRMC_COMMUNICATION_CONFIG_STRUCT serial_config;//ͨ�Ų���
	WRMC_SIZE_SPEED_FACTOR_STRUCT size_speed;//��ͬ�ߴ��ٶ�
}WRMC_ROBOT_STRUCT;

typedef struct
{
	WRMC_ROBOT_STRUCT  first_robot;
	WRMC_ROBOT_STRUCT  second_robot;
}WRMC_FILE_STRUCT;

#endif