/*******************************************************************************
* Copyright (C) 2009, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : ADAE
* 所属组件 : TR
* 模块名称 : libTR4A
* 文件名称 : TR4A_tc.h
* 概要描述 :
* 历史记录 :
* 版本      日期        作者    内容
* V.0    2009-05-18    唐群晖  创建文件
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
*       const char*             com_id       组件名称，它必须由两个大写字母组成，如”CN”
*       TR4A_SIM_MODE_ENUM      sim_mode     仿真模式
*       TR4A_TRACE_MODE_ENUM    trace_mode   追踪模式
*       TR4A_REQ_MODE_ENUM      datareq_mod  数据注入模式
*   -input/output:
*   -output:
* Returns: int
*      OK                       设置成功
*      TR4A_SYSTEM_ERR          CN通讯等引起的系统错误
*      TR4A_PARAMETER_ERR       参数错误
* Description:
*      设置模式
*PreCondition:
*          当前任务通讯已初始化。
* PostCondition:
*          目标组件的模式被设置。

*/
SMEE_EXPORT int TR4A_set_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod, IN TR4A_TRACE_MODE_ENUM trace_mod, IN TR4A_REQ_MODE_ENUM datareq_mod );


/* Function:
*      SMEE_EXPORT int TR4A_get_mode( IN const char* comp_id, OUT TR4A_SIM_MODE_ENUM* sim_mod, OUT TR4A_TRACE_MODE_ENUM* trace_mod, OUT TR4A_REQ_MODE_ENUM* datareq_mod )
* Parameters:
*   -input:
*      const char* comp_id      组件名称，它必须由两个大写字母组成，如”CN”
*   -input/output: 无
*   -output:
*      TR4A_SIM_MODE_ENUM* sim_mod           用于获取仿真模式值
*      TR4A_TRACE_MODE_ENUM * trace_mod      用于获取跟踪模式值
*      TR4A_REQ_MODE_ENUM * datareq_mod      用于获取数据注入模式值
* Returns: int
*      OK                   获取成功
*      TR4A_SYSTEM_ERR      CN通讯等引起的系统错误
*      TR4A_PARAMETER_ERR   参数错误
* Description:
*      获取模式
*PreCondition:
*          模式共享内存初始化成功。
* PostCondition:
*          目标组件的当前模式被获取。
*/
SMEE_EXPORT int TR4A_get_mode( IN const char* comp_id, OUT TR4A_SIM_MODE_ENUM* sim_mod, OUT TR4A_TRACE_MODE_ENUM* trace_mod, OUT TR4A_REQ_MODE_ENUM* datareq_mod );


/* Function:
*      SMEE_EXPORT void TR4A_trace( IN const char* comp_id, IN TR4A_TRACE_MODE_ENUM from_where, IN const char* func_name, IN const char* format_spec, ... )
* Parameters:
*   -input:
*      const char* comp_id                组件名称，它必须由两个大写字母组成，如”CN”
*      TR4A_TRACE_MODE_ENUM  from_where   跟踪模式，跟踪模式只能从如下的几种中选取：
*                                         TR4A_TRACE_INT,
*                                         TR4A_TRACE_EXT,
*										  TR4A_TRACE_REAL_TIME

*      const char* func_name              当前函数名称（推荐写成__SMEE_FUNC__），其中函数名不得超过80个字符。
*      const char* format_spec            格式化字符串，用来指定如何显示格式参数
*       ...                               格式参数,详细请参见《ADAE系统TR组件使用及维护手册.doc》。
*   -input/output: 无
*   -output: 无
* Returns: 无
* Description:
*      输出跟踪信息
*PreCondition:
*          模式共享内存初始化成功，且跟踪模式设置匹配成功，具体的匹配对于关系如下：
*          1) 若TR4A_trace的跟踪模式为TR4A_TRACE_INT，则TR4A_set_mode里的跟踪模式应对应TR4A_TRACE_INT、
*		   TR4A_TRACE_INT_EXT、TR4A_INT_REAL和TR4A_TRACE_INT_EXT_REAL中的一种；
*		   2) 若TR4A_trace的跟踪模式为TR4A_TRACE_EXT，则TR4A_set_mode里的跟踪模式应对应TR4A_TRACE_EXT、
*		   TR4A_TRACE_INT_EXT、TR4A_EXT_REAL和TR4A_TRACE_INT_EXT_REAL中的一种；
*		   3) 若TR4A_trace的跟踪模式为TR4A_TRACE_REAL_TIME，则TR4A_set_mode里的跟踪模式应对应TR4A_TRACE_REAL_TIME。
* PostCondition:
*          根据跟踪模式打印trace信息到后台文件或实时共享内存。
*/
SMEE_EXPORT void TR4A_trace( IN const char* comp_id, IN TR4A_TRACE_MODE_ENUM from_where, IN const char* func_name, IN const char* format_spec, ... );


