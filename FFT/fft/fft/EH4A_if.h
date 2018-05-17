/**************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* �� Ʒ �� : ADAE
* ������� : EH
* ģ������ : EH4A
* �ļ����� : EH4A_if.h
* ��Ҫ���� : EH�������ӿ�����
* ��ʷ��¼ :
* �汾   ����        ����        ����
* V1.0   2009-4-9    buxj        ����
* V1.1   2009-5-31   buxj        ����Ͻӿ�����
* V1.2   2009-6-2    buxj        �޸�report_exception�ӿڵ�option����
                                 ΪEH4A_EXCEPTION_RECOVERY_OPTION_ENUM
* V1.3   2009-7-16   buxj        1���޸�EH4A_get_active_componentwarnings�Ľӿ����� 
                                 2���޸�EH4A_deactive_componentwarning-->EH4A_destroy_componentwarnings
                                 3�����EH4A_deactive_exception�ӿ�
* V1.4   2009-7-22   buxj        ���ǰ�������ͺ�������
* V1.5	 2011-1-6	 buxj		 1�����EH4A_get_root_cause�ӿ�
***************************************************************/

#ifndef EH4A_IF_H
#define EH4A_IF_H

#include "EH4A_tc.h"
#include <stdarg.h> 
#include <time.h>

