/**************************************************************************
* Copyright (C) 2008, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS B500/10
* ������� : WRGN
* ģ������ : WRGN_if
* �ļ����� : WRGN_if.h
* ��Ҫ���� :
* ��ʷ��¼ :
* �汾    ����         ����        ����
  1.0       2010830    zhengjz     ����ӳٺ���
**************************************************************************/
#ifndef _WRGN_IF_H_
#define _WRGN_IF_H_

#include "WRGN_tc.h"
#include "math.h"
//#include <QTableWidget>
#include "EH4A_if.h"
#include "TR4A_if.h"
#include "GNMA.h"


/*�ӳ�ms������*/
void WRGN_wait_mseconds(IN int ms);

/*���ñ����i�У�j�е�����*/
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

int WRGN_bode(IN WRGN_SPECTRUM_STRUCT sSpectrum,        //������
                          OUT WRGN_BODE_STRUCT *psTF_Bode);        //����������ͼ��

int WRGN_spectrum(IN int iIndex,                                //�ڼ��μ��㹦���ף�Ҫ��ǰ��� iIndex-1 ����ƽ����
                              IN double dServoPeriod,                    //�ŷ�����
                              IN double *pdDataIn,                        //�����׷��������
                              IN double *pdDataOut,                        //�����׷��������
                              INOUT WRGN_SPECTRUM_STRUCT *psSpectrum,		//������
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
//					             IN WRGN_BODE_STRUCT sTFTotal,//�����ܴ���
//					             IN double dStartFreq,	//Ƶ�ε���ʼƵ��
//					             IN double dEndFreq,		//Ƶ�εĽ�ֹƵ��
//					             IN double dServoPeriod,	//�ŷ�����
//					             OUT WRGN_HIGH_STRUCT *psHigh);
#endif // _WRGN_H_
