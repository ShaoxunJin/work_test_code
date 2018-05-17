/*******************************************************************************
* Copyright (C) 2009, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : ADAE
* ������� : TR
* ģ������ : libTR4A
* �ļ����� : TR4A_tc.h
* ��Ҫ���� :
* ��ʷ��¼ :
* �汾      ����        ����    ����
* V.0    2009-05-18    ��Ⱥ��  �����ļ�
*******************************************************************************/

#ifndef _TR4A_IF_H_
#define _TR4A_IF_H_

#include "smee.h"
#include "ADAE.h"
#include "TR4A_tc.h"
#include <stdarg.h>

/* Function:
*      SMEE_EXPORT int TR4A_set_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod, IN TR4A_TRACE_MODE_ENUM trace_mod, IN TR4A_REQ_MODE_ENUM datareq_mod )
* Parameters:
*   -input:
*       const char*             com_id       ������ƣ���������������д��ĸ��ɣ��硱CN��
*       TR4A_SIM_MODE_ENUM      sim_mode     ����ģʽ
*       TR4A_TRACE_MODE_ENUM    trace_mode   ׷��ģʽ
*       TR4A_REQ_MODE_ENUM      datareq_mod  ����ע��ģʽ
*   -input/output:
*   -output:
* Returns: int
*      OK                       ���óɹ�
*      TR4A_SYSTEM_ERR          CNͨѶ�������ϵͳ����
*      TR4A_PARAMETER_ERR       ��������
* Description:
*      ����ģʽ
*PreCondition:
*          ��ǰ����ͨѶ�ѳ�ʼ����
* PostCondition:
*          Ŀ�������ģʽ�����á�

*/
SMEE_EXPORT int TR4A_set_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod, IN TR4A_TRACE_MODE_ENUM trace_mod, IN TR4A_REQ_MODE_ENUM datareq_mod );


/* Function:
*      SMEE_EXPORT int TR4A_get_mode( IN const char* comp_id, OUT TR4A_SIM_MODE_ENUM* sim_mod, OUT TR4A_TRACE_MODE_ENUM* trace_mod, OUT TR4A_REQ_MODE_ENUM* datareq_mod )
* Parameters:
*   -input:
*      const char* comp_id      ������ƣ���������������д��ĸ��ɣ��硱CN��
*   -input/output: ��
*   -output:
*      TR4A_SIM_MODE_ENUM* sim_mod           ���ڻ�ȡ����ģʽֵ
*      TR4A_TRACE_MODE_ENUM * trace_mod      ���ڻ�ȡ����ģʽֵ
*      TR4A_REQ_MODE_ENUM * datareq_mod      ���ڻ�ȡ����ע��ģʽֵ
* Returns: int
*      OK                   ��ȡ�ɹ�
*      TR4A_SYSTEM_ERR      CNͨѶ�������ϵͳ����
*      TR4A_PARAMETER_ERR   ��������
* Description:
*      ��ȡģʽ
*PreCondition:
*          ģʽ�����ڴ��ʼ���ɹ���
* PostCondition:
*          Ŀ������ĵ�ǰģʽ����ȡ��
*/
SMEE_EXPORT int TR4A_get_mode( IN const char* comp_id, OUT TR4A_SIM_MODE_ENUM* sim_mod, OUT TR4A_TRACE_MODE_ENUM* trace_mod, OUT TR4A_REQ_MODE_ENUM* datareq_mod );


/* Function:
*      SMEE_EXPORT void TR4A_trace( IN const char* comp_id, IN TR4A_TRACE_MODE_ENUM from_where, IN const char* func_name, IN const char* format_spec, ... )
* Parameters:
*   -input:
*      const char* comp_id                ������ƣ���������������д��ĸ��ɣ��硱CN��
*      TR4A_TRACE_MODE_ENUM  from_where   ����ģʽ������ģʽֻ�ܴ����µļ�����ѡȡ��
*                                         TR4A_TRACE_INT,
*                                         TR4A_TRACE_EXT,
*										  TR4A_TRACE_REAL_TIME

*      const char* func_name              ��ǰ�������ƣ��Ƽ�д��__SMEE_FUNC__�������к��������ó���80���ַ���
*      const char* format_spec            ��ʽ���ַ���������ָ�������ʾ��ʽ����
*       ...                               ��ʽ����,��ϸ��μ���ADAEϵͳTR���ʹ�ü�ά���ֲ�.doc����
*   -input/output: ��
*   -output: ��
* Returns: ��
* Description:
*      ���������Ϣ
*PreCondition:
*          ģʽ�����ڴ��ʼ���ɹ����Ҹ���ģʽ����ƥ��ɹ��������ƥ����ڹ�ϵ���£�
*          1) ��TR4A_trace�ĸ���ģʽΪTR4A_TRACE_INT����TR4A_set_mode��ĸ���ģʽӦ��ӦTR4A_TRACE_INT��
*		   TR4A_TRACE_INT_EXT��TR4A_INT_REAL��TR4A_TRACE_INT_EXT_REAL�е�һ�֣�
*		   2) ��TR4A_trace�ĸ���ģʽΪTR4A_TRACE_EXT����TR4A_set_mode��ĸ���ģʽӦ��ӦTR4A_TRACE_EXT��
*		   TR4A_TRACE_INT_EXT��TR4A_EXT_REAL��TR4A_TRACE_INT_EXT_REAL�е�һ�֣�
*		   3) ��TR4A_trace�ĸ���ģʽΪTR4A_TRACE_REAL_TIME����TR4A_set_mode��ĸ���ģʽӦ��ӦTR4A_TRACE_REAL_TIME��
* PostCondition:
*          ���ݸ���ģʽ��ӡtrace��Ϣ����̨�ļ���ʵʱ�����ڴ档
*/
SMEE_EXPORT void TR4A_trace( IN const char* comp_id, IN TR4A_TRACE_MODE_ENUM from_where, IN const char* func_name, IN const char* format_spec, ... );