/*== Fucntion declaration ====================================================*/
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_error_to_string(int exception_code,char* buffer,int len)
* Parameters:
*    -input:
*       int exception_code                      -- ��ת�����쳣����
*       int len                                 -- �ַ�������
*    -in/out:
*    -output:
*       char* buffer                            -- ת������ַ���
* Returns:
*      OK
*   EH4A_PARAMETER_ERR                          -- �ӿڲ�������ȷ
*   EH4A_INVALID_ERROR_CODE                     -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       1�����쳣����ת��Ϊ��Ӧ�ַ�����
*       2��������ݿ��д��ڸ��쳣����ֱ�ӻ�ȡ��Ӧ���ַ�����
*       3��������ݿ��в����ڸ��쳣�룬��ֱ���ڱ���ת����
* PreCondition:
*       �ͻ��˺ͷ����CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       ���쳣��ת��Ϊ��Ӧ���ַ�����
*/
extern "C" int EH4A_error_to_string(IN int error_code,OUT char* buffer,IN int len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_string_to_error(const char* buffer,int* exception_code )
* Parameters:
*    -input:
*       const char* buffer                       -- ��ת���ַ���
*    -in/out:
*    -output: 
*       int* exception_code                      -- ת�����쳣����
* Returns:
*       OK
*       EH4A_PARAMETER_ERR                       -- �ӿڲ�������ȷ
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       ���쳣�ַ���ת��Ϊ��Ӧ�쳣����
* PreCondition:
*       �ͻ��˺ͷ����CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       ���ַ���ת��Ϊ��Ӧ���쳣��
*/
extern "C" int EH4A_string_to_error(IN const char* buffer,OUT int* error_code );
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_show_exception(int exception_code, int *link_error, const char *file, int line, const char *format,��)
* Parameters:
*    -input:
*       int exception_code                        -- �쳣����
*       int* link_error                           -- �쳣�����쳣����󳤶�Ϊ10
*       const char* file                          -- �쳣�������ļ������ļ�����󳤶�Ϊ80
*       int line                                  -- �쳣�������ڵ���
*       const char* format                        -- �쳣������ʽ�ַ���
*       ...                                       -- �ɱ���� ��󳤶�Ϊ256
*    -in/out:
*    -output:
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                            -- ���ݿ����ӳ��������ϵͳ�쳣
*       EH4A_PARAMETER_ERR                         -- �ӿڲ�������ȷ
*       EH4A_INVALID_ERROR_CODE                    -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       1����¼�쳣��Ϣ����־�ļ���
*       2���쳣��Ϣ����������ɣ��ֱ�Ϊ���ñ��еľ�̬��Ϣ�Լ�������Ա�ṩ�Ķ�̬��Ϣ��
* PreCondition:
*       CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       �쳣д����־�ļ���
*/
extern "C" int EH4A_show_exception(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN const char *format, ...);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_show_exception_v(int exception_code, int *link_error, const char *file, int line, const char *format,va_list args)
* Parameters:
*    -input:
*       int exception_code                          -- �쳣����
*       int* link_error                             -- �쳣�������쳣����󳤶�Ϊ10
*       const char* file                            -- �쳣�������ļ����ļ�����󳤶�Ϊ80
*       int line                                    -- �쳣�������ڵ���
*       const char* format                          -- �쳣������ʽ�ַ�������󳤶�Ϊ256
*       va_list args                                -- �ɱ����
*    -in/out:
*    -output:
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                             -- ���ݿ����ӳ��������ϵͳ�쳣
*       EH4A_PARAMETER_ERR                          -- �ӿڲ�������ȷ
*       EH4A_INVALID_ERROR_CODE                     -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       1����¼�쳣��Ϣ����־�ļ���
*       2���쳣��Ϣ����������ɣ��ֱ�Ϊ���ñ��еľ�̬��Ϣ�Լ�������Ա�ṩ�Ķ�̬��Ϣ��
* PreCondition:
*       CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       �쳣д����־�ļ���
*/
extern "C" int EH4A_show_exception_v(IN int exception_code,IN int *link_error, IN const char *file, IN int line,IN const char *format,va_list args);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_report_exception(int exception_code, int *link_error, const char *file, int line,EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response, const char *format,��)
* Parameters:
*    -input:
*       int exception_code                             -- �쳣����
*       int* link_error                                -- �쳣�����쳣���������ֵΪ10
*       const char* file                               -- �쳣�������ļ����ļ�����󳤶�Ϊ80
*       int line                                       -- �쳣�������ڵ���
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[]   -- �쳣�ָ�ѡ��
*       const char* format                             -- �쳣������ʽ�ַ�������󳤶�Ϊ256
*       ...                                            -- �ɱ����
*    -in/out:
*    -output:
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response  -- ����Աִ�е��쳣�ָ���ʩ
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                                -- ϵͳ�쳣
*       EH4A_PARAMETER_ERR                             -- �ӿڲ�������ȷ
*       EH4A_INVALID_ERROR_CODE                        -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       �����Ա�����쳣��ͨ���Ͳ���Ա�Ľ���ִ���쳣�ָ�������¼�쳣��Ϣ����־
* PreCondition:
*       �ͻ��ˡ�EHMA��EHLO�ͽ���CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       �쳣д����־�ļ������ҽ�����ʾ�ָ�ѡ��ȴ�����Աѡ��
*/
extern "C" int EH4A_report_exception(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],OUT EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response,IN const char *format,...);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_report_exception(int exception_code, int *link_error, const char *file, int line,EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response, const char *format,va_list args)
* Parameters:
*    -input:
*       int exception_code                            -- �쳣����
*       int* link_error                               -- �쳣������󳤶�Ϊ10
*       const char* file                              -- �쳣�������ļ����ļ�����󳤶�Ϊ80
*       int line                                      -- �쳣�������ڵ���
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[]  -- �쳣�ָ�ѡ��
*       const char* format                            -- �쳣������ʽ�ַ�������󳤶�Ϊ256
*       va_list args                                  -- �ɱ����
*    -in/out:
*    -output:
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response --����Աִ�е��쳣�ָ���ʩ
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                                -- ϵͳ�쳣
*       EH4A_PARAMETER_ERR                             -- �ӿڲ�������ȷ
*       EH4A_INVALID_ERROR_CODE                        -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       �����Ա�����쳣��ͨ���Ͳ���Ա�Ľ���ִ���쳣�ָ�������¼�쳣��Ϣ����־��
* PreCondition:
*       �ͻ��ˡ�EHMA��EHLO�ͽ���CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       �쳣д����־�ļ������ҽ�����ʾ�ָ�ѡ��ȴ�����Աѡ��
*/
extern "C" int EH4A_report_exception_v(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],OUT EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response,IN const char *format,IN va_list args);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_log_mode(EH4A_LOG_MODE_ENUM log_mode)
* Parameters:
*    -input:
*       EH4A_LOG_MODE_ENUM log_mode				  -- �쳣��¼ģʽ-���ػ�����
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_PARAMETER_ERR                       -- �ӿڲ�������ȷ
* Description:
*		�����쳣�ļ�¼ģʽ��
* PreCondition:
*		CN�Ѿ��ɹ���ʼ����
* PostCondition:
*		�쳣��¼ģʽ�ı䡣
*/
extern "C" int EH4A_set_log_mode(IN EH4A_LOG_MODE_ENUM log_mode);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_log_mode(EH4A_LOG_MODE_ENUM log_mode)
* Parameters:
*    -input:
*       EH4A_LOG_MODE_ENUM* log_mode             -- �쳣��¼ģʽ-���ػ�����
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_PARAMETER_ERR				  		 -- �ӿڲ�������ȷ
* Description:
*		��ȡ�쳣�ļ�¼ģʽ��
* PreCondition:
*		CN�Ѿ��ɹ���ʼ����
* PostCondition:
*		��ȡ��ǰ��¼ģʽ
*/
extern "C" int EH4A_get_log_mode(OUT EH4A_LOG_MODE_ENUM* log_mode);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_signal_install(void)
* Parameters:
*    -input:
*    -in/out:
*    -output:
* Returns:
*		OK 
*		EH4A_SYSTEM_ERR             
* Description:
*		��װ�źŴ�������
* PreCondition:
*		��
* PostCondition:
*	 �źŴ���������װ��
*/
extern "C" int EH4A_signal_install(void);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_signal_uninstall(void)
* Parameters:
*    -input:
*    -in/out:
*    -output:
* Returns:
*   OK 
* Description:
*		 ж���źŴ�������
* PreCondition:
*		�źű���װ��
* PostCondition:
*		�źŴ�������ж�أ������ٽ����źš�
*/
extern "C" int EH4A_signal_uninstall(void);
/**
* Include:
*    EH4A_if.h
* Function:
*    EH4A_CURR_EVENT *EH4A_current_event(void)
* Parameters:
*    -input:
*    -in/out:
*    -output:
* Returns:
*       EH4A_CURR_EVENT * �쳣������ָ�롣
* Description:
*		��ȡ�쳣������ָ�롣
* PreCondition:
*		��
* PostCondition:
*		�쳣��¼ģʽ�ı䡣
*/
extern "C" EH4A_CURR_EVENT *EH4A_current_event(void);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_nr_sigsegv(void)
* Parameters:
*    -input:
*    -in/out:
*    -output:
* Returns:
*       int ��ǰ�źŷ�������
* Description:
*		��ȡ�źŷ���������
* PreCondition:
*		��
* PostCondition:
*		��
*/
extern "C" int EH4A_nr_sigsegv(void);
/**
* Include:
*    EH4A_if.h
* Function:
*    void EH4A_set_nr_sigsegv(int nr_sigsegv)
* Parameters:
*    -input:
*       int nr_sigsegv  �źŷ�������
*    -in/out:
*    -output:
* Returns:
* Description:
*		�����źŷ���������
* PreCondition:
*		��
* PostCondition:
*		�źŷ����������޸ġ�
*/
extern "C" int EH4A_set_nr_sigsegv(IN int nr_sigsegv);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_alarm(int alarm_code,int alarm_id)
* Parameters:
*    -input:
*       int alarm_code                           -- ������  (��ʱ����)
*		int alarm_id                             -- ������id����Ϊ���ݿ�������Լ����
*    -in/out:
*    -output:
* Returns:
*	    OK
*       EH4A_SYSTEM_ERR                           -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                   -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		����ALARM ITEM������EHIT_ALARM_ITEM ��IT4A_ATTR_VALUEֵ�������ֽ�Ϊalarm_idֵ�������ֽڴ��Ϊ1�������;��浽���棬ͬʱ�����õ���Ϣд�����ݿ��С�
* PreCondition:
*		��
* PostCondition:
*		���ı��е�ALARM_SET״̬�����á�
*/
extern "C" int EH4A_set_alarm(IN int alarm_code,IN int alarm_id);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_clear_alarm(int alarm_id)
* Parameters:
*    -input:
*       int alarm_id                              -- ������id                        
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_SYSTEM_ERR                             -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                     -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		�ڶ������ݿ��У����ALARM��Ŀ�����б仯��IT����֪ͨ���������SECS manager),������澯����Ϣ��ͬʱ������ݿ��и��������¼
* PreCondition:
*		alarm_id��Ӧ��ALARM��Ŀ���Ѿ����ڡ�
* PostCondition:
*		���ı��е�ALARM_CLEAR״̬�����á�
*/
extern "C" int EH4A_clear_alarm(IN int alarm_id);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_alarm(int alarm_id,bool *is_set);
* Parameters:
*    -input:
*       int alarm_id                           -- ����id��
*    -in/out:
*    -output:
*       bool is_set                              -- ָ�������Ƿ�����
* Returns:
*		OK
*		EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		�ڶ������ݿ��У���ȡָ��ALARM��Ŀ��״̬��������ù���is_setΪTRUE�������ALARM������ˣ���is_setΪFALSE
* PreCondition:
*		��
* PostCondition:
*		��
*/
extern "C" int EH4A_get_alarm(IN int alarm_id,OUT SMEE_BOOL *is_set);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_recovery_class(int exception_code,int *error_code, EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* recovery_class);
* Parameters:
*    -input:
*       int exception_code                                    -- �쳣����
*    -in/out:
*    -output: 
*       int* error_code                                       -- �����쳣�ĸ�����
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM recovery_class    -- ������Ļָ���
* Returns:
*		OK
*		EH4A_SYSTEM_ERR										  -- ����ϵͳ���⵼�µ��쳣
*       EH4A_SYSTEM_ERR										          -- ��������
*       EH4A_INVALID_ERROR_CODE                               -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		 ��ȡָ���쳣�Ļָ��ࡣ
* PreCondition:
*		ָ���쳣����ڻָ�ѡ�
* PostCondition:
*		ָ���쳣�����ߵȼ��Ļظ�ѡ���ȡ��
*/
extern "C" int EH4A_get_recovery_class(IN int exception_code,OUT int *error_code,OUT EH4A_EXCEPTION_RECOVERY_CLASS_ENUM* recovery_class);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_active_componentwarnings(const char* com_name,int * warning_code)
* Parameters:
*    -input:
*       const char* com_name				     -- ���������󳤶�Ϊ3
*    -in/out:
*    -output:
*       int* warning_list						 -- �����б�
*       int* len								 -- �����б�ĳ��ȣ���󳤶�Ϊ32
* Returns:
*       OK
*       EH4A_PARAMETER_ERR
*       EH4A_SYSTEM_ERR                           -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*       ��ȡָ�������δ����ľ�����Ϣ����������������ڼ���Ƿ������Ҫ����������ٵľ���
* PreCondition:
*		��
* PostCondition:
*		�����˾����б�Ŀռ䣬�����������EH4A_destroy_componentwarnings
*/
extern "C" int EH4A_get_active_componentwarnings(IN const char* com_name,OUT int * warning_list,OUT int *len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_destroy_componentwarnings(int* warning_list)
* Parameters:
*    -input:
*       int* warning_list                         -- �����б��ַ
*    -in/out:
*    -output:
* Returns:
*		OK
* Description:
*		�ͷ�EH4A_get_active_componentwarnings��̬����ı��澯����Ϣ�Ŀռ䡣
* PreCondition:
*		�Ѿ�����EH4A_get_active_componentwarnings��
* PostCondition:
*	    �ͷ�EH4A_get_active_componentwarnings����Ŀռ䡣
*/
extern "C" int EH4A_destroy_componentwarnings(IN int* warning_list);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_deactive_exception(int deactive_code,int exception_code,char* format,...)
* Parameters: 
*    -input:
*       int deactive_code                       -- �쳣�������쳣�룬���ڼ�¼����־�ļ������ΪOK������ԡ�
*       int exception_code                      -- ����Ҫ��EH������ʾ���쳣����
*       char* format                            -- �����ĵ� 
*       ...                                     -- �ɱ��������󳤶�Ϊ256
*    -in/out:
*    -output:
* Returns:
*	    OK
*		EH4A_SYSTEM_ERR                         --- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                 -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		����Ѿ��ָ��ɹ����쳣���߲���Ҫ��ʾ�ľ�����Ϣ��
* PreCondition:
*		ָ���쳣�Ѿ�������ִ���˻ָ���ʩ
* PostCondition:
*	    ָ�����쳣��������
*/
extern "C" int EH4A_deactive_exception(IN int deactive_code,IN int exception_code,IN char* format,...);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_exception_tree(int  exception_code, time_t time ,char* exception_tree);
* Parameters:
*    -input:
*       int exception_code                       -- ָ�����쳣����
*       time_t time                              -- �쳣�����Ľ�ֹʱ��,Ĭ��Ϊ0������ǰʱ��
*    -in/out:
*    -output:
*       char* exception_tree                     -- �쳣�����쳣������󳤶�Ϊ409600
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
*       EH4A_PARAMETER_ERR                       -- ��������ȷ
* Description:
*		 ��ȡerror������쳣����
* PreCondition:
*		�������������С�
* PostCondition:
*		��ȡ���ַ���ʽ��ʾ���쳣����
*/
extern "C" int EH4A_get_exception_tree(IN int exception_code,IN time_t time, OUT char* exception_tree);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_root_cause(IN int exception_code,OUT int* root_cause);
* Parameters:
*    -input:
*       int exception_code                       -- ָ�����쳣����
*		int stop_at_event_code						 -- ������ֹ����(����������ʹ��)
*    -in/out:
*    -output:
*       int* root_cause							 -- ָ���쳣�ĸ�����
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
*       EH4A_PARAMETER_ERR                       -- ��������ȷ
*		EH4A_NO_ROOT_CAUSE_ERR					 -- �����ҵ���������ߴ������ж��޷�ȷ��������
* Description:
*		��ȡerror������쳣������
* PreCondition:
*		�������������С�
* PostCondition:
*		��ȡ������
*/
extern "C" int EH4A_get_root_cause(IN int exception_code,IN int stop_at_event_code,OUT int* root_cause);
/**
* Include:
*    EH4A_if.h
* Function:
*   int EH2PSM_init(EH4A_EXCEPTION_RECOVERY_CLASS_ENUM restart_model)
* Parameters:
*    -input:
*       EH4A_EXCEPTION_RECOVERY_CLASS_ENUM        restart_model   ��������
*    -in/out:
* Returns:
*       OK
*       EH4A_PARAMETER_ERR                       -- �ӿڲ�������ȷ
* Description:
*       ������ƽ̨ʱ��SM֪ͨEH���������Ϣ
* PreCondition:
*       �ͻ��˺ͷ����CN�Ѿ��ɹ���ʼ����
* PostCondition:
*      
*/
extern "C" int EH2PSM_init(IN EH4A_EXCEPTION_RECOVERY_CLASS_ENUM restart_model); 

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*������ƽ̨�ӿ�,����Ϊ�˱��ּ��ݣ��벻Ҫ����ʹ��*/
/**
* Include:
*    EH4A_if.h
* Function:
*    char *EH4A_create_text(const char *fmt, ...)
* Parameters:
*    -intput:
*       const char *fmt     ��ת���ĸ�ʽ
*         .....             ת��ǰ���ַ���
*    -int/out:
*    -output:
* Returns: ת������ַ���
* Description:
*		�����ʽ���ַ�����ʽ��
* PreCondition:
*		�������������С�
* PostCondition:
*		��ȡ���ַ���ʽ��ʾ���쳣����
*/
extern "C" char *EH4A_create_text(IN const char *fmt, ...);
/**
* Include:
*    EH4A_if.h
* Function:
*    void EH4A_signal_handler( int Sig_no, int code )
* Parameters:
*    -intput:
*      int Sig_no
*      int code
*    -int/out:
*    -output:
* Returns��
* Description:
*		�Բ��񵽵ĸ����ź�����Ӧ����
* PreCondition:
*		�ޡ�
* PostCondition:
*		�ޡ�
*/
extern "C" void EH4A_signal_handler(IN int Sig_no,IN int code );
/**
* Include:
*    EH4A_if.h
* Function:
*     int EH4A_exception_logoff(void)
* Parameters:
*    -intput:
*    -int/out:
*    -output:
* Returns��
* Description:
*		�ر��쳣ģʽ��
* PreCondition:
*		�ޡ�
* PostCondition:
*		�ޡ�
*/
extern "C" int EH4A_exception_logoff(void);
/**
* Include:
*    EH4A_if.h
* Function:
*     int EH4A_exception_logon(void)
* Parameters:
*    -intput:
*    -int/out:
*    -output:
* Returns��
* Description:
*		�����쳣ģʽ��
* PreCondition:
*		�ޡ�
* PostCondition:
*		�ޡ�
*/
extern "C" int EH4A_exception_logon(void);
/**
* Include:
*    EH4A_if.h
* Function:
*     intEH4A_log_error(int error_code, int *linkError,const char *text,const char *file, int line)
* Parameters:
*       int error_code:                          -- ����/�쳣��
*       int *linkError:                          -- ԭʼ�����룬��������󳤶�Ϊ10
*       const char *text:                        -- ����/�쳣���ݣ��䳤�����ֵΪ256
*       const char *file:                        -- ���������Դ�ļ����ļ����������ֵΪ80
*       int line:                                -- ���������������
*    -int/out:
*    -output:
* Returns��
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		���ýӿ�LogRecord������¼���󣬽���д���ڴ�ʹ��̼�¼�ļ��ļ��С�
*		�ú�����Ӧ���ж�/�쳣��������е��á����ô���Ϊԭʼ��������linkErrorΪNULL��
*		����linkErrorָ��ô����γɴ�������
* PreCondition:
*		�ޡ�
* PostCondition:
*		�ޡ�
*/
extern "C" int EH4A_log_error(IN int error_code,IN int *linkError,IN const char *text,IN const char *file,IN int line);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_log_event(int event_code, const char *text, const char *file, int line)
* Parameters:
*    -input:
*       int error_code:                          -- ����/�쳣��
*       char *text:                              -- ����/�쳣���ݣ�����󳤶�Ϊ256
*       char *file:                              -- ���������Դ�ļ�������󳤶�Ϊ80
*       int line:                                -- ��������������к�
*    -int/out:
*    -output:
* Returns: 
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		�ú���������¼ͨ���¼�������д���ڴ�ʹ��̼�¼�ļ��ļ��С�
*		�ú�����Ӧ���ж�/�쳣��������е��á��ַ�������Ҫ�󽫱��ضϡ�
*/
extern "C" int EH4A_log_event(IN int event_code,IN  const char *text,IN const char *file,IN int line);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_log_event(int event_code, const char *text, const char *file, int line)
* Parameters:
*    -input:
*       char *exception_text:                     -- �쳣��Ϣ������󳤶�Ϊ256
*       int signal:                               -- �����쳣���ź�
*       int code:                                 -- �쳣����
*       char *file:                               -- ���������Դ�ļ������ļ�������󳤶�Ϊ80
*       ine line:                                 -- ��������������к�
*    -int/out:
*    -output:
* Returns: int
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
* Description:
*		�ú�����¼һ���쳣.�쳣��Ϣ����¼����פ�ڴ�ʹ��̼�¼�ļ���.�ַ�������Ҫ�󽫱��ضϡ�
*/
extern "C" int EH4A_log_exception(IN const char *exception_text,IN int signal,IN int code,IN const char *file,IN int line);
/**
* Include:
*    EH4A_if.h
* Function:
*    int SMEE_BOOL EH4A_is_log_exception(void)
* Parameters:
*    -input:
*    -int/out:
*    -output:
* Returns: 
* Description:
*		�ж��Ƿ����쳣�������庯����ֵΪSMEE_TRUE��
*/
extern "C" SMEE_BOOL EH4A_is_log_exception(void);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_error_2_string(int exception_code,char* buffer,int len)
* Parameters:
*    -input:
*       int exception_code                      -- ��ת�����쳣����
*       int len                                 -- �ַ�������
*    -in/out:
*    -output:
*       char* buffer                            -- ת������ַ���
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
*       EH4A_PARAMETER_ERR                       -- ��������ȷ
* Description:
*       1�����쳣����ת��Ϊ��Ӧ�ַ�����
*       2��������ݿ��д��ڸ��쳣����ֱ�ӻ�ȡ��Ӧ���ַ�����
*       3��������ݿ��в����ڸ��쳣�룬��ֱ���ڱ���ת����
* PreCondition:
*       �ͻ��˺ͷ����CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       ���쳣��ת��Ϊ��Ӧ���ַ�����
*/
extern "C" int EH4A_error_2_string(IN int error_code,OUT char* buffer,IN int len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_string_2_error(const char* buffer,int* exception_code )
* Parameters:
*    -input:
*       const char* buffer                       -- ��ת���ַ���
*    -in/out:
*    -output: 
*       int* exception_code                      -- ת�����쳣����
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- ����ϵͳ���⵼�µ��쳣
*       EH4A_INVALID_ERROR_CODE                  -- �쳣�벻���Ϲ淶����0x45480000 ǰ��λ��ʾ�������
*       EH4A_PARAMETER_ERR                       -- ��������ȷ
* Description:
*       ���쳣�ַ���ת��Ϊ��Ӧ�쳣����
* PreCondition:
*       �ͻ��˺ͷ����CN�Ѿ��ɹ���ʼ����
* PostCondition:
*       ���ַ���ת��Ϊ��Ӧ���쳣��
*/
extern "C" int EH4A_string_2_error(OUT const char* buffer,OUT int* error_code );

/*== Macro function definitions �͵��������==============================================*/

#if TARGET_OS == SUN_OS || TARGET_OS == VXWORKS_OS

#define EH4A_free_error_text(text) free(text)

#elif TARGET_OS == WIN32_OS

#define EH4A_free_error_text(text)

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

