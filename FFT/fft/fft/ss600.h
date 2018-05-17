/*******************************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ��   : SS600
* ������� :
* ģ������ :
* �ļ����� : ss600.h
* ��Ҫ���� : ��SSA��Ʒ��ص�ͨ�����ݽṹ
*            ���ǵ����ݶ���ķ�����,���ļ��ж���Ĳ����������ͻ�곣��������SMEE����淶
* ��ʷ��¼ :
* �汾     ��  ��    ��  ��    ��  ��
*
* V1.0   2010.01.11  �����    �½�,�ݸ�
* V1.1   2010.01.26  �����    �޶����ݷ�װ���͡������������岿������.
* V1.2   2012.01.31  ����          ����ϵͳ�궨��.
* V2.0   2012.05.25  �����    ���ݵ�̨ɨ��ϵ�й�̻�ƽ̨��Ҫ���޶���
******************************************************************************/
#ifndef SS600_H_
#define SS600_H_

#include "smee.h"

typedef enum
{
    SS600_MACHINE_TYPE_MIN = 0,
    SS600_A_600_20 = 1,  	/* SSA600/20 - 193 ������*/
    SS600_B_600_10 = 2, 	/* SSB600/10 - i�߹���*/
    SS600_A_600_30 = 3,  	/* SSA600/20 - 248 ������ */
    SS600_A_600_04 = 4,  	/* ���� */
    SS600_X_XXX_05 = 5,  	/* ���� */
    SS600_X_XXX_06 = 6,  	/* ���� */
    SS600_X_XXX_07 = 7,  	/* ���� */
    SS600_X_XXX_08 = 8,  	/* ���� */
    SS600_X_XXX_09 = 9,  	/* ���� */
	SS600_X_XXX_10 = 10,  	/* ���� */
	SS600_X_XXX_11 = 11,  	/* ���� */
	SS600_X_XXX_12 = 12,  	/* ���� */
	SS600_X_XXX_13 = 13,  	/* ���� */
	SS600_X_XXX_14 = 14,  	/* ���� */
	SS600_X_XXX_15 = 15,  	/* ���� */
    SS600_MACHINE_TYPE_MAX
}SS600_MACHINE_TYPE_ENUM; /* �������� */


/*ÿ��ͼ���CDFEC�������*/
#define SS600_MAX_CDFEC_AREA_NR_PER_IMAGE  250

/*ÿ����ģ���������ģ��׼��Ǹ���*/
#define SS600_MAX_RA_MARK_NR_PER_RETICLE  20

/*ÿ��ͼ��ĳ����ĸ���*/
#define SS600_MAX_FLD_NR_PER_IMG  500

/*ÿ��������ͼ�����*/
#define SS600_MAX_IMG_NR_PER_LOT  30

/*ÿ�����������ģ����*/
#define SS600_MAX_RETICLE_NR_PER_LAYER  12

/*ÿ����Ķ�׼��������*/
#define SS600_MAX_ALIGN_RECIPE_NR_PER_LAYER  100

/*ÿ�����SUBRECIPE����*/
#define SS600_MAX_SUBRECIPE_NR_PER_LAYER  20

/*ÿ�������Ĳ�������*/
#define SS600_MAX_LAYER_NR_PER_RECIPE  32

/*ÿ�����������������׼���Ը���*/
#define SS600_MAX_EVAL_STRAT_NR_PER_RECIPE  5

/*ÿ����׼���Ե�����Ǹ���*/
#define SS600_MAX_MARK_NR_PER_STRATEGY  200

/*ÿ������������Ƭ����*/
#define SS600_MAX_WFR_NR_PER_LOT 999

/*ÿ��������Ƭ�и���*/
#define SS600_MAX_CARRIER_NR_PER_LOT 20

/*����Ƭ�����*/
#define SS600_MAX_CARRIER_SLOT_NR 20


/*�û�������*/
#define SS600_MAX_USER_ID_SIZE  64

/*��ģID�Ĵ洢�ռ䳤��*/
#define SS600_MAX_RETICLE_ID_SIZE 64

/*��ģPOD ID�Ĵ洢�ռ䳤��*/
#define SS600_MAX_RETICLE_POD_ID_SIZE 64

/*��ǵı��ID�ĳ���*/
#define SS600_MAX_MARK_ID_SIZE 64

/*��ǵ�VARIANT ID�ĳ���*/
#define SS600_MAX_MARK_VARIANT_ID_SIZE 32

