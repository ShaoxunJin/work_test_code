/********************************************************************
* Copyright (C) 2005, �Ϻ�΢����װ�����޹�˾ϵͳ�뼯�ɹ��̲�
* All rights reserved.
* ��Ʒ��	:	SS A600/10
* �������	:	GN
* ģ������	: 	General functions: Mathematical functions
* �ļ�����	:  	GNMA.h
*
* ����	 	:
* ������� :
* ��ǰ�汾 : 	1.0
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
/********************************�����뼰�궨��*******************************************/
#define GNMA_BASE_ERR 		0X474E0000

#define GNMA_SYSTEM_ERR		(GNMA_BASE_ERR+0)      //ϵͳ����
#define GNMA_PARAM_ERR 		(GNMA_BASE_ERR+1)       //����������߳���
#define GNMA_POINTER_ERR 		(GNMA_BASE_ERR+2)    //��ָ��
#define GNMA_SEARCH_FAIL 		(GNMA_BASE_ERR+3)  //Ѱ��ʧ��

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
	INVERT//����Ҷ���任
}GNMA_fourier_direction;

/*********************************�����ӿڼ���������*********************************************/
int GNMA_freq_size(IN int iNbr_points,/*�������ݵĸ���*/
							  IN int iNbr_frames,/*���ݼ����֡����ͨ��Ϊ1,������߼����ٶȣ�����Ƶ�ʷֱ���*/
							  OUT int *piNbr_freq_points);/*Ƶ�ʵ�ĸ���*/

int GNMA_spectrum(IN int iNbr_points,/*�������ݼ���ĸ���*/
							 IN int iNbr_frames,/*���ݼ����֡����ͨ��Ϊ1��������߼����ٶȣ�����Ƶ�ʷֱ���*/
							 IN int iNbr_freq_points, /*Ƶ�ʵ�ĸ�����һ��Ϊ2���ݴη��ĸ�����1*/
							 IN double dSample_period,/*�������ڣ����ǹ�˾ĿǰΪ400΢���������*/
							 IN double *pdX,/*���������1*/
							 IN double *pdY, /*���������2*/
							 OUT double *pdFreqs,/*�����Ƶ��*/
							 OUT double *pdPxx,/*���������1����*/
							 OUT double *pdPyy,/*���������2����*/
							 OUT GNMA_complex_type *psPxy);/*����Ļ���*/

int GNMA_transfer(IN int iNbr_freq_points,/*Ƶ�ʵ����*/
							 IN double *pdPxx,/*����*/
							 IN double *pdPyy, /*����*/
							 IN GNMA_complex_type *psPxy,/*����*/
							 OUT double *pdMagnitude, /*��ֵ*/
							 OUT double *pdPhase,/*��λֵ*/
							 OUT double *pdCoherence);/*��ض�*/
int GNMA_mov_avg_and_std_dev(IN double *input,/*��������*/
												IN int input_size,/*�������ݵĸ���*/
												IN int filter_window, /*�������Ĵ�С*/
												OUT double *mov_avg,/*������ֵMA*/
												OUT double *mov_std_dev);/*��������ֵMSD*/
int GNMA_peak_value(IN double *pdData, /*��������ݵ��׵�ַ,����Ϊdouble����,*/
								   IN int iNumber, /*���ݵĸ���*/
								   IN int iSizeOfItem,/*sizeof�����ݵ����ͣ�������Ϊsizeof��double����Ҳ����Ϊdouble�����Ľṹ��*/
								   OUT double *pDPeak);/*���ݵķ�ֵ*/
//��source���ҳ�����ֵ����������*peak��
int  GNMA_max_value(IN double *pdData, /*��������ݵ��׵�ַ,����Ϊdouble����,*/
								   IN int iNumber, /*�������ݵĸ���*/
								   IN int iSizeOfItem,/*sizeof�����ݵ����ͣ�������Ϊsizeof��double����Ҳ����Ϊdouble�����Ľṹ��*/
								   OUT double *pdMax);/*���ݵ����ֵ*/
//���ܣ���pdData[]���ҳ����ķ���*pdMax��

int  GNMA_min_value(IN double *pdData,/*��������ݵ��׵�ַ,����Ϊdouble����,*/
								   IN int iNumber,/*�������ݵĸ���*/
								   IN int iSizeOfItem,/*sizeof�����ݵ����ͣ�������Ϊsizeof��double����Ҳ����Ϊdouble�����Ľṹ��*/
								   OUT double *pdMin);/*���ݵ���Сֵ*/
