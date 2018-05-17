/********************************************************************
* Copyright (C) 2005, 上海微电子装备有限公司系统与集成工程部
* All rights reserved.
* 产品号	:	SS A600/10
* 所属组件	:	GN
* 模块名称	: 	General functions: Mathematical functions
* 文件名称	:  	GNMA.h
*
* 作者	 	:
* 完成日期 :
* 当前版本 : 	1.0
********************************************************************/
#ifndef GNMA_H
#define GNMA_H

#include "smee.h"
#ifdef __cplusplus
extern "C"
{
#endif
#define IO
#define IN
#define OUT
/********************************错误码及宏定义*******************************************/
#define GNMA_BASE_ERR 		0X474E0000

#define GNMA_SYSTEM_ERR		(GNMA_BASE_ERR+0)      //系统错误
#define GNMA_PARAM_ERR 		(GNMA_BASE_ERR+1)       //参数错误或者超限
#define GNMA_POINTER_ERR 		(GNMA_BASE_ERR+2)    //空指针
#define GNMA_SEARCH_FAIL 		(GNMA_BASE_ERR+3)  //寻找失败

#define GNMA_PI 3.141592653589793

/*******************************************************************************/
typedef struct
{
	double Re;
	double Im;
}GNMA_complex_type;

typedef enum
{
	NORMAL = 0,
	INVERT//付利叶反变换
}GNMA_fourier_direction;

/*********************************函数接口及参数定义*********************************************/
int GNMA_freq_size(IN int iNbr_points,/*输入数据的个数*/
							  IN int iNbr_frames,/*数据计算的帧数，通常为1,大则提高计算速度，降低频率分辨率*/
							  OUT int *piNbr_freq_points);/*频率点的个数*/

int GNMA_spectrum(IN int iNbr_points,/*输入数据计算的个数*/
							 IN int iNbr_frames,/*数据计算的帧数，通常为1，大则提高计算速度，降低频率分辨率*/
							 IN int iNbr_freq_points, /*频率点的个数，一般为2的幂次方的个数加1*/
							 IN double dSample_period,/*采样周期，我们公司目前为400微秒的整数倍*/
							 IN double *pdX,/*输入的数据1*/
							 IN double *pdY, /*输入的数据2*/
							 OUT double *pdFreqs,/*输出的频率*/
							 OUT double *pdPxx,/*输出的数据1自谱*/
							 OUT double *pdPyy,/*输出的数据2自谱*/
							 OUT GNMA_complex_type *psPxy);/*输出的互谱*/

int GNMA_transfer(IN int iNbr_freq_points,/*频率点个数*/
							 IN double *pdPxx,/*自谱*/
							 IN double *pdPyy, /*自谱*/
							 IN GNMA_complex_type *psPxy,/*互谱*/
							 OUT double *pdMagnitude, /*幅值*/
							 OUT double *pdPhase,/*相位值*/
							 OUT double *pdCoherence);/*相关度*/
int GNMA_mov_avg_and_std_dev(IN double *input,/*输入数据*/
												IN int input_size,/*输入数据的个数*/
												IN int filter_window, /*滑动窗的大小*/
												OUT double *mov_avg,/*滑动均值MA*/
												OUT double *mov_std_dev);/*滑动均方值MSD*/
int GNMA_peak_value(IN double *pdData, /*输入的数据的首地址,必须为double类型,*/
								   IN int iNumber, /*数据的个数*/
								   IN int iSizeOfItem,/*sizeof（数据的类型），可以为sizeof（double），也可以为double倍数的结构体*/
								   OUT double *pDPeak);/*数据的峰值*/
//从source中找出绝对值最大的数放入*peak。
int  GNMA_max_value(IN double *pdData, /*输入的数据的首地址,必须为double类型,*/
								   IN int iNumber, /*输入数据的个数*/
								   IN int iSizeOfItem,/*sizeof（数据的类型），可以为sizeof（double），也可以为double倍数的结构体*/
								   OUT double *pdMax);/*数据的最大值*/
//功能：从pdData[]中找出最大的放入*pdMax。

int  GNMA_min_value(IN double *pdData,/*输入的数据的首地址,必须为double类型,*/
								   IN int iNumber,/*输入数据的个数*/
								   IN int iSizeOfItem,/*sizeof（数据的类型），可以为sizeof（double），也可以为double倍数的结构体*/
								   OUT double *pdMin);/*数据的最小值*/
//功能：从pdData[]中找出最小的放入*pdMin。

int GNMA_statistics(IN double *pdData,/*输入的数据的首地址,必须为double类型,*/
								IN int iNumber, /*输入数据的个数*/
								IN int iSizeOfItem, /*sizeof（数据的类型），可以为sizeof（double），也可以为double倍数的结构体*/
								OUT double *pdMean,/*均值*/
								OUT double *pdStdDev,/*标准差*/
								OUT double *pdPeak, /*峰值*/
								OUT double *pdMin,/*最小值*/
								OUT double *pdMax,/*最大值*/
								OUT double *pdMean3Sigma);/*mean+3sigma*/
//功能：求出pdData[]的平均值*pdMean、标准差*pdStdDev、最大绝对值*pdPeak、
//					  最小值*pdMin、最大值*pdMax 和“平均值加3∑”*pdMean3Sigma。
int	GNMA_average_value(IN double *pdData, /*输入的数据的首地址,必须为double类型,*/
									  IN int iNumber, /*数据的个数*/
									  IN int iSizeOfItem, /*sizeof（数据的类型），可以为sizeof（double），也可以为double倍数的结构体*/
									  OUT double *pdMean,/*均值*/
									  OUT double *pdStdDev);/*标准差*/
//功能：求出pdData[]的平均值*pdMean和标准差*pdStdDev。

int GNMA_calc_bandwidth(IN int sim_mode, /*仿真模式*/
							  			IN double *freq_point/*频率数组*/,
										IN double *magnitude/*幅值数组*/,
										IN int nbr_fre_trace,/*频率个数*/
										IN double sample_period,/*采用周期，我们公司一般为400微秒的整数倍*/
										IN double start_fr/*开始频率*/,
										 IN double stop_fr/*停止频率*/,
										 OUT int *if_found/*是否找到，如果没找到返回0*/,
										 OUT double *bw/*计算出来的带宽*/);
//功能:求出带宽，带宽，定义为幅频值首次穿越零分贝点对应的频率值。

int GNMA_calc_phase_margin(IN int sim_mode, /*仿真模式*/
								  			IN double *freq_point/*频率数组*/,
											IN double *magnitude/*幅值数组*/,
											IN double *phase/*相位数组*/,
											IN int nbr_fre_trace,/*频率个数*/
											IN double sample_period,/*采样周期，我们公司一般为400微秒的整数倍*/
											IN double start_fr/*开始频率*/,
											IN double stop_fr/*停止频率*/,
											OUT int *if_found/*是否找到,0表示没有找到*/,
											OUT double *ph_mar/*相位裕度*/,
											OUT double *ph_fre/*相位裕度对应的频率点值*/);

//功能:求出相位裕度。

int  GNMA_calc_amplitude_margin(IN int sim_mode,/*仿真模式*/
												   IN double *freq_point/*频率数组*/,
												   IN double *magnitude/*幅值数组*/,
												   IN double *phase,/*相位数组*/
												   IN int nbr_fre_trace, /*频率点个数*/
												   IN double sample_period,/*采样周期，我们公司一般为400微秒的整数倍*/
												   IN double bw/*带宽频率,做为启始频率*/,
												   IN double amp_stop_fr/*停止频率*/,
												   OUT int*if_found/*是否找到，0表示没有找到*/,
												   OUT double *ampl_mar/*幅值裕度*/,
												   OUT double *ampl_freq/*对应的频率值*/ );
//功能:求出幅值裕度


#ifdef __cplusplus
}
#endif


#endif						// end of GNMA_H