/*ͼ��ID�ĳ���*/
#define SS600_MAX_IMAGE_ID_SIZE 64

/*��Ƭ��GRID MODEL ID�ĳ���*/
#define SS600_MAX_GRID_MODEL_ID_SIZE 64

/*��׼����ID�ĳ���*/
#define SS600_MAX_STRATEGY_ID_SIZE 64

/*��ǵķ������Ը���*/
#define SS600_MAX_MARK_DIRECTIONS_SIZE 2

/*��ǵ���ɫ���Ը���*/
#define SS600_MAX_MARK_COLORS_SIZE 2

/*��ǵļ���*/
#define SS600_MAX_MARK_ORDERS_SIZE 7

/*��ǵ�����*/
#define SS600_MAX_MARK_PERIODS_SIZE 5

/*��ID�ĳ���*/
#define SS600_MAX_LAYER_ID_SIZE 64

/*����·�����ļ�������*/
#define SS600_MAX_FILENAME_SIZE 64

/*��·�����ļ�������*/
#define SS600_MAX_PATH_FILENAME_SIZE 1024

/*ͨ��С�ַ�������*/
#define SS600_SMALL_STRING_SIZE 64

/*ͨ���ַ�������*/
#define SS600_COMMON_STRING_SIZE 256

/*ͨ�ô������ַ�������*/
#define SS600_LARGE_STRING_SIZE 1024


/*------------ͨ��ö�ٶ���-------------*/

/* Wafer rotation */
typedef enum
{
    SS600_WAFER_ROT_MIN = 0,
    SS600_WAFER_ROT_0,
    SS600_WAFER_ROT_90,
    SS600_WAFER_ROT_270,
    SS600_WAFER_ROT_MAX
} SS600_WAFER_ROT_ENUM;


/* Focus Monitoring Threshold Type */
typedef enum
{
    SS600_THRESHOLD_TYPE_MIN = 0,
    SS600_THRESHOLD_TYPE_RELATIVE,
    SS600_THRESHOLD_TYPE_ABSOLUTE,
    SS600_THRESHOLD_TYPE_MAX
} SS600_THRESHOLD_TYPE_ENUM;

/* Reticle Class */
typedef enum
{
    SS600_RETICLE_CLASS_MIN = 0,
    SS600_RETICLE_CLASS_PRODUCTION,
    SS600_RETICLE_CLASS_CALIBRATION,
    SS600_RETICLE_CLASS_MAX
} SS600_RETICLE_CLASS_ENUM;

/* Reticle Size */
typedef enum
{
    SS600_RETICLE_SIZE_MIN = 0,
    SS600_RETICLE_SIZE_6INCH,
    SS600_RETICLE_SIZE_MAX
} SS600_RETICLE_SIZE_ENUM;

/* Reticle Type */
typedef enum
{
    SS600_RETICLE_TYPE_MIN = 0,
    SS600_RETICLE_TYPE_PSM,    /* ������ģ */
    SS600_RETICLE_TYPE_BINARY, /* ��������ģ */
    SS600_RETICLE_TYPE_MAX
} SS600_RETICLE_TYPE_ENUM;

/* Reticle Alignment Mark Type */
typedef enum
{
    SS600_RA_MARK_TYPE_MIN = 0,
    SS600_RA_MARK_TYPE_H,          /* Horizontal RA mark on reticle */
    SS600_RA_MARK_TYPE_SETUP_HOOK, /* Setup hook mark on fiducial plate */
    SS600_RA_MARK_TYPE_MAX
} SS600_RA_MARK_TYPE_ENUM;

/* Image Type */
typedef enum
{
    SS600_IMAGE_TYPE_MIN = 0,
    SS600_IMAGE_TYPE_PRODUCT,
    SS600_IMAGE_TYPE_MARK,
    SS600_IMAGE_TYPE_CLEAROUT,
    SS600_IMAGE_TYPE_SCRIBELANE_MARK,
    SS600_IMAGE_TYPE_MAX
} SS600_IMAGE_TYPE_ENUM;

