/**************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产 品 号 : ADAE
* 所属组件 : EH
* 模块名称 : EH4A
* 文件名称 : EH4A_if.h
* 概要描述 : EH组件对外接口声明
* 历史记录 :
* 版本   日期        作者        内容
* V1.0   2009-4-9    buxj        创建
* V1.1   2009-5-31   buxj        添加老接口声明
* V1.2   2009-6-2    buxj        修改report_exception接口的option类型
                                 为EH4A_EXCEPTION_RECOVERY_OPTION_ENUM
* V1.3   2009-7-16   buxj        1、修改EH4A_get_active_componentwarnings的接口声明 
                                 2、修改EH4A_deactive_componentwarning-->EH4A_destroy_componentwarnings
                                 3、添加EH4A_deactive_exception接口
* V1.4   2009-7-22   buxj        添加前置条件和后置条件
* V1.5	 2011-1-6	 buxj		 1、添加EH4A_get_root_cause接口
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
*       int exception_code                      -- 待转换的异常代码
*       int len                                 -- 字符串长度
*    -in/out:
*    -output:
*       char* buffer                            -- 转换后的字符串
* Returns:
*      OK
*   EH4A_PARAMETER_ERR                          -- 接口参数不正确
*   EH4A_INVALID_ERROR_CODE                     -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       1、将异常代码转换为对应字符串。
*       2、如果数据库中存在该异常码则直接获取对应的字符串。
*       3、如果数据库中不存在该异常码，则直接在本地转换。
* PreCondition:
*       客户端和服务端CN已经成功初始化。
* PostCondition:
*       将异常码转换为对应的字符串。
*/
extern "C" int EH4A_error_to_string(IN int error_code,OUT char* buffer,IN int len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_string_to_error(const char* buffer,int* exception_code )
* Parameters:
*    -input:
*       const char* buffer                       -- 待转换字符串
*    -in/out:
*    -output: 
*       int* exception_code                      -- 转换后异常代码
* Returns:
*       OK
*       EH4A_PARAMETER_ERR                       -- 接口参数不正确
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       将异常字符串转换为对应异常代码
* PreCondition:
*       客户端和服务端CN已经成功初始化。
* PostCondition:
*       将字符串转换为对应的异常码
*/
extern "C" int EH4A_string_to_error(IN const char* buffer,OUT int* error_code );
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_show_exception(int exception_code, int *link_error, const char *file, int line, const char *format,…)
* Parameters:
*    -input:
*       int exception_code                        -- 异常代码
*       int* link_error                           -- 异常链，异常链最大长度为10
*       const char* file                          -- 异常发生的文件，该文件名最大长度为80
*       int line                                  -- 异常发生所在的行
*       const char* format                        -- 异常描述格式字符串
*       ...                                       -- 可变参数 最大长度为256
*    -in/out:
*    -output:
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                            -- 数据库连接出错或其他系统异常
*       EH4A_PARAMETER_ERR                         -- 接口参数不正确
*       EH4A_INVALID_ERROR_CODE                    -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       1、记录异常信息到日志文件。
*       2、异常信息由两部分组成，分别为配置表中的静态信息以及开发人员提供的动态信息。
* PreCondition:
*       CN已经成功初始化。
* PostCondition:
*       异常写入日志文件。
*/
extern "C" int EH4A_show_exception(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN const char *format, ...);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_show_exception_v(int exception_code, int *link_error, const char *file, int line, const char *format,va_list args)
* Parameters:
*    -input:
*       int exception_code                          -- 异常代码
*       int* link_error                             -- 异常链，该异常链最大长度为10
*       const char* file                            -- 异常发生的文件，文件名最大长度为80
*       int line                                    -- 异常发生所在的行
*       const char* format                          -- 异常描述格式字符串，最大长度为256
*       va_list args                                -- 可变参数
*    -in/out:
*    -output:
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                             -- 数据库连接出错或其他系统异常
*       EH4A_PARAMETER_ERR                          -- 接口参数不正确
*       EH4A_INVALID_ERROR_CODE                     -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       1、记录异常信息到日志文件。
*       2、异常信息由两部分组成，分别为配置表中的静态信息以及开发人员提供的动态信息。
* PreCondition:
*       CN已经成功初始化。
* PostCondition:
*       异常写入日志文件。
*/
extern "C" int EH4A_show_exception_v(IN int exception_code,IN int *link_error, IN const char *file, IN int line,IN const char *format,va_list args);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_report_exception(int exception_code, int *link_error, const char *file, int line,EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response, const char *format,…)
* Parameters:
*    -input:
*       int exception_code                             -- 异常代码
*       int* link_error                                -- 异常链，异常链长度最大值为10
*       const char* file                               -- 异常发生的文件，文件名最大长度为80
*       int line                                       -- 异常发生所在的行
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[]   -- 异常恢复选项
*       const char* format                             -- 异常描述格式字符串，最大长度为256
*       ...                                            -- 可变参数
*    -in/out:
*    -output:
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response  -- 操作员执行的异常恢复措施
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                                -- 系统异常
*       EH4A_PARAMETER_ERR                             -- 接口参数不正确
*       EH4A_INVALID_ERROR_CODE                        -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       向操作员报告异常，通过和操作员的交互执行异常恢复，并记录异常信息到日志
* PreCondition:
*       客户端、EHMA、EHLO和界面CN已经成功初始化。
* PostCondition:
*       异常写入日志文件，并且界面显示恢复选项，等待操作员选择。
*/
extern "C" int EH4A_report_exception(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],OUT EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response,IN const char *format,...);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_report_exception(int exception_code, int *link_error, const char *file, int line,EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response, const char *format,va_list args)
* Parameters:
*    -input:
*       int exception_code                            -- 异常代码
*       int* link_error                               -- 异常链，最大长度为10
*       const char* file                              -- 异常发生的文件，文件名最大长度为80
*       int line                                      -- 异常发生所在的行
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[]  -- 异常恢复选项
*       const char* format                            -- 异常描述格式字符串，最大长度为256
*       va_list args                                  -- 可变参数
*    -in/out:
*    -output:
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response --操作员执行的异常恢复措施
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                                -- 系统异常
*       EH4A_PARAMETER_ERR                             -- 接口参数不正确
*       EH4A_INVALID_ERROR_CODE                        -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       向操作员报告异常，通过和操作员的交互执行异常恢复，并记录异常信息到日志。
* PreCondition:
*       客户端、EHMA、EHLO和界面CN已经成功初始化。
* PostCondition:
*       异常写入日志文件，并且界面显示恢复选项，等待操作员选择。
*/
extern "C" int EH4A_report_exception_v(IN int exception_code,IN int *link_error,IN const char *file,IN int line,IN EH4A_EXCEPTION_RECOVERY_OPTION_ENUM option[],OUT EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* response,IN const char *format,IN va_list args);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_log_mode(EH4A_LOG_MODE_ENUM log_mode)
* Parameters:
*    -input:
*       EH4A_LOG_MODE_ENUM log_mode				  -- 异常记录模式-本地或服务端
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_PARAMETER_ERR                       -- 接口参数不正确
* Description:
*		设置异常的记录模式。
* PreCondition:
*		CN已经成功初始化。
* PostCondition:
*		异常记录模式改变。
*/
extern "C" int EH4A_set_log_mode(IN EH4A_LOG_MODE_ENUM log_mode);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_log_mode(EH4A_LOG_MODE_ENUM log_mode)
* Parameters:
*    -input:
*       EH4A_LOG_MODE_ENUM* log_mode             -- 异常记录模式-本地或服务端
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_PARAMETER_ERR				  		 -- 接口参数不正确
* Description:
*		获取异常的记录模式。
* PreCondition:
*		CN已经成功初始化。
* PostCondition:
*		获取当前记录模式
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
*		安装信号处理函数。
* PreCondition:
*		无
* PostCondition:
*	 信号处理函数被安装。
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
*		 卸载信号处理函数。
* PreCondition:
*		信号被安装。
* PostCondition:
*		信号处理函数被卸载，任务不再接收信号。
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
*       EH4A_CURR_EVENT * 异常处理环境指针。
* Description:
*		获取异常处理环境指针。
* PreCondition:
*		无
* PostCondition:
*		异常记录模式改变。
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
*       int 当前信号发生次数
* Description:
*		获取信号发生次数。
* PreCondition:
*		无
* PostCondition:
*		无
*/
extern "C" int EH4A_nr_sigsegv(void);
/**
* Include:
*    EH4A_if.h
* Function:
*    void EH4A_set_nr_sigsegv(int nr_sigsegv)
* Parameters:
*    -input:
*       int nr_sigsegv  信号发生次数
*    -in/out:
*    -output:
* Returns:
* Description:
*		设置信号发生次数。
* PreCondition:
*		无
* PostCondition:
*		信号发生次数被修改。
*/
extern "C" int EH4A_set_nr_sigsegv(IN int nr_sigsegv);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_set_alarm(int alarm_code,int alarm_id)
* Parameters:
*    -input:
*       int alarm_code                           -- 警告码  (暂时保留)
*		int alarm_id                             -- 警告码id（作为数据库中主键约束）
*    -in/out:
*    -output:
* Returns:
*	    OK
*       EH4A_SYSTEM_ERR                           -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                   -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		设置ALARM ITEM（设置EHIT_ALARM_ITEM 的IT4A_ATTR_VALUE值，高四字节为alarm_id值，低四字节存放为1），发送警告到界面，同时将设置的信息写入数据库中。
* PreCondition:
*		无
* PostCondition:
*		订阅表中的ALARM_SET状态被设置。
*/
extern "C" int EH4A_set_alarm(IN int alarm_code,IN int alarm_id);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_clear_alarm(int alarm_id)
* Parameters:
*    -input:
*       int alarm_id                              -- 警告码id                        
*    -in/out:
*    -output:
* Returns:
*		OK
*		EH4A_SYSTEM_ERR                             -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                     -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		在订阅数据库中，清除ALARM条目，如有变化由IT负责通知订阅组件（SECS manager),解除界面警告信息，同时清除数据库中该条警告记录
* PreCondition:
*		alarm_id对应的ALARM条目的已经存在。
* PostCondition:
*		订阅表中的ALARM_CLEAR状态被设置。
*/
extern "C" int EH4A_clear_alarm(IN int alarm_id);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_alarm(int alarm_id,bool *is_set);
* Parameters:
*    -input:
*       int alarm_id                           -- 警告id码
*    -in/out:
*    -output:
*       bool is_set                              -- 指定警告是否被设置
* Returns:
*		OK
*		EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		在订阅数据库中，获取指定ALARM条目的状态，如果设置过则is_set为TRUE，如果该ALARM被清除了，则is_set为FALSE
* PreCondition:
*		无
* PostCondition:
*		无
*/
extern "C" int EH4A_get_alarm(IN int alarm_id,OUT SMEE_BOOL *is_set);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_recovery_class(int exception_code,int *error_code, EH4A_EXCEPTION_RECOVERY_OPTION_ENUM* recovery_class);
* Parameters:
*    -input:
*       int exception_code                                    -- 异常代码
*    -in/out:
*    -output: 
*       int* error_code                                       -- 导致异常的根错误
*       EH4A_EXCEPTION_RECOVERY_OPTION_ENUM recovery_class    -- 根错误的恢复类
* Returns:
*		OK
*		EH4A_SYSTEM_ERR										  -- 由于系统问题导致的异常
*       EH4A_SYSTEM_ERR										          -- 参数错误
*       EH4A_INVALID_ERROR_CODE                               -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		 获取指定异常的恢复类。
* PreCondition:
*		指定异常码存在恢复选项。
* PostCondition:
*		指定异常码的最高等级的回复选项被获取。
*/
extern "C" int EH4A_get_recovery_class(IN int exception_code,OUT int *error_code,OUT EH4A_EXCEPTION_RECOVERY_CLASS_ENUM* recovery_class);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_active_componentwarnings(const char* com_name,int * warning_code)
* Parameters:
*    -input:
*       const char* com_name				     -- 组件名，最大长度为3
*    -in/out:
*    -output:
*       int* warning_list						 -- 警告列表
*       int* len								 -- 警告列表的长度，最大长度为32
* Returns:
*       OK
*       EH4A_PARAMETER_ERR
*       EH4A_SYSTEM_ERR                           -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*       获取指定组件的未处理的警告信息，当组件重启后用于检查是否存在需要处理或者销毁的警告
* PreCondition:
*		无
* PostCondition:
*		分配了警告列表的空间，后续必须调用EH4A_destroy_componentwarnings
*/
extern "C" int EH4A_get_active_componentwarnings(IN const char* com_name,OUT int * warning_list,OUT int *len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_destroy_componentwarnings(int* warning_list)
* Parameters:
*    -input:
*       int* warning_list                         -- 警告列表地址
*    -in/out:
*    -output:
* Returns:
*		OK
* Description:
*		释放EH4A_get_active_componentwarnings动态分配的保存警告信息的空间。
* PreCondition:
*		已经调用EH4A_get_active_componentwarnings。
* PostCondition:
*	    释放EH4A_get_active_componentwarnings分配的空间。
*/
extern "C" int EH4A_destroy_componentwarnings(IN int* warning_list);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_deactive_exception(int deactive_code,int exception_code,char* format,...)
* Parameters: 
*    -input:
*       int deactive_code                       -- 异常解决后的异常码，用于记录到日志文件，如果为OK，则忽略。
*       int exception_code                      -- 不需要在EH界面显示的异常代码
*       char* format                            -- 描述文档 
*       ...                                     -- 可变参数，最大长度为256
*    -in/out:
*    -output:
* Returns:
*	    OK
*		EH4A_SYSTEM_ERR                         --- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                 -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		解除已经恢复成功的异常或者不需要显示的警告信息。
* PreCondition:
*		指定异常已经发生并执行了恢复措施
* PostCondition:
*	    指定的异常不再提醒
*/
extern "C" int EH4A_deactive_exception(IN int deactive_code,IN int exception_code,IN char* format,...);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_exception_tree(int  exception_code, time_t time ,char* exception_tree);
* Parameters:
*    -input:
*       int exception_code                       -- 指定的异常代码
*       time_t time                              -- 异常发生的截止时间,默认为0，即当前时间
*    -in/out:
*    -output:
*       char* exception_tree                     -- 异常树，异常树的最大长度为409600
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
*       EH4A_PARAMETER_ERR                       -- 参数不正确
* Description:
*		 获取error级别的异常树。
* PreCondition:
*		主程序正常运行。
* PostCondition:
*		获取以字符形式表示的异常树。
*/
extern "C" int EH4A_get_exception_tree(IN int exception_code,IN time_t time, OUT char* exception_tree);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_get_root_cause(IN int exception_code,OUT int* root_cause);
* Parameters:
*    -input:
*       int exception_code                       -- 指定的异常代码
*		int stop_at_event_code						 -- 搜索终止条件(暂作保留不使用)
*    -in/out:
*    -output:
*       int* root_cause							 -- 指定异常的根错误
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
*       EH4A_PARAMETER_ERR                       -- 参数不正确
*		EH4A_NO_ROOT_CAUSE_ERR					 -- 不能找到错误码或者错误链中断无法确定根错误
* Description:
*		获取error级别的异常跟错误。
* PreCondition:
*		主程序正常运行。
* PostCondition:
*		获取根错误。
*/
extern "C" int EH4A_get_root_cause(IN int exception_code,IN int stop_at_event_code,OUT int* root_cause);
/**
* Include:
*    EH4A_if.h
* Function:
*   int EH2PSM_init(EH4A_EXCEPTION_RECOVERY_CLASS_ENUM restart_model)
* Parameters:
*    -input:
*       EH4A_EXCEPTION_RECOVERY_CLASS_ENUM        restart_model   重启类型
*    -in/out:
* Returns:
*       OK
*       EH4A_PARAMETER_ERR                       -- 接口参数不正确
* Description:
*       当重启平台时，SM通知EH解除警告信息
* PreCondition:
*       客户端和服务端CN已经成功初始化。
* PostCondition:
*      
*/
extern "C" int EH2PSM_init(IN EH4A_EXCEPTION_RECOVERY_CLASS_ENUM restart_model); 

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*第三版平台接口,仅仅为了保持兼容，请不要继续使用*/
/**
* Include:
*    EH4A_if.h
* Function:
*    char *EH4A_create_text(const char *fmt, ...)
* Parameters:
*    -intput:
*       const char *fmt     待转换的格式
*         .....             转换前的字符串
*    -int/out:
*    -output:
* Returns: 转换后的字符串
* Description:
*		输出格式化字符串格式。
* PreCondition:
*		主程序正常运行。
* PostCondition:
*		获取以字符形式表示的异常树。
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
* Returns：
* Description:
*		对捕获到的各种信号做相应处理。
* PreCondition:
*		无。
* PostCondition:
*		无。
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
* Returns：
* Description:
*		关闭异常模式。
* PreCondition:
*		无。
* PostCondition:
*		无。
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
* Returns：
* Description:
*		开启异常模式。
* PreCondition:
*		无。
* PostCondition:
*		无。
*/
extern "C" int EH4A_exception_logon(void);
/**
* Include:
*    EH4A_if.h
* Function:
*     intEH4A_log_error(int error_code, int *linkError,const char *text,const char *file, int line)
* Parameters:
*       int error_code:                          -- 错误/异常码
*       int *linkError:                          -- 原始错误码，错误链最大长度为10
*       const char *text:                        -- 错误/异常内容，其长度最大值为256
*       const char *file:                        -- 包含错误的源文件，文件名长度最大值为80
*       int line:                                -- 发生错误的所在行
*    -int/out:
*    -output:
* Returns：
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		调用接口LogRecord函数记录错误，将其写进内存和磁盘记录文件文件中。
*		该函数不应在中断/异常处理代码中调用。若该错误为原始根错误，则linkError为NULL，
*		否则linkError指向该错误，形成错误链表。
* PreCondition:
*		无。
* PostCondition:
*		无。
*/
extern "C" int EH4A_log_error(IN int error_code,IN int *linkError,IN const char *text,IN const char *file,IN int line);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_log_event(int event_code, const char *text, const char *file, int line)
* Parameters:
*    -input:
*       int error_code:                          -- 错误/异常码
*       char *text:                              -- 错误/异常内容，其最大长度为256
*       char *file:                              -- 包含错误的源文件，其最大长度为80
*       int line:                                -- 发生错误的所在行号
*    -int/out:
*    -output:
* Returns: 
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		该函数用来记录通用事件，将其写进内存和磁盘记录文件文件中。
*		该函数不应在中断/异常处理代码中调用。字符串不合要求将被截断。
*/
extern "C" int EH4A_log_event(IN int event_code,IN  const char *text,IN const char *file,IN int line);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_log_event(int event_code, const char *text, const char *file, int line)
* Parameters:
*    -input:
*       char *exception_text:                     -- 异常信息，其最大长度为256
*       int signal:                               -- 引起异常的信号
*       int code:                                 -- 异常代码
*       char *file:                               -- 包含错误的源文件，其文件名的最大长度为80
*       ine line:                                 -- 发生错误的所在行号
*    -int/out:
*    -output:
* Returns: int
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
* Description:
*		该函数记录一个异常.异常信息被记录在暂驻内存和磁盘记录文件中.字符串不合要求将被截断。
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
*		判断是否是异常，并定义函数初值为SMEE_TRUE。
*/
extern "C" SMEE_BOOL EH4A_is_log_exception(void);

/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_error_2_string(int exception_code,char* buffer,int len)
* Parameters:
*    -input:
*       int exception_code                      -- 待转换的异常代码
*       int len                                 -- 字符串长度
*    -in/out:
*    -output:
*       char* buffer                            -- 转换后的字符串
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
*       EH4A_PARAMETER_ERR                       -- 参数不正确
* Description:
*       1、将异常代码转换为对应字符串。
*       2、如果数据库中存在该异常码则直接获取对应的字符串。
*       3、如果数据库中不存在该异常码，则直接在本地转换。
* PreCondition:
*       客户端和服务端CN已经成功初始化。
* PostCondition:
*       将异常码转换为对应的字符串。
*/
extern "C" int EH4A_error_2_string(IN int error_code,OUT char* buffer,IN int len);
/**
* Include:
*    EH4A_if.h
* Function:
*    int EH4A_string_2_error(const char* buffer,int* exception_code )
* Parameters:
*    -input:
*       const char* buffer                       -- 待转换字符串
*    -in/out:
*    -output: 
*       int* exception_code                      -- 转换后异常代码
* Returns:
*       OK
*       EH4A_SYSTEM_ERR                          -- 由于系统问题导致的异常
*       EH4A_INVALID_ERROR_CODE                  -- 异常码不符合规范（如0x45480000 前两位表示组件名）
*       EH4A_PARAMETER_ERR                       -- 参数不正确
* Description:
*       将异常字符串转换为对应异常代码
* PreCondition:
*       客户端和服务端CN已经成功初始化。
* PostCondition:
*       将字符串转换为对应的异常码
*/
extern "C" int EH4A_string_2_error(OUT const char* buffer,OUT int* error_code );

/*== Macro function definitions 和第三版兼容==============================================*/

#if TARGET_OS == SUN_OS || TARGET_OS == VXWORKS_OS

#define EH4A_free_error_text(text) free(text)

#elif TARGET_OS == WIN32_OS

#define EH4A_free_error_text(text)

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

