/*******************************************************************************
* Copyright (C) 2005, �Ϻ�΢����װ�����޹�˾
* All rights reserved.
* ��Ʒ�� : SS B500/10M
* ������� : RH,WH
* ģ������ : WRGN
* �ļ����� : WRGN_tc.h
* ��Ҫ���� :��ģ������WH,RH������ͷ�ļ�
* ��ʷ��¼ :
* �汾   ����    ����   ����
* 1.0    2011-2-16 zhengjz ����    ��     ��
******************************************************************************/
#ifndef _WRGN_TC_H_
#define _WRGN_TC_H_

#include "ss600.h"
#include "smee.h"
#include <stdio.h>

//#include <poll.h>
//#include <QTableWidget>

//#include "HWGN4T_if.h"
//#include "math.h"
//#include "HWVPSP.h"

//#include "EH4A_if.h"
//#include "TR4A_if.h"
//#include "MF4A_if.h"
#include "GNMA.h"

#define IN
#define OUT
#define IO

/*ERROR CODE*/
#define WRGN_BASE_ERROR 0x57520000

/*���ܺ�������*/
#define WRGN_CAL_STABLE_ERROR (WRGN_BASE_ERROR +0x10)
#define WRGN_NORM_RANDOM_ERROR_FAILED (WRGN_BASE_ERROR +0x11)
#define WRGN_MEASURED_MASS_ERROR (WRGN_BASE_ERROR +0x12)
#define WRGN_BODE_ERROR (WRGN_BASE_ERROR +0x13)
#define WRGN_SPECTRUM_ERROR (WRGN_BASE_ERROR +0x14)
#define WRGN_CAL_OPENLOOP_ERROR (WRGN_BASE_ERROR +0x15)
//#define WRGN_HR_CAL_TF_ERROR (WRGN_BASE_ERROR +0x16)
#define WRGN_HW_CAL_TF_ERROR (WRGN_BASE_ERROR +0x17)
//#define WRGN_HR_TRACE_TF_ERROR  (WRGN_BASE_ERROR +0x18)
#define WRGN_HW_TRACE_TF_ERROR (WRGN_BASE_ERROR +0x19)
#define WRGN_CAL_SETTLING_TIME_ERROR (WRGN_BASE_ERROR +0x1A)
/**/
#define WRGN_PARAM_ERROR	(WRGN_BASE_ERROR +0x40)	//����NRE�������������
#define WRGN_MEASURED_MASS_IS_ZERO_ERROR (WRGN_BASE_ERROR +0x41)	//��������ʱ��ĸΪ0��
#define WRGN_BANDWIDTH_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x42)	//����δ�ҵ�����
#define WRGN_AMPLTITUDE_MARGIN_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x43)	//��ֵԣ��δ�ҵ�
#define WRGN_PHASE_MARGIN_NOT_FOUND_ERROR (WRGN_BASE_ERROR +0x44)	//��λԣ��δ�ҵ�
#define WRGN_NRE_LESS_THAN_ZERO	(WRGN_BASE_ERROR +0x45)	//����õ���NREС��0
#define WRGN_STABLE_TIME_TOO_LONG_ERROR	(WRGN_BASE_ERROR +0x46)	//����õ���NREС��0
#define WRGN_REACH_SET_ERR_WINDOW_FAILED	(WRGN_BASE_ERROR +0x47)


#define WRGN_TRACE_DATA_NUMBER 2048
#define WRGN_MAX_TRANSFER_TYPE 6
#define WRGN_PI 3.14159265

typedef enum
{
    WRGN_MECHANICS,          //���Ի�е����
    WRGN_CONTROLLER,         //���Կ��ƴ���
    WRGN_OPENTOTAL,          //���Կ����ܴ���
    WRGN_CLOSEDLOOP,         //���Աջ�����
    WRGN_SENSITIVITY,        // �������жȴ���
    WRGN_PROCESSSENSITIVITY //���Թ������жȴ���
}WRGN_TRANSFER_TYPE_ENUM;

typedef struct
{
    double freq[WRGN_TRACE_DATA_NUMBER];
    double mag[WRGN_TRACE_DATA_NUMBER];
    double phase[WRGN_TRACE_DATA_NUMBER];
    double cohere[WRGN_TRACE_DATA_NUMBER];
}WRGN_BODE_STRUCT;

typedef struct
{
    double Pxx[WRGN_TRACE_DATA_NUMBER];
    double Pyy[WRGN_TRACE_DATA_NUMBER];
    GNMA_complex_type Pxy[WRGN_TRACE_DATA_NUMBER];
}WRGN_SPECTRUM_STRUCT;

typedef struct
{
  double dBandwidth;   //��������
  double dMagnt_margin;  //������ֵԣ��
  double dPhase_margin;   //������λԣ��
}WRGN_OPEN_LOOP_RESULT_STRUCT;

typedef struct{

	SMEE_BOOL bMechanical;   //���Ի�е����
	SMEE_BOOL bController;     //���Կ��ƴ���
	SMEE_BOOL bOpenTotal;    //���Կ����ܴ���
	SMEE_BOOL bClosedLoop;   //���Աջ�����
	SMEE_BOOL bSensity;      // �������жȴ���
	SMEE_BOOL bProcessSensity; //���Թ������жȴ���

}WRGN_TRANSFER_TYPE_STRUCT;

typedef struct{

	WRGN_BODE_STRUCT sMechanical;    //��е������Bodeͼ���
	WRGN_BODE_STRUCT sControl;      //������������Bodeͼ���
	WRGN_BODE_STRUCT sOpenTotal;     //�����ܴ�����Bodeͼ���
	WRGN_BODE_STRUCT sClosedLoop;    //�ջ�������Bodeͼ���
	WRGN_BODE_STRUCT sSensity;        //���жȴ���������Bodeͼ���
	WRGN_BODE_STRUCT sProcessSensity;//�������жȴ�����Bodeͼ���

} WRGN_TF_STRUCT;
//typedef struct
//{
//	SMEE_BOOL b0dbTooMany;	//SMEE_TRUE��ʾ0�ֱ���̫���ˣ���������5��
//	int i0dbNbr;			//0�ֱ���ĸ���
//	double d0db[5];			//0�ֱ����λ�ã��ӵ�Ƶ����Ƶ���У���i0dbNbr��
//	SMEE_BOOL b180TooMany;	//SMEE_TRUE��ʾ��180�ȵ�̫���ˣ���������5��
//	int i180Nbr;			//��180�ȵ�ĸ���
//	double d180[5];			//��180�ȵ��λ�ã��ӵ�Ƶ����Ƶ���У���i180Nbr��
//}WRGN_HIGH_STRUCT;
#endif


