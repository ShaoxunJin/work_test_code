/*******************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号   : SS600
* 所属组件 :
* 模块名称 :
* 文件名称 : ss600.h
* 概要描述 : 与SSA产品相关的通用数据结构
*            考虑到数据定义的方便性,该文件中定义的部分数据类型或宏常数不遵守SMEE编码规范
* 历史记录 :
* 版本     日  期    作  者    内  容
*
* V1.0   2010.01.11  沈锦华    新建,草稿
* V1.1   2010.01.26  沈锦华    修订数据封装类型、增加向量定义部分内容.
* V1.2   2012.01.31  陈敏          增加系统宏定义.
* V2.0   2012.05.25  沈锦华    根据单台扫描系列光刻机平台化要求，修订。
******************************************************************************/
#ifndef SS600_H_
#define SS600_H_

#include "smee.h"

typedef enum
{
    SS600_MACHINE_TYPE_MIN = 0,
    SS600_A_600_20 = 1,  	/* SSA600/20 - 193 激光器*/
    SS600_B_600_10 = 2, 	/* SSB600/10 - i线汞灯*/
    SS600_A_600_30 = 3,  	/* SSA600/20 - 248 激光器 */
    SS600_A_600_04 = 4,  	/* 保留 */
    SS600_X_XXX_05 = 5,  	/* 保留 */
    SS600_X_XXX_06 = 6,  	/* 保留 */
    SS600_X_XXX_07 = 7,  	/* 保留 */
    SS600_X_XXX_08 = 8,  	/* 保留 */
    SS600_X_XXX_09 = 9,  	/* 保留 */
	SS600_X_XXX_10 = 10,  	/* 保留 */
	SS600_X_XXX_11 = 11,  	/* 保留 */
	SS600_X_XXX_12 = 12,  	/* 保留 */
	SS600_X_XXX_13 = 13,  	/* 保留 */
	SS600_X_XXX_14 = 14,  	/* 保留 */
	SS600_X_XXX_15 = 15,  	/* 保留 */
    SS600_MACHINE_TYPE_MAX
}SS600_MACHINE_TYPE_ENUM; /* 机器类型 */


/*每个图像的CDFEC区域个数*/
#define SS600_MAX_CDFEC_AREA_NR_PER_IMAGE  250

/*每个掩模版的最大的掩模对准标记个数*/
#define SS600_MAX_RA_MARK_NR_PER_RETICLE  20

/*每个图像的场最大的个数*/
#define SS600_MAX_FLD_NR_PER_IMG  500

/*每个层的最大图像个数*/
#define SS600_MAX_IMG_NR_PER_LOT  30

/*每个层的最大的掩模个数*/
#define SS600_MAX_RETICLE_NR_PER_LAYER  12

/*每个层的对准处方个数*/
#define SS600_MAX_ALIGN_RECIPE_NR_PER_LAYER  100

/*每个层的SUBRECIPE个数*/
#define SS600_MAX_SUBRECIPE_NR_PER_LAYER  20

/*每个处方的层最大个数*/
#define SS600_MAX_LAYER_NR_PER_RECIPE  32

/*每个处方的最大评估对准策略个数*/
#define SS600_MAX_EVAL_STRAT_NR_PER_RECIPE  5

/*每个对准策略的最大标记个数*/
#define SS600_MAX_MARK_NR_PER_STRATEGY  200

/*每个量产的最大硅片个数*/
#define SS600_MAX_WFR_NR_PER_LOT 999

/*每个量产的片盒个数*/
#define SS600_MAX_CARRIER_NR_PER_LOT 20

/*最大的片库个数*/
#define SS600_MAX_CARRIER_SLOT_NR 20


/*用户名长度*/
#define SS600_MAX_USER_ID_SIZE  64

/*掩模ID的存储空间长度*/
#define SS600_MAX_RETICLE_ID_SIZE 64

/*掩模POD ID的存储空间长度*/
#define SS600_MAX_RETICLE_POD_ID_SIZE 64