/* Wafer Alignment Mark Type */
typedef enum
{
    SS600_WA_MARK_TYPE_MIN = 0,
    SS600_WA_MARK_TYPE_XPA,         /* XPA ��� */
    SS600_WA_MARK_TYPE_PM,          /* PM ��� */
    SS600_WA_MARK_TYPE_XPA_X,       /* XPA-X ��� */
    SS600_WA_MARK_TYPE_XPA_Y,       /* XPA-Y ��� */
    SS600_WA_MARK_TYPE_SPM_X,       /* SPM-X ��� */
    SS600_WA_MARK_TYPE_SPM_Y,       /* SPM-Y ��� */
    SS600_WA_MARK_TYPE_OV,          /* OV ��� */
    SS600_WA_MARK_TYPE_WGM,         /* WGM ��� */
    SS600_WA_MARK_TYPE_SM_XG,       /* SM-XG ��� */
    SS600_WA_MARK_TYPE_SM_XF,       /* SM-XF ��� */
    SS600_WA_MARK_TYPE_CSM_XG,      /* CSM-XG ��� */
    SS600_WA_MARK_TYPE_CSM_XF,      /* CSM-XF ��� */
    SS600_WA_MARK_TYPE_SM_YG,       /* SM-YG ��� */
    SS600_WA_MARK_TYPE_SM_YF,       /* SM-YF ��� */
    SS600_WA_MARK_TYPE_CSM_YG,      /* CSM-YG ��� */
    SS600_WA_MARK_TYPE_CSM_YF,      /* CSM-YF ��� */
    SS600_WA_MARK_TYPE_NSM_XG,      /* NSM-XG ��� */
    SS600_WA_MARK_TYPE_NSM_XF,      /* NSM-XF ��� */
    SS600_WA_MARK_TYPE_NCSM_XG,     /* NCSM-XG ��� */
    SS600_WA_MARK_TYPE_NCSM_XF,     /* NCSM-XF ��� */
    SS600_WA_MARK_TYPE_NSM_YG,      /* NSM-YG ��� */
    SS600_WA_MARK_TYPE_NSM_YF,      /* NSM-YF ��� */
    SS600_WA_MARK_TYPE_NCSM_YG,     /* NCSM-YG ��� */
    SS600_WA_MARK_TYPE_NCSM_YF,     /* NCSM-YF ��� */
    SS600_WA_MARK_TYPE_CSM_GXRz,    /* CSM-GXRz ��� */
    SS600_WA_MARK_TYPE_CSM_GYRz,    /* CSM-GYRz ��� */
    SS600_WA_MARK_TYPE_CSM_FXRz,    /* CSM-FXRz ��� */
    SS600_WA_MARK_TYPE_CSM_FYRz,    /* CSM-FYRz ��� */
    SS600_WA_MARK_TYPE_VSPM_AX,     /* VSPM_AX ��� */
    SS600_WA_MARK_TYPE_VSPM_BX,     /* VSPM_BX ��� */
    SS600_WA_MARK_TYPE_VSPM_CX,     /* NVSM_CX ��� */
    SS600_WA_MARK_TYPE_VSPM_X,      /* NVSM_X ��� */
    SS600_WA_MARK_TYPE_VSPM_AY,     /* SSPM_AY ��� */
    SS600_WA_MARK_TYPE_VSPM_BY,     /* SSPM_BY ��� */
    SS600_WA_MARK_TYPE_VSPM_CY,     /* VCSM_CY ��� */
    SS600_WA_MARK_TYPE_VSPM_Y,      /* VCSM_Y ��� */
    SS600_WA_MARK_TYPE_NVSM_AX,     /* NVCM_AX ��� */
    SS600_WA_MARK_TYPE_NVSM_BX,     /* NVCM_BX ��� */
    SS600_WA_MARK_TYPE_NVSM_CX,     /* NVSM_CX ��� */
    SS600_WA_MARK_TYPE_NVSM_X,      /* NVSM_X ��� */
    SS600_WA_MARK_TYPE_NVSM_AY,     /* NVSM_AY ��� */
    SS600_WA_MARK_TYPE_NVSM_BY,     /* NVSM_BY ��� */
    SS600_WA_MARK_TYPE_NVSM_CY,     /* NVSM_CY ��� */
    SS600_WA_MARK_TYPE_NVSM_Y,      /* NVSM_Y ��� */
    SS600_WA_MARK_TYPE_SSPM_X,      /* SSPM_X ��� */
    SS600_WA_MARK_TYPE_SSPM_Y,      /* SSPM_Y ��� */
    SS600_WA_MARK_TYPE_VCSM_MX,     /* VCSM_MX ��� */
    SS600_WA_MARK_TYPE_VCSM_GX,     /* VCSM_GX ��� */
    SS600_WA_MARK_TYPE_VCSM_FX,     /* VCSM_FX ��� */
    SS600_WA_MARK_TYPE_VCSM_X,      /* VCSM_X ��� */
    SS600_WA_MARK_TYPE_VCSM_MY,     /* VCSM_MY ��� */
    SS600_WA_MARK_TYPE_VCSM_GY,     /* VCSM_GY ��� */
    SS600_WA_MARK_TYPE_VCSM_FY,     /* VCSM_FY ��� */
    SS600_WA_MARK_TYPE_VCSM_Y,      /* VCSM_Y ��� */
    SS600_WA_MARK_TYPE_NVCM_MX,     /* NVCM_MX ��� */
    SS600_WA_MARK_TYPE_NVCM_GX,     /* NVCM_GX ��� */
    SS600_WA_MARK_TYPE_NVCM_FX,     /* NVCM_FX ��� */
    SS600_WA_MARK_TYPE_NVCM_X,      /* NVCM_X ��� */
    SS600_WA_MARK_TYPE_NVCM_MY,     /* NVCM_MY ��� */
    SS600_WA_MARK_TYPE_NVCM_GY,     /* NVCM_GY ��� */
    SS600_WA_MARK_TYPE_NVCM_FY,     /* NVCM_FY ��� */
    SS600_WA_MARK_TYPE_NVCM_Y,      /* NVCM_Y ��� */
    SS600_WA_MARK_TYPE_MAX
} SS600_WA_MARK_TYPE_ENUM;


