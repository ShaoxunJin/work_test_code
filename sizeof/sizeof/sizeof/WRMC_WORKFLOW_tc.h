/**************************************************************************
 * Copyright (C) 2016, 上海微电子装备有限公司
 * All rights reserved.
 * 产品号 : GCS
 * 所属组件：WR
 * 文件名称：WRMC_tc.h
 * 概要描述：机械手机器常数头文件数据定义
 * 历史记录：
 * 版本       日  期      作  者          内    容
 *1.0                     sunww
 *************************************************************************/

#ifndef WRMC_WORKFLOW_TC_H
#define WRMC_WORKFLOW_TC_H
//机械手网口扫描结构体
typedef struct
{
	char ip_address[20];
	unsigned int  port_id;
}WRMC_SOCKER_CONFIG_STRUCT;
//串口通讯扫描结构体
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
	WRMC_SERIAL_DEVS_ENUM serial_devices;//PPC为PPC自带串口,TTY_4为四口多串口卡,TTY_16为16口多串口卡
	WRMC_PORT_PARAMETER_STRUCT port; //PPC范围是0-3,TTY_4范围是1-4,TTY_16范围是0-15
}WRMC_SERIAL_CONFIG_STRUCT;

//通讯方式是串口还是网口
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
	unsigned int use_swap_pickup_mode;//使用该模式
	unsigned int swap_z_move_first;//z先运动再SWAP
	unsigned int  swap_z_distance;//两只手臂在同一个工位的垂向高度差
	unsigned int open_cda_after_release_vac;//释放物料时开正压，关正压
	unsigned int  material_release_vac_delay;// vac delay
	unsigned int  material_release_cda_delay;// cda delay
}WRMC_SWAP_PICKUP_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_swap_putget_mode;//使用该模式
	unsigned int swap_putget_vac_mode_priority;
	unsigned int swap_z_distance;//两只手臂在同一个工位的垂向高度差
	unsigned int open_cda_after_release_vac;//释放物料时开正压，关正压
	unsigned int material_release_vac_delay;// vac delay
	unsigned int material_release_cda_delay;// cda delay
}WRMC_SWAP_PUTGET_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_put_mode;//使用该模式
	unsigned int do_put_retry;//put重试默认1次
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
	unsigned int use_get_mode;//使用该模式
	unsigned int do_get_retry;//get重试默认1次
	unsigned int material_release_vac_delay;//get vac delay
	unsigned int material_release_cda_delay;//get cda delay
	WRMC_GET_MOTION_TYPE_ENUM get_motion_type; //指定get运动类型，机械手自身支持该模式
}WRMC_GET_PARAMTER_STRUCT;

typedef struct
{
	unsigned int use_pickup_mode;//使用该模式
	unsigned int filler;
}WRMC_PICKUP_PARAMTER_STRUCT;

typedef struct
{ 
	WRMC_PICKUP_PARAMTER_STRUCT pickup;//pickup参数
	WRMC_GET_PARAMTER_STRUCT get;//get参数
	WRMC_PUT_PARAMTER_STRUCT put;//put参数
	WRMC_SWAP_PICKUP_PARAMTER_STRUCT swap_pickup;//swap_pickup参数
	WRMC_SWAP_PUTGET_PARAMTER_STRUCT swap_putget;//swap_putget参数
}WRMC_EXCHANGE_PARAMETER_STRUCT;


typedef struct
{
	char lower_arm_name;//下臂工位名称
	char upper_arm_name;//上臂工位名称
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
	unsigned int is_valid;//当前改工位是否有效
	unsigned int max_slot;
	unsigned int do_mateial_verify_before_exchange;
	unsigned int do_mateial_verify_after_exchange;
	WRMC_SIZE_STATION_STRUCT station_name;
	WRMC_SPEED_LEVEL_ENUM speed;//指定put 速度
	WRMC_EXCHANGE_PARAMETER_STRUCT parameters;//参数
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
	int on_line;//调试用
	int use_one_arm;
	WRMC_INFO_MODE_ENUM info_mode; //机械手通信模式
	WRMC_STATION_STRUCT station;  //<default>1<>
	WRMC_COMMUNICATION_CONFIG_STRUCT serial_config;//通信参数
	WRMC_SIZE_SPEED_FACTOR_STRUCT size_speed;//不同尺寸速度
}WRMC_ROBOT_STRUCT;

typedef struct
{
	WRMC_ROBOT_STRUCT  first_robot;
	WRMC_ROBOT_STRUCT  second_robot;
}WRMC_FILE_STRUCT;

#endif