//���ܣ���pdData[]���ҳ���С�ķ���*pdMin��

int GNMA_statistics(IN double *pdData,/*��������ݵ��׵�ַ,����Ϊdouble����,*/
								IN int iNumber, /*�������ݵĸ���*/
								IN int iSizeOfItem, /*sizeof�����ݵ����ͣ�������Ϊsizeof��double����Ҳ����Ϊdouble�����Ľṹ��*/
								OUT double *pdMean,/*��ֵ*/
								OUT double *pdStdDev,/*��׼��*/
								OUT double *pdPeak, /*��ֵ*/
								OUT double *pdMin,/*��Сֵ*/
								OUT double *pdMax,/*���ֵ*/
								OUT double *pdMean3Sigma);/*mean+3sigma*/
//���ܣ����pdData[]��ƽ��ֵ*pdMean����׼��*pdStdDev��������ֵ*pdPeak��
//					  ��Сֵ*pdMin�����ֵ*pdMax �͡�ƽ��ֵ��3�ơ�*pdMean3Sigma��
int	GNMA_average_value(IN double *pdData, /*��������ݵ��׵�ַ,����Ϊdouble����,*/
									  IN int iNumber, /*���ݵĸ���*/
									  IN int iSizeOfItem, /*sizeof�����ݵ����ͣ�������Ϊsizeof��double����Ҳ����Ϊdouble�����Ľṹ��*/
									  OUT double *pdMean,/*��ֵ*/
									  OUT double *pdStdDev);/*��׼��*/
//���ܣ����pdData[]��ƽ��ֵ*pdMean�ͱ�׼��*pdStdDev��

int GNMA_calc_bandwidth(IN int sim_mode, /*����ģʽ*/
							  			IN double *freq_point/*Ƶ������*/,
										IN double *magnitude/*��ֵ����*/,
										IN int nbr_fre_trace,/*Ƶ�ʸ���*/
										IN double sample_period,/*�������ڣ����ǹ�˾һ��Ϊ400΢���������*/
										IN double start_fr/*��ʼƵ��*/,
										 IN double stop_fr/*ֹͣƵ��*/,
										 OUT int *if_found/*�Ƿ��ҵ������û�ҵ�����0*/,
										 OUT double *bw/*��������Ĵ���*/);
//����:���������������Ϊ��Ƶֵ�״δ�Խ��ֱ����Ӧ��Ƶ��ֵ��

int GNMA_calc_phase_margin(IN int sim_mode, /*����ģʽ*/
								  			IN double *freq_point/*Ƶ������*/,
											IN double *magnitude/*��ֵ����*/,
											IN double *phase/*��λ����*/,
											IN int nbr_fre_trace,/*Ƶ�ʸ���*/
											IN double sample_period,/*�������ڣ����ǹ�˾һ��Ϊ400΢���������*/
											IN double start_fr/*��ʼƵ��*/,
											IN double stop_fr/*ֹͣƵ��*/,
											OUT int *if_found/*�Ƿ��ҵ�,0��ʾû���ҵ�*/,
											OUT double *ph_mar/*��λԣ��*/,
											OUT double *ph_fre/*��λԣ�ȶ�Ӧ��Ƶ�ʵ�ֵ*/);

//����:�����λԣ�ȡ�

int  GNMA_calc_amplitude_margin(IN int sim_mode,/*����ģʽ*/
												   IN double *freq_point/*Ƶ������*/,
												   IN double *magnitude/*��ֵ����*/,
												   IN double *phase,/*��λ����*/
												   IN int nbr_fre_trace, /*Ƶ�ʵ����*/
												   IN double sample_period,/*�������ڣ����ǹ�˾һ��Ϊ400΢���������*/
												   IN double bw/*����Ƶ��,��Ϊ��ʼƵ��*/,
												   IN double amp_stop_fr/*ֹͣƵ��*/,
												   OUT int*if_found/*�Ƿ��ҵ���0��ʾû���ҵ�*/,
												   OUT double *ampl_mar/*��ֵԣ��*/,
												   OUT double *ampl_freq/*��Ӧ��Ƶ��ֵ*/ );
//����:�����ֵԣ��


#ifdef __cplusplus
}
#endif


#endif						// end of GNMA_H