/*标记的标记ID的长度*/
#define SS600_MAX_MARK_ID_SIZE 64

/*标记的VARIANT ID的长度*/
#define SS600_MAX_MARK_VARIANT_ID_SIZE 32

/*图像ID的长度*/
#define SS600_MAX_IMAGE_ID_SIZE 64

/*硅片的GRID MODEL ID的长度*/
#define SS600_MAX_GRID_MODEL_ID_SIZE 64

/*对准策略ID的长度*/
#define SS600_MAX_STRATEGY_ID_SIZE 64

/*标记的方向属性个数*/
#define SS600_MAX_MARK_DIRECTIONS_SIZE 2

/*标记的颜色属性个数*/
#define SS600_MAX_MARK_COLORS_SIZE 2

/*标记的级数*/
#define SS600_MAX_MARK_ORDERS_SIZE 7

/*标记的周期*/
#define SS600_MAX_MARK_PERIODS_SIZE 5

/*层ID的长度*/
#define SS600_MAX_LAYER_ID_SIZE 64

/*不带路径的文件名长度*/
#define SS600_MAX_FILENAME_SIZE 64

/*带路径的文件名长度*/
#define SS600_MAX_PATH_FILENAME_SIZE 1024

/*通用小字符串长度*/
#define SS600_SMALL_STRING_SIZE 64

/*通用字符串长度*/
#define SS600_COMMON_STRING_SIZE 256

/*通用大容量字符串长度*/
#define SS600_LARGE_STRING_SIZE 1024


