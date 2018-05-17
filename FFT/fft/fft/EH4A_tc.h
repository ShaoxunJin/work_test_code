/**************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产 品 号 : ADAE
* 所属组件 : EH
* 模块名称 : EH4A
* 文件名称 : EH4A_tc.h
* 概要描述 : EH组件对外数据定义
* 历史记录 :
* 版本   日期        作者        内容
* V1.0   2009-4-9    buxj        创建
* V1.1   2009-7-20   buxj        添加枚举定义：EH4A_WARNING_CLEAR_ENUM
* V1.2	 2011-1-6	 buxj		 1、删除EH4A_EXCEPTION_SEVERITY_LEVER_ENUM中
								 EH4A_SEVERITY_LEVER_EXCEPTION定义
								 2添加错误码EH4A_NO_ROOT_CAUSE_ERR
***************************************************************/
#ifndef EH4A_TC_H
#define EH4A_TC_H

#include "EH4A_config.h"
#include "smee.h"
#include "ADAE.h"
#if TARGET_OS == VXWORKS_OS
#elif TARGET_OS == SUN_OS
#include <signal.h>
#endif
#include <setjmp.h>


/*错误码定义*/
#define EH4A_SYSTEM_ERR                     0x45480000            //系统错误
#define EH4A_TIMEOUT_ERR                    0x45480001            //超时错误
#define EH4A_PARAMETER_ERR                  0x45480002            //参数错误
#define EH4A_ILLEGAL_CALL_ERR               0x45480003            //非法调用
#define EH4A_INVALID_ERROR_CODE             0x45480004            //错误码异常，不符合规范要求错误码
#define EH4A_SIGSEGV_ERROR                  0x45480005			  //保持对第三版的兼容
#define EH4A_NO_ROOT_CAUSE_ERR				0x45480006			  //没有发现或者错误连中断会导致该错误

#define EHIT_ALARM_ITEM						0x4548FF01          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH alarm. "/> 
#define EHIT_SYSTEM_ERROR_ITEM 				0x4548FF02          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH system error. "/> 
#define EHIT_PROCESS_ERROR_ITEM			    0x4548FF03          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH process error. "/> 
#define EHIT_USER_ERROR_ITEM				0x4548FF04          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH user error. "/> 
#define EHIT_ENVIRONMENT_ERROR_ITEM 		0x4548FF05          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH environment error."/> 
#define EHIT_MATERIAL_ERROR_ITEM			0x4548FF06          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH material error. "/> 
#define EHIT_LAMP_WARNING_ITEM				0x4548FF07          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH user material enviroment warning. "/> 
#define EHIT_NORMAL_WARNING_ITEM		    0x4548FF08          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH exception warning. "/> 
#define EHIT_EXCEPTION_ITEM                 0x4548FF09          // <item attribute="IT4A_ATTR_VALUE"  value_type="IT4A_REP_BYTE"description="The item is EH send_to_host TRUE. "/>   

/*枚举：错误日志模式*/
typedef enum
{
    EH4A_LOG_MODE_MIN = -1,
    EH4A_LOG_MODE_NORMAL,   /*普通模式*/
    EH4A_LOG_MODE_LOCAL,    /*本地模式*/
    EH4A_LOG_MODE_MAX
} EH4A_LOG_MODE_ENUM;

/* 记录当前信号跳转事件 */
typedef jmp_buf EH4A_CURR_EVENT;
/* 异常等级 */
typedef enum
{
    EH4A_SEVERITY_LEVER_MIN = -1,
	EH4A_SEVERITY_LEVER_EVENT,
    EH4A_SEVERITY_LEVER_WARNING ,
    EH4A_SEVERITY_LEVER_ERROR,
	EH4A_SEVERITY_LEVER_ALARM,
    EH4A_SEVERITY_LEVER_MAX
}EH4A_EXCEPTION_SEVERITY_LEVER_ENUM;

/* 异常类别 */
typedef enum
{
    EH4A_EXCEPTION_CLASS_MIN = -1,
    EH4A_EXCEPTION_CLASS_SYSTEM,
    EH4A_EXCEPTION_CLASS_USER,
    EH4A_EXCEPTION_CLASS_PROCESS,
    EH4A_EXCEPTION_CLASS_MATERIAL,
    EH4A_EXCEPTION_CLASS_ENVIRONMENT,
    EH4A_EXCEPTION_CLASS_MAX
}EH4A_EXCEPTION_CLASS_ENUM;

/* 异常恢复类 */
typedef enum
{
    EH4A_RECV_MIN = -1,
    EH4A_RECV_DEFAULT,
    EH4A_RECV_RETRY,
    EH4A_RECV_CHANGEPARAMS,
    EH4A_RECV_SKIP,
    EH4A_RECV_INIT,
    EH4A_RECV_RESTART,
    EH4A_RECV_REBOOT,
    EH4A_RECV_SERVICE,
    EH4A_RECV_MAX
}EH4A_EXCEPTION_RECOVERY_CLASS_ENUM;

/*警告处理选项*/
typedef enum
{
	EH4A_WARNING_CLEAR_MIN = -1,
	EH4A_AUTO_CLEAR = 0,
	EH4A_USER_CLEAR,
	EH4A_WARNING_CLEAR_MAX
}EH4A_WARNING_CLEAR_ENUM;


#endif
