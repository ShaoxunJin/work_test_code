#include "head_file.h"

//机械手网口扫描结构体
typedef struct
{
	char ip_address[20];
	SMEE_INT32 port_id;
}WM4A_RO_SOCKER_CONFIG_STRUCT;

//串口通讯扫描结构体
typedef enum
{
	WM4A_RO_SERIAL_DEVS_MIN = 0,
	WM4A_RO_SERIAL_DEVS_PPC_COM,
	WM4A_RO_SERIAL_DEVS_TTY_4_COM,
	WM4A_RO_SERIAL_DEVS_TTY_16_COM,
	WM4A_RO_SERIAL_DEVS_MAX,
}WM4A_RO_SERIAL_DEVS_ENUM;

typedef struct
{
	char port_name[64];
	int baudrate;
	int stop_bit;
	int data_bit;
	int even_odd_bit;
}WM4A_RO_PORT_PARAMETER_STRUCT;

typedef struct
{
	int filler;
	WM4A_RO_SERIAL_DEVS_ENUM serial_devices;		//<default>3<unit><range><description>
	WM4A_RO_PORT_PARAMETER_STRUCT port; 			//PPC范围是0-3,TTY_4范围是1-4,TTY_16范围是0-15
}WM4A_RO_SERIAL_CONFIG_STRUCT;

//通讯方式是串口还是网口
typedef enum
{
	WM4A_RO_COM_DEVICE_MIN = 0,
	WM4A_RO_COM_DEVICE_SERIAL,
	WM4A_RO_COM_DEVICE_NET,
	WM4A_RO_COM_DEVICE_MAX
}WM4A_RO_COM_DEVICE_ENUM;

typedef struct
{
	SMEE_INT32 filler;
	WM4A_RO_COM_DEVICE_ENUM config;				//<default>1<unit><range><description>
	WM4A_RO_SOCKER_CONFIG_STRUCT socket_config;	//<default>0<unit><range><description>
	WM4A_RO_SERIAL_CONFIG_STRUCT serial_config;	//<default>0<unit><range><description>
}WM4A_RO_COMMUNICATION_CONFIG_STRUCT;