/*------------通用枚举定义-------------*/

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
    SS600_RETICLE_TYPE_PSM,    /* 相移掩模 */
    SS600_RETICLE_TYPE_BINARY, /* 二进制掩模 */
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
    SS600_WA_MARK_TYPE_XPA,         /* XPA 标记 */
    SS600_WA_MARK_TYPE_PM,          /* PM 标记 */
    SS600_WA_MARK_TYPE_XPA_X,       /* XPA-X 标记 */
    SS600_WA_MARK_TYPE_XPA_Y,       /* XPA-Y 标记 */
    SS600_WA_MARK_TYPE_SPM_X,       /* SPM-X 标记 */
    SS600_WA_MARK_TYPE_SPM_Y,       /* SPM-Y 标记 */
    SS600_WA_MARK_TYPE_OV,          /* OV 标记 */
    SS600_WA_MARK_TYPE_WGM,         /* WGM 标记 */
    SS600_WA_MARK_TYPE_SM_XG,       /* SM-XG 标记 */
    SS600_WA_MARK_TYPE_SM_XF,       /* SM-XF 标记 */
    SS600_WA_MARK_TYPE_CSM_XG,      /* CSM-XG 标记 */
    SS600_WA_MARK_TYPE_CSM_XF,      /* CSM-XF 标记 */
    SS600_WA_MARK_TYPE_SM_YG,       /* SM-YG 标记 */
    SS600_WA_MARK_TYPE_SM_YF,       /* SM-YF 标记 */
    SS600_WA_MARK_TYPE_CSM_YG,      /* CSM-YG 标记 */
    SS600_WA_MARK_TYPE_CSM_YF,      /* CSM-YF 标记 */
    SS600_WA_MARK_TYPE_NSM_XG,      /* NSM-XG 标记 */
    SS600_WA_MARK_TYPE_NSM_XF,      /* NSM-XF 标记 */
    SS600_WA_MARK_TYPE_NCSM_XG,     /* NCSM-XG 标记 */
    SS600_WA_MARK_TYPE_NCSM_XF,     /* NCSM-XF 标记 */
    SS600_WA_MARK_TYPE_NSM_YG,      /* NSM-YG 标记 */
    SS600_WA_MARK_TYPE_NSM_YF,      /* NSM-YF 标记 */
    SS600_WA_MARK_TYPE_NCSM_YG,     /* NCSM-YG 标记 */
    SS600_WA_MARK_TYPE_NCSM_YF,     /* NCSM-YF 标记 */
    SS600_WA_MARK_TYPE_CSM_GXRz,    /* CSM-GXRz 标记 */
    SS600_WA_MARK_TYPE_CSM_GYRz,    /* CSM-GYRz 标记 */
    SS600_WA_MARK_TYPE_CSM_FXRz,    /* CSM-FXRz 标记 */
    SS600_WA_MARK_TYPE_CSM_FYRz,    /* CSM-FYRz 标记 */
    SS600_WA_MARK_TYPE_VSPM_AX,     /* VSPM_AX 标记 */
    SS600_WA_MARK_TYPE_VSPM_BX,     /* VSPM_BX 标记 */
    SS600_WA_MARK_TYPE_VSPM_CX,     /* NVSM_CX 标记 */
    SS600_WA_MARK_TYPE_VSPM_X,      /* NVSM_X 标记 */
    SS600_WA_MARK_TYPE_VSPM_AY,     /* SSPM_AY 标记 */
    SS600_WA_MARK_TYPE_VSPM_BY,     /* SSPM_BY 标记 */
    SS600_WA_MARK_TYPE_VSPM_CY,     /* VCSM_CY 标记 */
    SS600_WA_MARK_TYPE_VSPM_Y,      /* VCSM_Y 标记 */
    SS600_WA_MARK_TYPE_NVSM_AX,     /* NVCM_AX 标记 */
    SS600_WA_MARK_TYPE_NVSM_BX,     /* NVCM_BX 标记 */
    SS600_WA_MARK_TYPE_NVSM_CX,     /* NVSM_CX 标记 */
    SS600_WA_MARK_TYPE_NVSM_X,      /* NVSM_X 标记 */
    SS600_WA_MARK_TYPE_NVSM_AY,     /* NVSM_AY 标记 */
    SS600_WA_MARK_TYPE_NVSM_BY,     /* NVSM_BY 标记 */
    SS600_WA_MARK_TYPE_NVSM_CY,     /* NVSM_CY 标记 */
    SS600_WA_MARK_TYPE_NVSM_Y,      /* NVSM_Y 标记 */
    SS600_WA_MARK_TYPE_SSPM_X,      /* SSPM_X 标记 */
    SS600_WA_MARK_TYPE_SSPM_Y,      /* SSPM_Y 标记 */
    SS600_WA_MARK_TYPE_VCSM_MX,     /* VCSM_MX 标记 */
    SS600_WA_MARK_TYPE_VCSM_GX,     /* VCSM_GX 标记 */
    SS600_WA_MARK_TYPE_VCSM_FX,     /* VCSM_FX 标记 */
    SS600_WA_MARK_TYPE_VCSM_X,      /* VCSM_X 标记 */
    SS600_WA_MARK_TYPE_VCSM_MY,     /* VCSM_MY 标记 */
    SS600_WA_MARK_TYPE_VCSM_GY,     /* VCSM_GY 标记 */
    SS600_WA_MARK_TYPE_VCSM_FY,     /* VCSM_FY 标记 */
    SS600_WA_MARK_TYPE_VCSM_Y,      /* VCSM_Y 标记 */
    SS600_WA_MARK_TYPE_NVCM_MX,     /* NVCM_MX 标记 */
    SS600_WA_MARK_TYPE_NVCM_GX,     /* NVCM_GX 标记 */
    SS600_WA_MARK_TYPE_NVCM_FX,     /* NVCM_FX 标记 */
    SS600_WA_MARK_TYPE_NVCM_X,      /* NVCM_X 标记 */
    SS600_WA_MARK_TYPE_NVCM_MY,     /* NVCM_MY 标记 */
    SS600_WA_MARK_TYPE_NVCM_GY,     /* NVCM_GY 标记 */
    SS600_WA_MARK_TYPE_NVCM_FY,     /* NVCM_FY 标记 */
    SS600_WA_MARK_TYPE_NVCM_Y,      /* NVCM_Y 标记 */
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
/*参见ES4A*/

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