/* Exposure Type */
typedef enum
{
    SS600_EXPO_TYPE_MIN = 0,
    SS600_EXPO_TYPE_SCAN,
    SS600_EXPO_TYPE_STEP,
    SS600_EXPO_TYPE_MAX
} SS600_EXPO_TYPE_ENUM;

/* Routing Option */
typedef enum
{
    SS600_ROUTING_OPTION_MIN = 0,
    SS600_ROUTING_OPTION_STANDARD,
    SS600_ROUTING_OPTION_OPTIMIZED,
    SS600_ROUTING_OPTION_MAX
} SS600_ROUTING_OPTION_ENUM;

/* Illumination Mode */
/*�μ�ES4A*/

/* Leveling Method */
typedef enum
{
    SS600_LEVEL_METHOD_MIN = 0,
    SS600_LEVEL_METHOD_DYNAMIC,
    SS600_LEVEL_METHOD_STATIC_LOCAL,
    SS600_LEVEL_METHOD_STATIC_GLOBAL,
    SS600_LEVEL_METHOD_DYNAMIC_LOP,
    SS600_LEVEL_METHOD_MAX
} SS600_LEVEL_METHOD_ENUM;


/* Leveling Scan Direction */
typedef enum
{
    SS600_LEVEL_SCANDIR_MIN = 0,
    SS600_LEVEL_SCANDIR_FREE,
    SS600_LEVEL_SCANDIR_DOWN,
    SS600_LEVEL_SCANDIR_UP,
    SS600_LEVEL_SCANDIR_MAX
} SS600_LEVEL_SCANDIR_ENUM;

/* Exposure Scan Direction */
typedef enum
{
    SS600_EXPO_SCANDIR_MIN = 0,
    SS600_EXPO_SCANDIR_DOWN,
    SS600_EXPO_SCANDIR_NONE,
    SS600_EXPO_SCANDIR_UP,
    SS600_EXPO_SCANDIR_MAX
} SS600_EXPO_SCANDIR_ENUM;

/* 8.0-8.8 Error Detection Switch */
typedef enum
{
    SS600_80_88_ERR_DETECT_SWITCH_MIN = 0,
    SS600_80_88_ERR_DETECT_SWITCH_MC_DEPENDENCY,
    SS600_80_88_ERR_DETECT_SWITCH_ON,
    SS600_80_88_ERR_DETECT_SWITCH_OFF,
    SS600_80_88_ERR_DETECT_SWITCH_MAX
} SS600_80_88_ERR_DETECT_SWITCH_ENUM;

/* SPM Fine Capture Range */
typedef enum
{
    SS600_SPM_FINE_CAP_RANGE_MIN = 0,
    SS600_SPM_FINE_CAP_RANGE_FULL,
    SS600_SPM_FINE_CAP_RANGE_MEDIUM,
    SS600_SPM_FINE_CAP_RANGE_SMALL,
    SS600_SPM_FINE_CAP_RANGE_MAX
} SS600_SPM_FINE_CAP_RANGE_ENUM;


#endif /* SS600_H_ */

