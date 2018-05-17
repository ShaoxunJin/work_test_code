/**************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* �� Ʒ �� : ADAE
* ������� : EH
* ģ������ : EH4A
* �ļ����� : EH4A_tc.h
* ��Ҫ���� : EH����������ݶ���
* ��ʷ��¼ :
* �汾   ����        ����        ����
* V1.0   2009-4-9    buxj        ����
* V1.1   2009-7-20   buxj        ���ö�ٶ��壺EH4A_WARNING_CLEAR_ENUM
* V1.2	 2011-1-6	 buxj		 1��ɾ��EH4A_EXCEPTION_SEVERITY_LEVER_ENUM��
								 EH4A_SEVERITY_LEVER_EXCEPTION����
								 2��Ӵ�����EH4A_NO_ROOT_CAUSE_ERR
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


/*�����붨��*/
#define EH4A_SYSTEM_ERR                     0x45480000            //ϵͳ����
#define EH4A_TIMEOUT_ERR                    0x45480001            //��ʱ����
#define EH4A_PARAMETER_ERR                  0x45480002            //��������
#define EH4A_ILLEGAL_CALL_ERR               0x45480003            //�Ƿ�����
#define EH4A_INVALID_ERROR_CODE             0x45480004            //�������쳣�������Ϲ淶Ҫ�������
#define EH4A_SIGSEGV_ERROR                  0x45480005			  //���ֶԵ�����ļ���
#define EH4A_NO_ROOT_CAUSE_ERR				0x45480006			  //û�з��ֻ��ߴ������жϻᵼ�¸ô���

#define EHIT_ALARM_ITEM						0x4548FF01          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH alarm. "/> 
#define EHIT_SYSTEM_ERROR_ITEM 				0x4548FF02          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH system error. "/> 
#define EHIT_PROCESS_ERROR_ITEM			    0x4548FF03          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH process error. "/> 
#define EHIT_USER_ERROR_ITEM				0x4548FF04          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH user error. "/> 
#define EHIT_ENVIRONMENT_ERROR_ITEM 		0x4548FF05          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH environment error."/> 
#define EHIT_MATERIAL_ERROR_ITEM			0x4548FF06          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH material error. "/> 
#define EHIT_LAMP_WARNING_ITEM				0x4548FF07          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH user material enviroment warning. "/> 
#define EHIT_NORMAL_WARNING_ITEM		    0x4548FF08          // <item attribute="IT4A_ATTR_VALUE,IT4A_ATTR_STATUS"  value_type="IT4A_REP_BYTE"description="The item is EH exception warning. "/> 
#define EHIT_EXCEPTION_ITEM                 0x4548FF09          // <item attribute="IT4A_ATTR_VALUE"  value_type="IT4A_REP_BYTE"description="The item is EH send_to_host TRUE. "/>   

/*ö�٣�������־ģʽ*/
typedef enum
{
    EH4A_LOG_MODE_MIN = -1,
    EH4A_LOG_MODE_NORMAL,   /*��ͨģʽ*/
    EH4A_LOG_MODE_LOCAL,    /*����ģʽ*/
    EH4A_LOG_MODE_MAX
} EH4A_LOG_MODE_ENUM;

/* ��¼��ǰ�ź���ת�¼� */
typedef jmp_buf EH4A_CURR_EVENT;
/* �쳣�ȼ� */
typedef enum
{
    EH4A_SEVERITY_LEVER_MIN = -1,
	EH4A_SEVERITY_LEVER_EVENT,
    EH4A_SEVERITY_LEVER_WARNING ,
    EH4A_SEVERITY_LEVER_ERROR,
	EH4A_SEVERITY_LEVER_ALARM,
    EH4A_SEVERITY_LEVER_MAX
}EH4A_EXCEPTION_SEVERITY_LEVER_ENUM;

/* �쳣��� */
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

/* �쳣�ָ��� */
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

/*���洦��ѡ��*/
typedef enum
{
	EH4A_WARNING_CLEAR_MIN = -1,
	EH4A_AUTO_CLEAR = 0,
	EH4A_USER_CLEAR,
	EH4A_WARNING_CLEAR_MAX
}EH4A_WARNING_CLEAR_ENUM;


#endif