/* Function:
*      SMEE_EXPORT int TR4A_data_request( IN const char* comp_id, IN TR4A_REQ_MODE_ENUM from_where, IN const char* func_name, IN const char* input_format, IN const char* output_format, ... )
* Parameters:
*   -input:
*      const char* comp_id             组件名称，它必须由两个大写字母组成，如”CN”
*      TR4A_REQ_MODE from_where        数据注入模式，数据注入模式只能从如下的几种中选取：
*                                      TR4A_REQ_INT_INPUT
*                                      TR4A _REQ_INT_OUTPUT
*                                      TR4A _REQ_EXT_INPUT
*                                      TR4A _REQ_EXT_OUTPUT

*      const char *func_name           当前函数名称（推荐写成__SMEE_FUNC__），其中函数名不得超过80个字节。
*      const char *input_format        输入的格式字符串，该参数的设定，仅仅是为了与第三版的兼容，对于该版本而言，输入的任何合法的格式字符串，都作为NULL看待
*      const char *output_format       输出的格式字符串,详细请参见《ADAE系统TR组件使用及维护手册.doc》。
*       …                             部分输入格式参数,详细请参见《ADAE系统TR组件使用及维护手册.doc》。
*   -input/output:
*      …             部分输入输出格式参数
*   -output: 
*      …             部分输入格式参数
* Returns: int
*     OK                               执行成功
*     TR4A_SYSTEM_ERR                  系统错误
*     TR4A_PARAMETER_ERR               参数错误
*     TR4A_ TR4A_NOT_INITIALIZED_ERR   TR初始化错误
*    TR4A_INVALID_FORMAT_ERR           格式错误
* Description:
*      数据注入
*PreCondition:
*          模式共享内存初始化成功，且数据注入模式设置成功。
* PostCondition:
*          
*/
SMEE_EXPORT int TR4A_data_request( IN const char* comp_id, IN TR4A_REQ_MODE_ENUM from_where, IN const char* func_name, IN const char* input_format, IN const char* output_format, ... );


/* Function:
*      SMEE_EXPORT SMEE_BOOL TR4A_check_sim_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod )
* Parameters:
*   -input:
*      const char* comp_id             组件名称，它必须由两个大写字母组成，如”CN”
*      TR4A_SIM_MODE_ENUM  sim_mod     仿真模式
*   -input/output: 无
*   -output: 无
* Returns: SMEE_BOOL类型
*      SMEE_TRUE         模式匹配
*      SMEE_FALSE        模式不匹配或参数错误
* Description:
*      检查仿真模式
*PreCondition:
*          模式共享内存初始化。
* PostCondition:
*          返回检查的值。
*/
SMEE_EXPORT SMEE_BOOL TR4A_check_sim_mode( IN const char* comp_id, IN TR4A_SIM_MODE_ENUM sim_mod );


/* Function:
*      SMEE_EXPORT int TR4A_saveRT(IN const char* comp_id, IN const char* proc_id)
* Parameters:
*   -input:
*      const char* comp_id             组件名称，它必须由两个大写字母组成，如”CN”
*      const char* proc_id             上述组件所属进程名称，不得超过35个字节
*   -input/output: 无
*   -output: 无
* Returns: int
*      OK                               设置成功
*      TR4A_PARAMETER_ERR               参数错误	

* Description:
*      实时模式下进程的跟踪信息的保存
*PreCondition:
*          实时trace已经打印到共享内存
* PostCondition:
*          相关进程的实时trace从共享内存保存到文件中。
*/
SMEE_EXPORT int TR4A_saveRT(IN const char* comp_id, IN const char* proc_id);


#endif /*_TR4A_IF_H_*/
