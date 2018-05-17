/**************************************************************
* Copyright (C) 2010, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* �� Ʒ �� : ADAE
* ������� : EH
* ģ������ : EH4A
* �ļ����� : EH4A_config.h
* ��Ҫ���� : �쳣�ָ�ѡ������ͷ�ļ������û� ����
* ��ʷ��¼ : 
* �汾   ����        	����        ���� 
* V1.0   2010-10-14     buxj 		����
***************************************************************/
#ifndef __EH4A_CONFIG_H__
#define __EH4A_CONFIG_H__

/* �쳣�ָ�ѡ�� */
typedef enum
{
	EH4A_RESP_MIN = -1,
	EH4A_RESP_ABORT,                        
	EH4A_RESP_CANCEL,                          
	EH4A_RESP_CONFIRM,                        
	EH4A_RESP_CONTINUE,                        
	EH4A_RESP_FAIL,                           
	EH4A_RESP_FINISH,                          
	EH4A_RESP_PAUSE,                           
	EH4A_RESP_PROCEED,                         
	EH4A_RESP_QUIT,                           
	EH4A_RESP_RESUME,                          
	EH4A_RESP_RETRY,                         
	EH4A_RESP_STOP,                           
	EH4A_RESP_TERMINATE,                      
	EH4A_RESP_CANCEL_BATCH,                   
	EH4A_RESP_HALT_BATCH,                     
	EH4A_RESP_FINISH_BATCH,                   
	EH4A_RESP_RESUME_BATCH,                  
	EH4A_RESP_TERMINATE_BATCH,               
	EH4A_RESP_USE_DEFAULT_VAL_BATCH,          
	EH4A_RESP_CLIP_VAL_RANGE_BATCH,           
	EH4A_RESP_DISCARD_WAFER,                  
	EH4A_RESP_FEED_WAFER,                     
	EH4A_RESP_REJECT_WAFER,                    
	EH4A_RESP_REMOVE_ALL_WAFERS,               
	EH4A_RESP_ACCEPT_RETICLE,                  
	EH4A_RESP_REJECT_RETICLE,                 
	EH4A_RESP_ABORT_INITIALISATION,           
	EH4A_RESP_CANCEL_INITIALISATION,          
	EH4A_RESP_CONTINUE_INITIALISATION,        
	EH4A_RESP_CANCEL_CARRIER_INSPEC,          
	EH4A_RESP_CHECK_CARRIER_AND_RETRY,        
	EH4A_RESP_NEW_CARRIER,                    
	EH4A_RESP_NO_NEW_CARRIER,                 
	EH4A_RESP_REPLACE_CARRIER,                
	EH4A_RESP_CLOSE_COVER,                     
	EH4A_RESP_COVERS_CLOSED,                   
	EH4A_RESP_DOWN,                            
	EH4A_RESP_UP,                           
	EH4A_RESP_UNKNOWN_UP,                      
	EH4A_RESP_CANCEL_MOVE,                     
	EH4A_RESP_CONTINUE_MOVE,                   
	EH4A_RESP_NO,                             
	EH4A_RESP_YES,                             
	EH4A_RESP_CANCEL_UNSAFE,                   
	EH4A_RESP_SAFE_TO_PROCEED,                 
	EH4A_RESP_NO_UNSAFE,                     
	EH4A_RESP_YES_SAFE,                        
	EH4A_RESP_PORT1,                         
	EH4A_RESP_PORT2,                        
	EH4A_RESP_PORT3,                          
	EH4A_RESP_PORT4,                           
	EH4A_RESP_CANCEL_UNLOAD,                   
	EH4A_RESP_QUIT_CALIBRATION,                
	EH4A_RESP_SKIP,                           
	EH4A_RESP_VIEW_REPORT,                     
	EH4A_RESP_RETRY_INSPEC,                    
	EH4A_RESP_INIT_DRIVER,
	/*����Ϊ�û��Զ��岿�֣��û����Ը�����Ҫ�޸�ö�����ƣ�����������ɾ*/
	EH4A_RESP_DELETE,
	EH4A_RESP_MODIFY,
	EH4A_RESP_NEW_POD,
	EH4A_RESP_CLEAN_RETICLE,
	EH4A_RESP_USER_5,
	EH4A_RESP_USER_6,
	EH4A_RESP_USER_7,
	EH4A_RESP_USER_8,
	EH4A_RESP_USER_9,
	EH4A_RESP_USER_10,
	EH4A_RESP_USER_11,
	EH4A_RESP_USER_12,
	EH4A_RESP_USER_13,
	EH4A_RESP_USER_14,
	EH4A_RESP_USER_15,
	EH4A_RESP_USER_16,
	EH4A_RESP_USER_17,
	EH4A_RESP_USER_18,
	EH4A_RESP_USER_19,
	EH4A_RESP_USER_20,
	EH4A_RESP_USER_21,
	EH4A_RESP_USER_22,
	EH4A_RESP_USER_23,
	EH4A_RESP_USER_24,
	EH4A_RESP_USER_25,
	EH4A_RESP_USER_26,
	EH4A_RESP_USER_27,
	EH4A_RESP_USER_28,
	EH4A_RESP_USER_29,
	EH4A_RESP_USER_30,
	EH4A_RESP_USER_31,
	EH4A_RESP_USER_32,
	EH4A_RESP_USER_33,
	EH4A_RESP_USER_34,
	EH4A_RESP_USER_35,
	EH4A_RESP_USER_36,
	EH4A_RESP_USER_37,
	EH4A_RESP_USER_38,
	EH4A_RESP_USER_39,
	EH4A_RESP_USER_40,
	EH4A_RESP_USER_41,
	EH4A_RESP_USER_42,
	EH4A_RESP_USER_43,
	EH4A_RESP_USER_44,
	EH4A_RESP_USER_45,
	EH4A_RESP_USER_46,
	EH4A_RESP_USER_47,
	EH4A_RESP_USER_48,
	EH4A_RESP_USER_49,
	EH4A_RESP_USER_50,
	EH4A_RESP_USER_51,
	EH4A_RESP_USER_52,
	EH4A_RESP_USER_53,
	EH4A_RESP_USER_54,
	EH4A_RESP_USER_55,
	EH4A_RESP_USER_56,
	EH4A_RESP_USER_57,
	EH4A_RESP_USER_58,
	EH4A_RESP_USER_59,
	EH4A_RESP_USER_60,
	EH4A_RESP_USER_61,
	EH4A_RESP_USER_62,
	EH4A_RESP_USER_63,
	EH4A_RESP_USER_64,
	EH4A_RESP_USER_65,
	EH4A_RESP_USER_66,
	EH4A_RESP_USER_67,
	EH4A_RESP_USER_68,
	EH4A_RESP_USER_69,
	EH4A_RESP_USER_70,
	EH4A_RESP_USER_71,
	EH4A_RESP_USER_72,
	EH4A_RESP_USER_73,
	EH4A_RESP_USER_74,
	EH4A_RESP_USER_75,
	EH4A_RESP_USER_76,
	EH4A_RESP_USER_77,
	EH4A_RESP_USER_78,
	EH4A_RESP_USER_79,
	EH4A_RESP_USER_80,
	EH4A_RESP_USER_81,
	EH4A_RESP_USER_82,
	EH4A_RESP_USER_83,
	EH4A_RESP_USER_84,
	EH4A_RESP_USER_85,
	EH4A_RESP_USER_86,
	EH4A_RESP_USER_87,
	EH4A_RESP_USER_88,
	EH4A_RESP_USER_89,
	EH4A_RESP_USER_90,
	EH4A_RESP_USER_91,
	EH4A_RESP_USER_92,
	EH4A_RESP_USER_93,
	EH4A_RESP_USER_94,
	EH4A_RESP_USER_95,
	EH4A_RESP_USER_96,
	EH4A_RESP_USER_97,
	EH4A_RESP_USER_98,
	EH4A_RESP_USER_99,
	EH4A_RESP_USER_100,
	EH4A_RESP_USER_101,
	EH4A_RESP_USER_102,
	EH4A_RESP_USER_103,
	EH4A_RESP_USER_104,
	EH4A_RESP_USER_105,
	EH4A_RESP_USER_106,
	EH4A_RESP_USER_107,
	EH4A_RESP_USER_108,
	EH4A_RESP_USER_109,
	EH4A_RESP_USER_110,
	EH4A_RESP_USER_111,
	EH4A_RESP_USER_112,
	EH4A_RESP_USER_113,
	EH4A_RESP_USER_114,
	EH4A_RESP_USER_115,
	EH4A_RESP_USER_116,
	EH4A_RESP_USER_117,
	EH4A_RESP_USER_118,
	EH4A_RESP_USER_119,
	EH4A_RESP_USER_120,
	EH4A_RESP_USER_121,
	EH4A_RESP_USER_122,
	EH4A_RESP_USER_123,
	EH4A_RESP_USER_124,
	EH4A_RESP_USER_125,
	EH4A_RESP_USER_126,
	EH4A_RESP_USER_127,
	EH4A_RESP_USER_128,
	EH4A_RESP_MAX
}EH4A_EXCEPTION_RECOVERY_OPTION_ENUM;

#endif