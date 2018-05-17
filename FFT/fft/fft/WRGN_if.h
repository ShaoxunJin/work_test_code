/**************************************************************************
* Copyright (C) 2008, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS B500/10
* 所属组件 : WRGN
* 模块名称 : WRGN_if
* 文件名称 : WRGN_if.h
* 概要描述 :
* 历史记录 :
* 版本    日期         作者        内容
  1.0       2010830    zhengjz     添加延迟函数
**************************************************************************/
#ifndef _WRGN_IF_H_
#define _WRGN_IF_H_

#include "WRGN_tc.h"
#include "math.h"
//#include <QTableWidget>
#include "EH4A_if.h"
#include "TR4A_if.h"
#include "GNMA.h"


/*延迟ms个毫秒*/
void WRGN_wait_mseconds(IN int ms);

/*设置表格中i行，j列的数据*/
/*
void WRGN_set_table_item(IN QTableWidget *qtable,
                         IN int row,
                         IN int column,
                         IN QString sText);
 */
 const char * WRenum2str(const WRGN_TRANSFER_TYPE_ENUM &t);

 int WRGN_cal_tf(IN SMEE_BOOL bSim,
									IN WRGN_TRANSFER_TYPE_STRUCT sType,
		            		    	IN double *pdTrace_data_crl_out,
								    IN double *pdTrace_data_crl_err,
								    IN double *pdTrace_data_crl_north2_out,
								    IN double *pdTrace_data_crl_after_signal,
									IN double dServoPeriod,
									IN int iTestNum,
									OUT WRGN_TF_STRUCT * psTF_out);

int WRGN_cal_openloop(IN SMEE_BOOL bSim,
					IN WRGN_BODE_STRUCT sTf_out,
					IN double dServoPeriod,
					IN double dStart_fr,
					IN double dStop_fr,
					OUT WRGN_OPEN_LOOP_RESULT_STRUCT * psResult);

int WRGN_bode(IN WRGN_SPECTRUM_STRUCT sSpectrum,        //功率谱
                          OUT WRGN_BODE_STRUCT *psTF_Bode);        //传函（伯德图）

int WRGN_spectrum(IN int iIndex,                                //第几次计算功率谱（要和前面的 iIndex-1 次做平均）
                              IN double dServoPeriod,                    //伺服周期
                              IN double *pdDataIn,                        //输入点追到的数据
                              IN double *pdDataOut,                        //输出点追到的数据
                              INOUT WRGN_SPECTRUM_STRUCT *psSpectrum,		//功率谱
                              OUT double *pdFreq);

int WRGN_measured_mass(IN double dServoPeriod,
								  IN double dFrequence_start,
								  IN double dFrequence_stop,
					              IN WRGN_BODE_STRUCT sBode,
					              OUT double *pdMeasured_mass,
					              OUT double *pdCoherance);

int WRGN_norm_random_error(IN double dCoherence,
						               IN int iTest_Number,
						               OUT double *pdNRE);
int WRGN_cal_stable_err(IN double dPos_err [ 2048 ],
										IN int iUpdate_rate,
										IN double dServoPeriod,
										IN double dSettling_time,
										OUT double * pdMean,
										OUT double *pd3Sigma);
int WRGN_cal_setting_time(IN double dPos_err[2048],
										IN double dServoPeriod,
										IN double dError_window,
										IN int iUpdate_rate,
										OUT double *pdSettling_time);
//int WRGN_high_response(IN SMEE_BOOL bSim,
//					             IN WRGN_BODE_STRUCT sTFTotal,//开环总传函
//					             IN double dStartFreq,	//频段的起始频率
//					             IN double dEndFreq,		//频段的截止频率
//					             IN double dServoPeriod,	//伺服周期
//					             OUT WRGN_HIGH_STRUCT *psHigh);
#endif // _WRGN_H_