/* Function:
*      SMEE_EXPORT int TR4A_data_request( IN const char* comp_id, IN TR4A_REQ_MODE_ENUM from_where, IN const char* func_name, IN const char* input_format, IN const char* output_format, ... )
* Parameters:
*   -input:
*      const char* comp_id             ������ƣ���������������д��ĸ��ɣ��硱CN��
*      TR4A_REQ_MODE from_where        ����ע��ģʽ������ע��ģʽֻ�ܴ����µļ�����ѡȡ��
*                                      TR4A_REQ_INT_INPUT
*                                      TR4A _REQ_INT_OUTPUT
*                                      TR4A _REQ_EXT_INPUT
*                                      TR4A _REQ_EXT_OUTPUT

*      const char *func_name           ��ǰ�������ƣ��Ƽ�д��__SMEE_FUNC__�������к��������ó���80���ֽڡ�
*      const char *input_format        ����ĸ�ʽ�ַ������ò������趨��������Ϊ���������ļ��ݣ����ڸð汾���ԣ�������κκϷ��ĸ�ʽ�ַ���������ΪNULL����
*      const char *output_format       ����ĸ�ʽ�ַ���,��ϸ��μ���ADAEϵͳTR���ʹ�ü�ά���ֲ�.doc����
*       ��                             ���������ʽ����,��ϸ��μ���ADAEϵͳTR���ʹ�ü�ά���ֲ�.doc����
*   -input/output:
*      ��             �������������ʽ����
*   -output: 
*      ��             ���������ʽ����
* Returns: int
*     OK                               ִ�гɹ�
*     TR4A_SYSTEM_ERR                  ϵͳ����
*     TR4A_PARAMETER_ERR               ��������
*     TR4A_ TR4A_NOT_INITIALIZED_ERR   TR��ʼ������
*    TR4A_INVALID_FORMAT_ERR           ��ʽ����
* Description:
*      ����ע��
*PreCondition:
*          ģʽ�����ڴ��ʼ���ɹ���������ע��ģʽ���óɹ���
* PostCondition:
*          
*/
SMEE_EXPORT int TR4A_data_request( IN const char* comp_id, IN TR4A_REQ_MODE_ENUM from_where, IN const char* func_name, IN const char* input_format, IN const char* output_format, ... );


/* Function:
*      SMEE_EXPORT SMEE_BOOL TR4A_check_sim_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod )
* Parameters:
*   -input:
*      const char* comp_id             ������ƣ���������������д��ĸ��ɣ��硱CN��
*      TR4A_SIM_MODE_ENUM  sim_mod     ����ģʽ
*   -input/output: ��
*   -output: ��
* Returns: SMEE_BOOL����
*      SMEE_TRUE         ģʽƥ��
*      SMEE_FALSE        ģʽ��ƥ����������
* Description:
*      ������ģʽ
*PreCondition:
*          ģʽ�����ڴ��ʼ����
* PostCondition:
*          ���ؼ���ֵ��
*/
SMEE_EXPORT SMEE_BOOL TR4A_check_sim_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod );


/* Function:
*      SMEE_EXPORT int TR4A_saveRT(IN const char* comp_id, IN const char* proc_id)
* Parameters:
*   -input:
*      const char* comp_id             ������ƣ���������������д��ĸ��ɣ��硱CN��
*      const char* proc_id             ������������������ƣ����ó���35���ֽ�
*   -input/output: ��
*   -output: ��
* Returns: int
*      OK                               ���óɹ�
*      TR4A_PARAMETER_ERR               ��������	

* Description:
*      ʵʱģʽ�½��̵ĸ�����Ϣ�ı���
*PreCondition:
*          ʵʱtrace�Ѿ���ӡ�������ڴ�
* PostCondition:
*          ��ؽ��̵�ʵʱtrace�ӹ����ڴ汣�浽�ļ��С�
*/
SMEE_EXPORT int TR4A_saveRT(IN const char* comp_id, IN const char* proc_id);


#endif /*_TR4A_IF_H_*/
