/**********************************
* Copyright (C) 2009,  �Ϻ�΢����װ����
* All rights reserved.
*  ��Ʒ��  : SS A600/102
*  ������� :  GN
*  ģ������ :  GNMA
*  �ļ����� :  GNMA.cpp
*  ��Ҫ���� :  ͨ�����ݿ�
*  ��ʷ��¼ :
*  �汾    ����     ����    ����
	1.1		20090625  zhengjz
* ***********************************************************/
#include "stdafx.h"
#include "smee_type.h"
#include "GNMA.h"
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <iostream>
using namespace std;
/*======================================================
* Include:
* Function:
* Parameters:
*   -input:  	double a
			double b
*   -input/output:
* -output:
* Returns:   TRUE/FALSE
* Description:   �Ƚ�����double�͵����Ƿ����
======================================================*/
static SMEE_BOOL gnma_dbl_equal(double a, double b)
{
	if( abs(a - b) < 4.450147717014403e-308) 
	 {
		  return SMEE_TRUE;
	 }
	 else
	 {
		  return SMEE_FALSE;
	 }
}

/*======================================================
* Include:
* Function: bit_invert
* Parameters:
*   -input:  	int iNbr_fft
*   -input/output:  GNMA_complex_type psInput[]
* -output:
* Returns:   0/Error
* Description:   ��fft�㷨�����廪�桶�����źŴ���̡̳��ڶ���(��������)��д(�޸������Ĳ��ִ���)
 	���׸��㷨ʵ��λ����
ժ���廪�桶�����źŴ���̡̳��ڶ���(��������)��185ҳ--ʵ�ַ����λ�ӷ�����λ���������������һ����������һ���������λ��1���ɸ�λ���λ��λ���õ��ģ�
ʵ�ַ�����x��i����ʾ���ԭ��Ȼ˳���������ݵ��ڴ浥Ԫ��x��j����ʾ��ŵ�λ�������ڴ浥Ԫ��i��j���Ǵ�0��ʼ��
����֪ĳ����λ����j��Ҫ����һ����λ��������Ӧ���ж�j�����λ�Ƿ�Ϊ0���������k=N/2�Ƚϣ���ΪN/2�Ķ����Ʊ�ʾ�϶��ǡ�10000...����
���k>j��˵��j�����λΪ0��ֻҪ�Ѹ�λ��Ϊ1��j����N/2���ɣ����͵õ�����һ����λ������x��i+1����x��j����������
���k<=j��˵��j�����λΪ1��ֻҪ�Ѹ�λ��Ϊ0��j-N/2���ɣ���
Ȼ�����жϴθ�λ����N/4�Ƚϣ������θ�λΪ0���⽫��λ��Ϊ1��j+N/4���ɣ�������λ���䣬��õ���һ����λ���������θ�λ��1���⽫��λ��Ϊ0��j-N/4���ɣ���Ȼ�����ж�����һλ��
�������k=N/8�Ƚϣ�.......���ν��У��ܻ�����ĳλΪ0�����ǰ�0��Ϊ1���õ���һ����λ����������µĵ�λ����j�Ժ󣬽���i<jʱ���б�ַ������
ע��x��0����x��N-1���ǲ���Ҫ���б�ַ�����ģ���Ϊ���ԭ��Ȼ˳����һ���ġ�
======================================================*/
static int bit_invert(GNMA_complex_type psInput[], int iNbr_fft)
{
	int iErrorCode = 0;
//	int iErrorLink[2] = {0, 0};
//	char *psErrorText = NULL;

	GNMA_complex_type sSwap = {0.0, 0.0};

	int NV2 = iNbr_fft / 2;//����j�������ֵ��Ƚ�
	//int NM1 = iNbr_fft - 1;//�ɱ�ַ�����ݸ���,��0���͵�iNbr_fft-1�����õ�λ��ַ
	int i = 0;//ԭ��
	int j = 0;//��Ӧ�ĵ���
	int k = 0;//��ʾĳλΪ1
	//NM1 = NM1;//��ʱ���ã�Ϊ���⾯���д

	if(NULL == psInput)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: bit_invert error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "psInput = %d", psInput);
#endif /* NEVER */
	}
	if(0 == iErrorCode && iNbr_fft <= 0)
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: bit_invert error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "iNbr_fft = %d", iNbr_fft);
#endif /* NEVER */
	}

	for(i = 0; i < (iNbr_fft - 1) && 0 == iErrorCode; i++)//iNbr_fft - 1
	{
		if(i < j)
		{//ֻ��ԭ��С�ڵ�λ����ʱ�Ž���
			//printf("%d-->%d\n",i,j);
			sSwap = psInput[j];
			psInput[j] = psInput[i];
			psInput[i] = sSwap;

		}
		//����������һ������
		k = NV2;//��һ��ΪN/2 ��ʾ���λΪ1
		while(j >= k)
		{//����λ����jĳλΪ1�������λ��λ
			j -= k;
			k /= 2;
		}
		j += k;
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/*======================================================
* Include:
* Function: gnma_fft
* Parameters:
*   -input:  	int iNbr_fft,  �������ݵĸ�����Ϊ2���ݴη�
			GNMA_complex_type *psInput_str, ��������
			GNMA_fourier_direction eFourier_dir  FFT����iFFT
*   -input/output:  GNMA_complex_type psInput[]
* -output:  GNMA_complex_type *psOut_str,  FFT���
* Returns:   0/Error
* Description: fft DIT ��2�㷨
ժ���廪�桶�����źŴ���̡̳��ڶ���(��������)��185ҳ---L�����Ƽ��㣨2^L =N��
�ص㣺
1��ÿ����N/2�����νᣬ��һ����N/2�����νᶼ��ͬһ�ֵ������㣬Ҳ����˵����ϵ������ͬ��ΪW��0��N��=exp��-2pi*0/N����
   �ڶ�����N/2�����νṲ�����ֵ������㣬һ��ϵ��ΪW��0��N����һ��ϵ��ΪW��2��N����ÿ�ָ���N/4�����νᡣ�����ɿ�����
   ��L����N/2�����νṲ��2^(L-1)=N/2�ֵ������㣬����N/2����ͬ������ϵ�����ֱ�ΪW(0,N),W(1,N),������W(N/2-1��N),Ҳ����˵��
   ��M����2^(M-1)�ֵ������㣨M= 1��2��������L����������W��k��2^M����k=0��1��������2^(M-1)-1��
2�������һ��ÿ��ǰ�ƽ�һ������ϵ��ȡ��ϵ����ż����������һ�롣
3�����ν������ڵ�ļ��Ϊ2^(M-1),MΪ���ڵļ���,Ҳ����ÿ��ǰ�ƽ�һ��,���ͱ��ԭ����1/2��
�������̷�����ѭ�����ƣ�
����һ��ѭ������L��2^L=N������˳�����㣬�ڲ������ѭ������ͬһ����M��ͬ�������ν�����㣬��������һ��ѭ������ͬһ�֣���W��r��N����r��ͬ�����ν�����㣬
���м�һ��ѭ�����Ʋ�ͬ�֣���W��r��N����r��ͬ�����ν�����㡣I��IP��һ�����ν�������ڵ㡣
===============================================================*/
static int gnma_fft(int iNbr_fft,
				 GNMA_complex_type *psInput_str,
				 GNMA_complex_type *psOut_str,
				 GNMA_fourier_direction eFourier_dir)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int m = 0;//m = 1,2,��,L, L = Log(2,N),���������еļ�����ѭ������
	int j = 0;
	int i = 0;//���ν��еĵ�һ���ڵ�
	int ip = 0;//���ν��еĵڶ����ڵ�
	int n = iNbr_fft;
	int L = 1;//����
	int nbr_butfly = 1;//���ν�����͸�����ͬһ���ν�����֮��ļ��
	int dist_betwn_butfly = 2;//���ν�֮��ľ���
	double a = 0.0;
	double b = 0.0;
	double pi = 4.0*atan(1.0);
	GNMA_complex_type W = {1.0, 0.0};//��������
	GNMA_complex_type Wl = {0.0, 0.0};//������������
	GNMA_complex_type sTemp = {0.0, 0.0};

	//�õ��Ʒ�������fft
	if(NULL == psInput_str || NULL == psOut_str)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: gnma_fft error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "psInput_str = %d, psOut_str = %d",
		psInput_str, psOut_str);
#endif /* NEVER */
	}
	if(iNbr_fft <= 0 && 0 == iErrorCode)
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: gnma_fft error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "iNbr_fft = %d",
		iNbr_fft);
#endif /* NEVER */
	}
	if(0 == iErrorCode && !(INVERT == eFourier_dir || NORMAL == eFourier_dir))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: gnma_fft error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "eFourier_dir = %d",
		eFourier_dir);
#endif /* NEVER */
	}

	//����Ҷ���任��������ȡ����ټ���fft�����Խ��ȡ���������1/N
	if((INVERT == eFourier_dir) && (0 == iErrorCode))
	{

		for(i = 0; i < n; i++)
		{
			psInput_str[i].Im *= (-1);
		}
	}

	//���㸶��Ҷ�㷨�ļ���
	if(0 == iErrorCode)
	{
		i = 0;
		while(L <= n)
		{
			L *= 2;
			i++;
		}
		L = i - 1;
	}

	//���������ݽ���λ����
	if(0 == iErrorCode)
	{
		iErrorCode = bit_invert(psInput_str, iNbr_fft);
	}

	if(0 == iErrorCode)
	{

		for(m = 1; m <= L; m++)
		{//����ѭ��
			W.Re = 1; W.Im = 0; // W0

			//exp(pi/l)
			Wl.Re = cos(pi / pow(2, (double)m-1.0));
			Wl.Im = -sin(pi / pow(2, (double)m-1.0));// Wl, W = W0*Wl
			for(j = 0; j < nbr_butfly; j++)
			{//��ͬ���νᣬϵ����ͬ�ĵ��νᣬ����ֵΪ1��
				for(i = j; i + nbr_butfly < n; i += dist_betwn_butfly)//�̲��еڶ��������ǣ�i < n
				{//��ͬ���ν����㣬����ֵΪ���ν��࣬dist_betwn_butfly=2^M
					ip = i + nbr_butfly;

					//��������
					//t = x[ip]*W;
					sTemp.Re = psInput_str[ip].Re * W.Re - psInput_str[ip].Im * W.Im;
					sTemp.Im = psInput_str[ip].Re * W.Im + psInput_str[ip].Im * W.Re;

					//x[ip] = x[i]-x[ip]*W;
					psInput_str[ip].Re = psInput_str[i].Re - sTemp.Re;
					psInput_str[ip].Im = psInput_str[i].Im - sTemp.Im;

					//x[i] = x[i]+x[ip]*W;
					psInput_str[i].Re = psInput_str[i].Re + sTemp.Re;
					psInput_str[i].Im = psInput_str[i].Im + sTemp.Im;
				}

				//ϵ�����ƹ�ʽ
				//W = W*Wl;

				a = W.Re * Wl.Re - W.Im * Wl.Im;
				b = W.Re * Wl.Im + W.Im * Wl.Re;
				W.Re = a;
				W.Im = b;

			}
			dist_betwn_butfly *= 2;//��ʼ����2
			nbr_butfly *= 2;		 //��ʼ����1
		}
	}

	//����Ǹ���Ҷ���任����ȡ�������1/N
	if((0 == iErrorCode) && (INVERT == eFourier_dir))
	{
		for(i = 0; i < n; i++)
		{
			psInput_str[i].Im *= (-1 / iNbr_fft);//ȡ����
			psInput_str[i].Re *= 1 / iNbr_fft;	//1/N
		}//n
	}

	//���������������Ϊ�գ���������
	if(NULL != psOut_str && 0 == iErrorCode)
	{
		memcpy(psOut_str, psInput_str, iNbr_fft*sizeof(GNMA_complex_type));
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_freq_size
* Parameters:
*   -input:  	int iNbr_points,
			int iNbr_frames,
*   -input/output:
* -output:  int *piNbr_freq_points
* Returns:
* Description:   ���������GNMA_spectrum�������书���ǣ�*nr_freq_points���ΪN��1������N������С�� nr_points / nr_frames ��
   ���� 2^X ���������ġ�*nr_freq_points �� GNMA_spectrum �����������Ĵ�С��
==============================================================*/
int GNMA_freq_size(int iNbr_points, int iNbr_frames, int *piNbr_freq_points)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int iTemp = 0;
	int i = 0;
	int iFreq_Temp = 0;
	if(iNbr_points <=0 || 0 == iNbr_frames  || iNbr_points % iNbr_frames != 0)
	{
		iErrorCode = GNMA_PARAM_ERR;
	}
	else
	{
		iTemp =(int)(iNbr_points / iNbr_frames);
	}

	if(NULL == piNbr_freq_points && 0 == iErrorCode)
	{
		iErrorCode = GNMA_POINTER_ERR;
	}
	if(0 == iErrorCode)
	{
		do
		{
			iFreq_Temp = (int)pow(2, (double)i);
			*piNbr_freq_points = (int)(iFreq_Temp / 2) + 1;
			i++;
		}while(iFreq_Temp < iTemp);
		if(1 == iTemp)
		{
			*piNbr_freq_points = 2;
		}
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}


/** ======================================================
* Include:
* Function: GNMA_spectrum
* Parameters:
*   -input:  	int iNbr_points,  ���ݸ���
			int iNbr_frames,  ����֡��
			int iNbr_freq_points, Ƶ�ʵ���
			double dSample_period, ��������
			double *pdX, ��һ·��������
			double *pdY �ڶ�·��������
*   -input/output:
* -output:  	double *pdFreqs,  Ƶ�ʵ�����
			double *pdPxx,  ��һ·���ݵĹ�������������
			double *pdPyy,  �ڶ�·���ݹ�������������
			GNMA_complex_type *psPxy ��·���ݹ����׻�������
* Returns:   0
* Description:   �������ֶ��������ݼӴ��ض�,�ٽ��и���Ҷ�任,���������ǵ����׺ͻ���
==============================================================*/
extern int GNMA_spectrum(int iNbr_points,  int iNbr_frames,   int iNbr_freq_points,
						double dSample_period, double *pdX, double *pdY,
						 double *pdFreqs,  double *pdPxx,  double *pdPyy,  GNMA_complex_type *psPxy)
{
	int iErrorCode = 0;
	//	int iErrorLink[2] = {0, 0};
	//	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");

	int fft_points = 0;//the nbr for calculating fft
	//int frame = iNbr_frames;//����Ҷ�任��֡
	int i = 0;
	int j = 0;
	double dBit = 0.0;
	double *hanning = NULL;
	GNMA_complex_type *x_win = NULL;
	GNMA_complex_type *y_win = NULL;
	GNMA_complex_type *x_fft = NULL;
	GNMA_complex_type *y_fft = NULL;
	if(0 == iErrorCode)
	{//�ж�iNbr_points��iNbr_frames��iNbr_freq_points��dSample_period����Ч��
		if(iNbr_points <= 0 || iNbr_frames == 0 || iNbr_freq_points <=0 || iNbr_points % iNbr_points != 0 || dSample_period < 4e-4)
		{
			iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "iNbr_points value = %d, iNbr_frames = %d, iNbr_freq_points = %d, dSample_period = %e",
				iNbr_points, iNbr_frames, iNbr_freq_points, dSample_period);
#endif /* NEVER */

		}

	}
	if(0 == iErrorCode)
	{
		if(NULL == pdX || NULL == pdY || NULL == pdFreqs || NULL == pdPxx || NULL == pdPyy || NULL == psPxy)
		{
			iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdX = %d, pdY = %d, pdFreqs = %d, pdPxx = %d, psPxy = %d, pdPyy = %d",
				pdX , pdY, pdFreqs, pdPxx, psPxy, pdPyy);
#endif /* NEVER */
		}
	}
	
	if(0 == iErrorCode)
	{//��֤fft_points�Ƿ�Ϊ2��N����
		fft_points = (iNbr_freq_points - 1) * 2;
		dBit = log10((double)fft_points) / log10(2.0);
		if(!gnma_dbl_equal(dBit, (int)dBit) && !gnma_dbl_equal(dBit, (int)dBit + 1))
		{
			iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "dBit = %e, (int)dBit = %d", dBit, (int)dBit);
#endif /* NEVER */
		}
	}

	//�����Ƿ����ڴ�
	if(0 == iErrorCode)
	{
		if(NULL == (x_win = (GNMA_complex_type *) malloc(iNbr_frames * fft_points * sizeof(GNMA_complex_type))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "x_win malloc failed!");
#endif /* NEVER */
		}
		else
		{
			memset(x_win, 0, iNbr_frames * fft_points * sizeof(GNMA_complex_type));
		}
	}
	if(0 == iErrorCode)
	{
		if(NULL == (y_win = (GNMA_complex_type *) malloc(iNbr_frames * fft_points * sizeof(GNMA_complex_type))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "y_win malloc failed!");
#endif /* NEVER */
		}
		else
		{
			memset(y_win, 0, iNbr_frames * fft_points * sizeof(GNMA_complex_type));
		}
	}
	if(0 == iErrorCode)
	{
		if(NULL == (hanning = (double *) malloc(iNbr_frames * fft_points * sizeof(double))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "hanning window malloc failed!");
#endif /* NEVER */
		}
		else
		{
			memset(hanning, 0, iNbr_frames * fft_points * sizeof(double));
		}
	}

	//�������pdX��pdY�Ӵ�
	for(j = 0; j < iNbr_frames && 0 == iErrorCode; j++)
	{
		for(i = j * fft_points; i < (j * fft_points + iNbr_points / iNbr_frames) && 0 == iErrorCode; i++)
		{
			hanning[i - j * fft_points] = (1.0 - cos((i - j * fft_points) * GNMA_PI * 2 / fft_points)) / 2;
			x_win[i].Re = sqrt(8 / 3.0) * hanning[i - j * fft_points] * pdX[i % fft_points + j * iNbr_points / iNbr_frames];
			x_win[i].Im = 0.0;
			y_win[i].Re = sqrt(8 / 3.0) * hanning[i - j * fft_points] * pdY[i % fft_points + j * iNbr_points / iNbr_frames];
			y_win[i].Im = 0.0;
		}

		//�Բ�����fft_points�����ݣ����в�0
		if( (iNbr_points / iNbr_frames) < fft_points && 0 == iErrorCode)
		{
			for(i = (j * fft_points + iNbr_points / iNbr_frames); i < (j + 1) * fft_points; i++)
			{
				x_win[i].Re = 0;
				x_win[i].Im = 0;
				y_win[i].Re = 0;
				y_win[i].Im = 0;
			}
		}
	}

	//���hanning
	char *filename_write_hanning = ".\\hanning.txt";
	FILE *file_write_ptr_hanning = NULL;	
	file_write_ptr_hanning = fopen(filename_write_hanning,"w");
	if(file_write_ptr_hanning == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < 2048;i++)
	{
		fprintf(file_write_ptr_hanning,"%.25lf\n",hanning[i]);
		cout<<hanning[i]<<endl;
	}

	//���x_win
	char *filename_write_x_win = ".\\x_win.txt";
	FILE *file_write_ptr_x_win = NULL;	
	file_write_ptr_x_win = fopen(filename_write_x_win,"w");
	if(file_write_ptr_x_win == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < 2048;i++)
	{
		fprintf(file_write_ptr_x_win,"%.25lf\n",x_win[i].Re);
		cout<<x_win[i].Re<<endl;
	}
	//

	free(hanning);


	if(0 == iErrorCode)
	{
		if(NULL == (x_fft = (GNMA_complex_type *) malloc(iNbr_frames * fft_points * sizeof(GNMA_complex_type))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "x_fft malloc failed!");
#endif /* NEVER */
		}
		else
		{
			memset(x_fft, 0, iNbr_frames * fft_points * sizeof(GNMA_complex_type));
		}
	}
	if(0 == iErrorCode)
	{
		if(NULL == (y_fft = (GNMA_complex_type *) malloc(iNbr_frames * fft_points * sizeof(GNMA_complex_type))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_spectrum error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "y_fft malloc failed!");
#endif /* NEVER */
		}
		else
		{
			memset(y_fft, 0, iNbr_frames * fft_points * sizeof(GNMA_complex_type));
		}
	}

	//�ԼӴ�������ݽ���fft����
	for(j = 0; j < iNbr_frames && 0 == iErrorCode; j++)
	{
		if(0 == iErrorCode)
		{
			if(0 != (iErrorCode = gnma_fft(fft_points, &x_win[j * fft_points], &x_fft[j * fft_points], NORMAL)))
			{
#ifdef NEVER
				iErrorCode = GNMA_SYSTEM_ERR;
				psErrorText = ERAIcreateText("%s: gnma_fft error.", __FUNCTION__);
				ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
				free(psErrorText);
#endif /* NEVER */
			}
//			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "x-> fft_points value = %e, j nbr_frame value = %e ", fft_points, j);
		}

		if(0 == iErrorCode)
		{
			if(0 != (iErrorCode = gnma_fft(fft_points, &y_win[j * fft_points], &y_fft[j * fft_points], NORMAL)))
			{
				iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
				psErrorText = ERAIcreateText("%s: gnma_fft error.", __FUNCTION__);
				ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
				free(psErrorText);
#endif /* NEVER */
			}
	//		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "y-> fft_points value = %e, j nbr_frame value = %e ", fft_points, j);
		}

	}
	
	
	//���x_fft
	char *filename_write_x_fft = ".\\x_fft.txt";
	FILE *file_write_ptr_x_fft = NULL;	
	file_write_ptr_x_fft = fopen(filename_write_x_fft,"w");
	if(file_write_ptr_x_fft == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < 2048;i++)
	{
		fprintf(file_write_ptr_x_fft,"%.25lf\n",x_fft[i].Im);
		cout<<x_fft[i].Re<<"+"<<x_fft[i].Im<<"*i"<<endl;
	}
	//���y_fft
	char *filename_write_y_fft = ".\\win_hanning.txt";
	FILE *file_write_ptr_y_fft = NULL;	
	file_write_ptr_y_fft = fopen(filename_write_y_fft,"w");
	if(file_write_ptr_y_fft == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < 2048;i++)
	{
		fprintf(file_write_ptr_y_fft,"%.25lf\n",y_fft[i]);
		cout<<y_fft[i].Re<<endl;
	}
	//

	free(x_win);
	free(y_win);

	//���ݹ�ʽ���㹦����,��֡������ƽ��
	for(i = 0; i < iNbr_freq_points && 0 == iErrorCode; i++)//iNbr_freq_points
	{
		pdPxx[i] = 0;
		pdPyy[i] = 0;
		psPxy[i].Re = 0;
		psPxy[i].Im = 0;
		for(j = 0; j < iNbr_frames && 0 == iErrorCode; j++)
		{
			pdPxx[i] += (x_fft[j * fft_points + i].Re * x_fft[j * fft_points + i].Re + x_fft[j * fft_points + i].Im * x_fft[j * fft_points + i].Im) / (iNbr_frames * iNbr_frames * fft_points * fft_points);
			pdPyy[i] += (y_fft[j * fft_points + i].Re * y_fft[j * fft_points + i].Re + y_fft[j * fft_points + i].Im * y_fft[j * fft_points + i].Im) / (iNbr_frames * iNbr_frames  * fft_points * fft_points);
			psPxy[i].Re += (x_fft[j * fft_points + i].Re * y_fft[j * fft_points + i].Re + x_fft[j * fft_points + i].Im * y_fft[j * fft_points + i].Im) / (iNbr_frames * iNbr_frames  * fft_points * fft_points);
			psPxy[i].Im += (x_fft[j * fft_points + i].Re * y_fft[j * fft_points + i].Im - x_fft[j * fft_points + i].Im * y_fft[j * fft_points + i].Re) / (iNbr_frames * iNbr_frames  * fft_points * fft_points);
		}
		pdFreqs[i] = i  / (dSample_period * (iNbr_freq_points * 2));
	}

	//���pxx
	char *filename_write_pdPxx = ".\\pdPxx.txt";
	FILE *file_write_ptr_pdPxx = NULL;	
	file_write_ptr_pdPxx = fopen(filename_write_pdPxx,"w");
	if(file_write_ptr_pdPxx == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdPxx,"%.25lf\n",pdPxx[i]);
		cout<<pdPxx[i]<<endl;
	}

	//���pyy
	char *filename_write_pdPyy = ".\\pdPyy.txt";
	FILE *file_write_ptr_pdPyy = NULL;	
	file_write_ptr_pdPyy = fopen(filename_write_pdPyy,"w");
	if(file_write_ptr_pdPyy == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdPyy,"%.25lf\n",pdPyy[i]);
		cout<<pdPyy[i]<<endl;
	}

	//���pxy
	char *filename_write_pdPxy = ".\\psPxy.txt";
	FILE *file_write_ptr_pdPxy = NULL;	
	file_write_ptr_pdPxy = fopen(filename_write_pdPxy,"w");
	if(file_write_ptr_pdPxy == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	
	i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdPxy,"%.25lf %0.25lf\n",psPxy[i].Re, psPxy[i].Im);
		cout<<psPxy[i].Re<<"+"<<psPxy[i].Im<<"* i"<<endl;
	}

	free(x_fft);
	free(y_fft);
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_transfer
* Parameters:
*   -input:  	int iNbr_freq_points,  Ƶ�ʵ����
			double *pdPxx, ��һ·���ݵ�����
			double *pdPyy, �ڶ�·���ݵ�����
			GNMA_complex_type *psPxy,��·���ݵĻ���
*   -input/output:
* -output:  	double *pdMagnitude, ���ݺ����ķ�ֵ
			double *pdPhase,  ��λ
			double *pdCoherence �����
* Returns:   0
* Description:   ������·���ݵ����׺ͻ���,�������ǵĴ��ݺ�����������
==============================================================*/
extern int GNMA_transfer(int iNbr_freq_points,  double *pdPxx, double *pdPyy,
						  GNMA_complex_type *psPxy,  double *pdMagnitude,
						  double *pdPhase,  double *pdCoherence)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	double dTemp_amp;
	GNMA_complex_type *sTemp_tf = NULL;
	//double dTemp = 0.0;
	if(iNbr_freq_points <= 0)
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_transfer error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "iNbr_freq_points value = %d", iNbr_freq_points);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		if(NULL == pdCoherence || NULL == pdMagnitude || NULL == pdPxx ||
			NULL == psPxy || NULL == pdPyy || NULL == pdPhase)
		{
			iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_transfer error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdPhase = %d ,pdMagnitude = %d, pdCoherence = %d", pdPhase, pdMagnitude, pdCoherence);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdPxx = %d ,psPxy = %d, pdPyy = %d", pdPxx, psPxy, pdPyy);
#endif /* NEVER */
		}
	}
	if(0 == iErrorCode)
	{
		if(NULL == (sTemp_tf = (GNMA_complex_type *) malloc(iNbr_freq_points * sizeof(GNMA_complex_type))))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_transfer error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "sTemp_tf malloc failed!");
#endif /* NEVER */
		}
	}
	for(int i = 0; i < iNbr_freq_points && 0 == iErrorCode; i++)
	{
		if ((fabs(pdPxx[i]) > 4.450147717014403e-308)\
				&&fabs(pdPyy[i]) > 4.450147717014403e-308)
		{
			sTemp_tf[i].Re = (psPxy[i].Re) / (pdPxx[i]);
			sTemp_tf[i].Im = (psPxy[i].Im) / (pdPxx[i]);

			//�����(ʵ����ƽ��+�鲿��ƽ��)/���׵ĳ˻�
			pdCoherence[i] = ((psPxy[i].Im) * (psPxy[i].Im) + (psPxy[i].Re) * (psPxy[i].Re)) / (pdPxx[i] * pdPyy[i]);
		}
		else
		{
			sTemp_tf[i].Re = 1.0;
			sTemp_tf[i].Im = 0.0;
			pdCoherence[i] = 1.0;
		}

		dTemp_amp = sqrt(sTemp_tf[i].Re * sTemp_tf[i].Re + sTemp_tf[i].Im * sTemp_tf[i].Im);
		if (fabs(dTemp_amp) < 4.450147717014403e-308)
		{
			dTemp_amp = 2.225073858507201e-308;
		}
		//��ֵ
		pdMagnitude[i] = 20*log10(dTemp_amp);

		//��λ
		if (fabs(sTemp_tf[i].Re) < 4.450147717014403e-308)
		{
			if (sTemp_tf[i].Im < 0.0)
			{
				pdPhase[i] = -90;
			}
			else
			{
				pdPhase[i] = 90;
			}
		}
		else
		{
			pdPhase[i] = 5.729577951308232e1*atan2(sTemp_tf[i].Im,sTemp_tf[i].Re);
			if(i > 2)
			{	//atan2�ķ�Χ��[-pi��pi)����A��˾�õķ�Χ��[-2pi��2pi)��
				//ͨ�����ݷ��֣�A��˾���������˴���
				//����atan2�����ֵ��ǰһֵ�Ĳ��atan2��[-2pi��2pi)�ڵ���һֵ��ǰһֵ�Ĳ�Ƚϡ�
				//��������ֵ��ȣ���ȡatan2���ֵ
				//���ǰ�ߴ��ں��ߣ���ȡatan2��[-2pi��2pi)�ڵ���һֵ��
				//������ߵĲ�ֵ����540��Ҳȡatan2��[-2pi��2pi)�ڵ���һֵ��
				//����֤����������A��˾һ�£�����ԭ���д���֤��
				//by ֣����20080818
				/*dTemp = pdPhase[i] > 0 ? pdPhase[i] - 360 : pdPhase[i] + 360;
				if((fabs(dTemp) - fabs(pdPhase[i - 1])) < 180 || (fabs(pdPhase[i]) - fabs(pdPhase[i - 1])) < 180)
				{
					if((fabs(dTemp) - fabs(pdPhase[i - 1])) < (fabs(pdPhase[i]) - fabs(pdPhase[i - 1])))
					{
						pdPhase[i] = dTemp;
					}
				}
				else
				{
					if((fabs(dTemp) - fabs(pdPhase[i - 1])) > (fabs(pdPhase[i]) - fabs(pdPhase[i - 1])))
					{
						pdPhase[i] = dTemp;
					}
				}*/
			}
		}
	}

	//�����ֵ
	char *filename_write_pdMagnitude = ".\\pdMagnitude.txt";
	FILE *file_write_ptr_pdMagnitude = NULL;	
	file_write_ptr_pdMagnitude = fopen(filename_write_pdMagnitude,"w");
	if(file_write_ptr_pdMagnitude == NULL)
	{
		cout<<"Open file failed"<<endl;
	}
	int i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdMagnitude,"%.25lf\n",pdMagnitude[i]);
		cout<<pdMagnitude[i]<<endl;
	}

	//�����λ
	char *filename_write_pdPhase = ".\\pdPhase.txt";
	FILE *file_write_ptr_pdPhase = NULL;	
	file_write_ptr_pdPhase = fopen(filename_write_pdPhase,"w");
	if(file_write_ptr_pdPhase == NULL)
	{
		cout<<"Open file failed"<<endl;
	}	
	i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdPhase,"%.25lf\n",pdPhase[i]);
		cout<<pdPhase[i]<<endl;
	}

	//��������
	char *filename_write_pdCoherence = ".\\pdCoherence.txt";
	FILE *file_write_ptr_pdCoherence = NULL;	
	file_write_ptr_pdCoherence = fopen(filename_write_pdCoherence,"w");
	if(file_write_ptr_pdCoherence == NULL)
	{
		cout<<"Open file failed"<<endl;
	}	
	i = 0;
	for(i= 0 ;i < iNbr_freq_points;i++)
	{
		fprintf(file_write_ptr_pdCoherence,"%.25lf\n",pdCoherence[i]);
		cout<<pdCoherence[i]<<endl;
	}

	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_mov_avg_and_std_dev
* Parameters:
*   -input:  	double *input, ����
			int input_size, ���ݳ���
			int filter_window, MA�Ĵ�����,ǰ��filter_window/2, ��ǰ�㣬����filter_window/2-1
*   -input/output:
* -output:  	double *mov_avg,  MA  ����ƽ��
			double *mov_std_dev MSD
* Returns:   0
* Description:   ������·���ݵ����׺ͻ���,�������ǵĴ��ݺ�����������
==============================================================*/

extern int GNMA_mov_avg_and_std_dev(double *input, int input_size, int filter_window,
									  double *mov_avg,  double *mov_std_dev)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int i = 0;
	int j = 0;
	int iBefore_nbr = (int)floor((float)filter_window / 2);
	int iAfter_nbr_with_current = filter_window - iBefore_nbr;

	if((filter_window > input_size) || (0 == filter_window) || (0 == input_size))
	{
		//������Ч���ж�
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_mov_avg_and_std_dev error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "filter_window value = %d, input_size = %d ", filter_window, input_size);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		if((NULL == mov_avg) || (NULL == mov_std_dev) || NULL == input)
		{
			//�ڴ��ж�
			iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_mov_avg_and_std_dev error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg = %d ,mov_std_dev = %d, input = %d", mov_avg, mov_std_dev, input);
#endif /* NEVER */
		}
	}
	if(0 == iErrorCode)
	{
		for(i = 0; i < input_size; i++)
		{
			//printf("%d\n", i);
			mov_std_dev[i] = 0.0;
			mov_avg[i] = 0.0;
			if(i > iBefore_nbr && i < (input_size - iAfter_nbr_with_current))
			{
				for(j = i - iBefore_nbr; j < i + iAfter_nbr_with_current; j++)
				{
					mov_avg[i] += input[j];
				}
				mov_avg[i] /= filter_window;

				for(j = i - iBefore_nbr; j < i + iAfter_nbr_with_current; j++)
				{
					mov_std_dev[i] += ((input[j] - mov_avg[i]) * (input[j] - mov_avg[i]));
				}

				mov_std_dev[i] /= filter_window;
				mov_std_dev[i] = sqrt(mov_std_dev[i]);
			}
			else if(i <= iBefore_nbr)
			{
				for(j = 0; j < i+iAfter_nbr_with_current; j++)
				{
					mov_avg[i] += input[j];
				}
				mov_avg[i] /= (i+iAfter_nbr_with_current);

				for(j = 0; j < i + iAfter_nbr_with_current; j++)
				{
					mov_std_dev[i] += ((input[j] - mov_avg[i]) * (input[j] - mov_avg[i]));
				}
				mov_std_dev[i] /= (i + iAfter_nbr_with_current);
				mov_std_dev[i] = sqrt(mov_std_dev[i]);
			}
			else if(i >= (input_size - iAfter_nbr_with_current))
			{
				for(j = (i - iBefore_nbr); j < input_size; j++)
				{
					mov_avg[i] += input[j];
				}
				mov_avg[i] /= (input_size - i + iBefore_nbr);

				for(j = i - iBefore_nbr; j < input_size; j++)
				{
					mov_std_dev[i] += ((input[j] - mov_avg[i]) * (input[j] - mov_avg[i]));
				}
				mov_std_dev[i] /= (input_size - i + iBefore_nbr);
				mov_std_dev[i] = sqrt(mov_std_dev[i]);
			}
			//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg[0] = %d ,mov_std_dev[0] = %d", mov_avg[0], mov_std_dev[0]);
			//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg[1] = %d ,mov_std_dev[1] = %d", mov_avg[1], mov_std_dev[1]);
			//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg[2] = %d ,mov_std_dev[2] = %d", mov_avg[2], mov_std_dev[2]);
			//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg[3] = %d ,mov_std_dev[3] = %d", mov_avg[3], mov_std_dev[3]);
			//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mov_avg[4] = %d ,mov_std_dev[4] = %d", mov_avg[4], mov_std_dev[4]);
		}

	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_average_value
* Parameters:
*   -input:  	double *pdData,�����׵�ַ
			int iNumber, ���ݸ���
			int iSizeOfItem  �����������͵Ĵ�С
*   -input/output:
* -output:  	double *pdMean,  ��ֵ
			double *pdStdDev ����
* Returns:   0
* Description:   ���������ƽ��ֵ,�ͷ���
==============================================================*/
extern int	GNMA_average_value(double *pdData, int iNumber, int iSizeOfItem,
								double *pdMean, double *pdStdDev)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
#endif /* NEVER */

	int i = 0;
	double dTemp = iSizeOfItem;
	double dSum = 0;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
	int idouble_nbr = (int)iSizeOfItem / sizeof(double);
	if(0 == iErrorCode && (!gnma_dbl_equal(idouble_nbr, iSizeOfItem / sizeof(double))))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_average_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "double_nbr value = %d, SizeOfItem = %d ", idouble_nbr, iSizeOfItem);
#endif /* NEVER */
	}

	if(NULL == pdData || NULL == pdMean || NULL == pdStdDev)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_average_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdData value = %d, pdMean = %d ,pdStdDev= %d  ", pdData, pdMean, pdStdDev);
#endif /* NEVER */
	}
	if(0 == iErrorCode && (iNumber <= 1 || iSizeOfItem <= 0))//
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_average_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "number value = %d, iSizeOfItem = %d ", iNumber, iSizeOfItem);
#endif /* NEVER */
	}
	for(i = 0; i < iNumber && 0 == iErrorCode; i++)
	{
		dSum += *(pdData + i * idouble_nbr);
	}
	if(0 == iErrorCode)
	{
		*pdMean = dSum / iNumber;
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "average value = %e", *pdMean);
	}
	if(0 == iErrorCode)
	{
		dTemp = dSum * dSum / iNumber;
		dSum = 0;
		for(i = 0; i < iNumber; i++)
		{
			 dSum += (*(pdData + i * idouble_nbr)) * (*(pdData + i * idouble_nbr) );
		}
		*pdStdDev = sqrt((dSum - dTemp) / (iNumber - 1));
	//	THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "sigma value = %e", *pdStdDev);
	}
//	THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_peak_value
* Parameters:
*   -input:  	double *pdData,�����׵�ַ
			int iNumber, ���ݸ���
			int iSizeOfItem  �����������͵Ĵ�С
*   -input/output:
* -output:  	double *pDPeak  ��ֵ
* Returns:   0
* Description:   ��������ķ�ֵ
==============================================================*/
extern int GNMA_peak_value( double *pdData,  int iNumber,  int iSizeOfItem,  double *pDPeak)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
#endif /* NEVER */

	int i = 0;
	double dTemp = iSizeOfItem;
//	THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
	int idouble_nbr = (int)iSizeOfItem / sizeof(double);
	if(0 == iErrorCode && (!gnma_dbl_equal(idouble_nbr, iSizeOfItem / sizeof(double))))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_peak_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "double_nbr value = %d, SizeOfItem = %d ", idouble_nbr, iSizeOfItem);
#endif /* NEVER */
	}

	if(NULL == pdData || NULL == pDPeak)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_peak_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdData value = %d, pDPeak = %d", pdData, pDPeak);
#endif /* NEVER */

	}
	if(0 == iErrorCode && (iNumber <= 0 || iSizeOfItem <= 0))//
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_peak_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "number value = %d, iSizeOfItem = %d ", iNumber, iSizeOfItem);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		dTemp = *pdData;
		for(i = 1; i < iNumber; i++)
		{
			*pDPeak = fabs(*(pdData + i * idouble_nbr)) > fabs(dTemp) ? (*(pdData + i * idouble_nbr)): dTemp;
			dTemp = *pDPeak;
		}
	//	THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "peak value = %e", *pDPeak);
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_max_value
* Parameters:
*   -input:  	double *pdData,�����׵�ַ
			int iNumber, ���ݸ���
			int iSizeOfItem  �����������͵Ĵ�С
*   -input/output:
* -output:  	double *pdMax  ���ֵ
* Returns:   0
* Description:   ������������ֵ
==============================================================*/
extern int GNMA_max_value( double * pdData,  int iNumber,  int iSizeOfItem,  double * pdMax)
{
	 int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
#endif /* NEVER */

	int i = 0;
	double dTemp = iSizeOfItem;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
	int idouble_nbr = (int)iSizeOfItem / sizeof(double);
	if(0 == iErrorCode && (!gnma_dbl_equal(idouble_nbr, iSizeOfItem / sizeof(double))))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_max_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "double_nbr value = %d, SizeOfItem = %d ", idouble_nbr, iSizeOfItem);
#endif /* NEVER */
	}
	if(NULL == pdData || NULL == pdMax)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_max_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdData value = %d, pdMin = %d", pdData, pdMax);
#endif /* NEVER */
	}
	if(0 == iErrorCode && (iNumber <= 0 || iSizeOfItem <=0))//
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_max_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "number value = %d, iSizeOfItem = %d ", iNumber, iSizeOfItem);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		dTemp = *pdData;
		*pdMax = dTemp;
		for(i = 1; i < iNumber; i++)
		{
			*pdMax = *(pdData + i * idouble_nbr) > dTemp ? (*(pdData + i * idouble_nbr)) : dTemp;
			dTemp = *pdMax;
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "max value = %e", *pdMax);
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_min_value
* Parameters:
*   -input:  	double *pdData,�����׵�ַ
			int iNumber, ���ݸ���
			int iSizeOfItem  �����������͵Ĵ�С
*   -input/output:
* -output:  	double *pdMin  ��Сֵ
* Returns:   0
* Description:   �����������Сֵ
==============================================================*/
extern int GNMA_min_value( double * pdData,  int iNumber,  int iSizeOfItem,  double * pdMin)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
#endif /* NEVER */

	int i = 0;
	double dTemp = iSizeOfItem;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
	int idouble_nbr = (int)iSizeOfItem / sizeof(double);
	if(NULL == pdData || NULL == pdMin)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_min_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
  		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdData value = %d, pdMin = %d", pdData, pdMin);
#endif /* NEVER */
	}
	if(0 == iErrorCode && (iNumber <= 0 || iSizeOfItem <=0))//||
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_min_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "number value = %d, iSizeOfItem = %d ", iNumber, iSizeOfItem);
#endif /* NEVER */
	}
	if(0 == iErrorCode && (!gnma_dbl_equal(idouble_nbr, iSizeOfItem / sizeof(double))))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_min_value error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "double_nbr value = %d, SizeOfItem = %d ", idouble_nbr, iSizeOfItem);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		dTemp = *pdData;
		*pdMin = dTemp;
		for(i = 1; i < iNumber; i++)
		{
			*pdMin = *(pdData + i * idouble_nbr) < dTemp ? (*(pdData + i * idouble_nbr) ): dTemp;
			dTemp = *pdMin;
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "min value = ", *pdMin);
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_statistics
* Parameters:
*   -input:  	double *pdData,�����׵�ַ
			int iNumber, ���ݸ���
			int iSizeOfItem  �����������͵Ĵ�С
*   -input/output:
* -output:  	double *pdMean,  ��ֵ
			double *pdStdDev,  ����
			double *pdPeak, ��ֵ
			double *pdMin  ��Сֵ
			double *pdMax,  ���ֵ
			double *pdMean3Sigma
* Returns:   0
* Description:   ���������ͳ��ֵ
==============================================================*/
extern int GNMA_statistics( double *pdData,  int iNumber,  int iSizeOfItem,
							 double *pdMean,  double *pdStdDev,  double *pdPeak,
							 double *pdMin,  double *pdMax,  double *pdMean3Sigma)
{
	int iErrorCode = 0;
//	int iErrorLink[2] = {0, 0};
//	char *psErrorText = NULL;

	double dTemp = iSizeOfItem;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
	if(NULL == pdData || NULL == pdMin || NULL == pdMean || NULL == pdStdDev \
		|| NULL == pdMax|| NULL == pdPeak|| NULL == pdMean3Sigma)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_statistics error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "pdData value = %d, \
		pdMean value = %d, pdStdDev = %d, pdPeak = %d, pdMin = %d, pdMax = %d, pdMean3Sigma = %d	", pdData,
		pdMean, pdStdDev, pdPeak, pdMin, pdMax, pdMean3Sigma);
#endif /* NEVER */
	}
	if(0 == iErrorCode && (iNumber <= 1 || iSizeOfItem <=0))
	{
		iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_statistics error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "number value = %d, iSizeOfItem = %d ", iNumber, iSizeOfItem);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		if(0 != (iErrorCode = GNMA_average_value(pdData, iNumber, iSizeOfItem, pdMean, pdStdDev)))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_average_value error.", __FUNCTION__);
			ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mean value = %e, sigma value = %e ", *pdMean, *pdStdDev);
	}

	if(0 == iErrorCode)
	{
		if(0 != (iErrorCode = GNMA_peak_value(pdData, iNumber, iSizeOfItem, pdPeak)))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_peak_value error.", __FUNCTION__);
			ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "peak value  = %e", *pdPeak);
	}
	if(0 == iErrorCode)
	{
		if(0 != (iErrorCode = GNMA_max_value(pdData, iNumber, iSizeOfItem, pdMax)))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_max_value error.", __FUNCTION__);
			ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "max value  = %e", *pdMax);
	}
	if(0 == iErrorCode)
	{
		if(0 != (iErrorCode = GNMA_min_value(pdData, iNumber, iSizeOfItem, pdMin)))
		{
			iErrorCode = GNMA_SYSTEM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_min_value error.", __FUNCTION__);
			ERAIlogError(iErrorCode, iErrorLink, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "min value  = %e", *pdMin);
	}
	if(0 == iErrorCode)
	{
		dTemp = *pdStdDev;
		*pdMean3Sigma = fabs(*pdMean) + 3 * dTemp;
		//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "mean+ 3 sigma = %e", *pdMean3Sigma);
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_calc_bandwidth
* Parameters:
*   -input: 	int sim_mode,  ����ģʽ
			double *freq_point Ƶ�ʵ�
			 double *magnitude ��ֵ����
			 int nbr_fre_trace,Ƶ�ʵ����
			 double sample_period, ��������
			 double start_fr ������ʼƵ��
			 double stop_fr ������ֹƵ��
*   -input/output:
* -output:  	 int *if_found,�Ƿ��ҵ�
			double *bw/����ֵ
* Returns:   0
* Description:   ���������С������ֵ��С��������Ӧ��Ƶ��ֵ
==============================================================*/
extern int GNMA_calc_bandwidth(int sim_mode,  double *freq_point/*array*/,
								  double *magnitude/*array*/,  int nbr_fre_trace,
								  double sample_period, double start_fr/*arg5C*/,
								  double stop_fr/*arg64*/,  int *if_found/*arg6C*/,  double *bw/*arg70*/)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int i = 0;
	int iStartIndex = 0;
	int iStopIndex = 0;
	int iTemp = 0;
	int iBwIndex = 0;
	if(0 == sim_mode)
	{
		if(NULL == freq_point || NULL == magnitude || NULL == if_found || NULL == bw)
		{
			iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_bandwidth error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "freq_point value = %d, \
			magnitude value = %d, if_found = %d, bw = %d", freq_point,
			magnitude, if_found, bw);
#endif /* NEVER */
		}
		if(0 == iErrorCode)
		{
			if(nbr_fre_trace <=0 || sample_period < 4e-4 || start_fr < 0 || start_fr >= stop_fr)
			{
				iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
				psErrorText = ERAIcreateText("%s: GNMA_calc_bandwidth error.", __FUNCTION__);
				ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
				free(psErrorText);
				THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "nbr_fre_trace value = %d, \
				sample_period value = %e, start_fr = %e, stop_fr = %e", nbr_fre_trace,
				sample_period, start_fr, stop_fr);
#endif /* NEVER */
			}
		}
	/********************************/
	//���ݿ�ʼƵ�ʵ�ͽ���Ƶ�ʵ�����start_index,stop_index
	/************************************/
		if(0 == iErrorCode)
		{
			iStartIndex = (int)(start_fr * (nbr_fre_trace - 1) * 2 * sample_period);
			//printf("start_index = %d \n",iStartIndex);
			iStopIndex = (int)(stop_fr * (nbr_fre_trace - 1) * 2 * sample_period)+1;
			//printf("stop_index = %d \n",iStopIndex);
		}
	/**************************************/
	//��start_index�ķ�ֵ��ʼѰ�Ҵ�����Խ������index-1����index
	/******************************************************/
		iTemp = 1;
		for (i = iStartIndex; i <= iStopIndex && 0 == iErrorCode; i++)
		{
			if(gnma_dbl_equal(magnitude[i], 0))
			{//�����ƵֵΪ��
				iBwIndex = i;
				*if_found = 1;
				break;
			}
			else
			{//�����Ƶֵ��Ϊ��
				iTemp *= (int)(magnitude[i] / fabs(magnitude[i]));
				if(-1 == iTemp)
				{	//��ʱ����Ӧ�ķ�ֵΪ�׸���ֵ�����ҵ�
					iBwIndex = i;
				//	printf("iBwIndex = %d \n",iBwIndex);
					*if_found = 1;
					break;
				}
			}
		}
		if(0 == iBwIndex && 0 == iErrorCode)
		{//û���ҵ�����Ƶ�ʵ�
			*if_found = 0;
			iErrorCode = GNMA_SEARCH_FAIL;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_bandwidth error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
	/*****************************************/
	//����index-1��index��Ѱ�Ҷ�Ӧ��Ƶ�ʵ㣬��������Ƶ��б�߽���㡣�õ�����Ƶ�ʵ�
	/***************************************************/
		if(0 == iErrorCode && 1 == *if_found)
		{
			*bw = freq_point[iBwIndex - 1] - \
				 magnitude[iBwIndex - 1] * (freq_point[iBwIndex] - freq_point[iBwIndex - 1]) / (magnitude[iBwIndex] - magnitude[iBwIndex - 1]);
		}
	}
	else
	{
		//����ģʽ
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_calc_bandwidth
* Parameters:
*   -input: 	int sim_mode,  ����ģʽ
			double *freq_point Ƶ�ʵ�
			 double *magnitude ��ֵ����
			 int nbr_fre_trace,Ƶ�ʵ����
			 double sample_period, ��������
			 double start_fr ������ʼƵ��
			 double stop_fr ������ֹƵ��
*   -input/output:
* -output:  	 int *if_found,�Ƿ��ҵ�
			double *ph_mar ��λԣ��
			double *ph_fre ��λԣ�ȶ�Ӧ��Ƶ��ֵ
* Returns:   0
* Description:
==============================================================*/
extern int GNMA_calc_phase_margin( int sim_mode,  double *freq_point/*array*/,
								    double *magnitude/*array*/,  double *phase/*array*/,
								     int nbr_fre_trace,  double sample_period,
								    double start_fr/*arg60*/,  double stop_fr/*arg68*/,
								    int *if_found/*arg70*/,
								    double *ph_mar/*arg74*/,  double *ph_fre/*arg78*/)
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int i = 0;
	int iStartIndex = 0;
	int iStopIndex = 0;
	int iTemp = 0;
	int iBwIndex = 0;
	double dF = 0.0;
	if(NULL == freq_point || NULL == magnitude || NULL == phase || NULL == if_found || NULL == ph_mar || NULL == ph_fre)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_calc_phase_margin error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "freq_point value = %d, \
		magnitude value = %d, if_found = %d, phase = %d, ph_mar = %d, ph_fre = %d", freq_point,
		magnitude, if_found, phase, ph_mar, ph_fre);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		if(nbr_fre_trace <=0 || sample_period < 4.0e-4 || start_fr <= 0 || start_fr >=stop_fr)
		{
			iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_phase_margin error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "nbr_fre_trace value = %d, \
			sample_period value = %e, start_fr = %e, stop_fr = %e", nbr_fre_trace,
			sample_period, start_fr, stop_fr);
#endif /* NEVER */
		}
	}
	if(0 == sim_mode)
	{
	/********************************/
	//���ݿ�ʼƵ�ʵ�ͽ���Ƶ�ʵ�����start_index,stop_index
	/************************************/
		if(0 == iErrorCode)
		{
			iStartIndex = (int)(start_fr * (nbr_fre_trace - 1) * 2 * sample_period);
			//printf("start_index = %d \n",iStartIndex);
			iStopIndex = (int)(stop_fr * (nbr_fre_trace - 1) * 2 * sample_period)+1;
			//printf("stop_index = %d \n",iStopIndex);
		}
	/**************************************/
	//��start_index�ķ�ֵ��ʼѰ�Ҵ�����Խ������index-1����index
	/******************************************************/
		iTemp = 1;
		for (i = iStartIndex; i <= iStopIndex && 0 == iErrorCode; i++)
		{
			if(gnma_dbl_equal(magnitude[i], 0.0))
			{//�����ƵֵΪ��
				iBwIndex = i;
				*if_found = 1;
				break;
			}
			else
			{//�����Ƶֵ��Ϊ��
				iTemp *= (int)(magnitude[i] / fabs(magnitude[i]));
				if(-1 == iTemp)
				{	//��ʱ����Ӧ�ķ�ֵΪ�׸���ֵ�����ҵ�
					iBwIndex = i;
				//	printf("iBwIndex = %d \n",iBwIndex);
					*if_found = 1;
					break;
				}
			}
		}
		if(0 == iBwIndex && 0 == iErrorCode)
		{//û���ҵ�����Ƶ�ʵ�
			*if_found = 0;
			iErrorCode = GNMA_SEARCH_FAIL;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_phase_margin error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
	/*****************************************/
	//����index-1��index��Ѱ�Ҷ�Ӧ��Ƶ�ʵ㣬��������Ƶ��б�߽���㡣�õ�����Ƶ�ʵ�
	/***************************************************/
		if(0 == iErrorCode && 1 == *if_found)
		{
			if(magnitude[iBwIndex - 1] >= 0.0)
			{
				dF = freq_point[iBwIndex - 1] - \
					 magnitude[iBwIndex - 1] * (freq_point[iBwIndex] - freq_point[iBwIndex - 1]) / (magnitude[iBwIndex] - magnitude[iBwIndex - 1]);
				*ph_fre = dF;
			}
			else
			{
				dF = freq_point[iBwIndex];
				*ph_fre = freq_point[iBwIndex];
			}
			//printf("iBwIndex = %d \n",iBwIndex);
		}
		if(0 == iErrorCode && 1 == *if_found)
		{//�ҵ������ˣ���Ҫ������Ƶԣ��ֵ
			*ph_mar = phase[iBwIndex] + \
						(dF - freq_point[iBwIndex]) * (phase[iBwIndex - 1] - phase[iBwIndex]) / (freq_point[iBwIndex - 1] - freq_point[iBwIndex]);
			//printf("phase[%d] = %e \n", iBwIndex, phase[iBwIndex]);
			//printf("phase[%d] = %e \n", iBwIndex-1, phase[iBwIndex - 1]);
		}
	}
	else
	{
		//����ģʽ
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_calc_amplitude_margin
* Parameters:
*   -input: 	int sim_mode,  ����ģʽ
			double *freq_point Ƶ�ʵ�
			 double *magnitude ��ֵ����
			 int nbr_fre_trace,Ƶ�ʵ����
			 double sample_period, ��������
			double bw,��Ϊ��ʼƵ��
			double amp_stop_fr ��ֹƵ��
*   -input/output:
* -output:  	 int *if_found,�Ƿ��ҵ�
			double *ampl_mar��ֵԣ��
			double *ampl_freq ��ֵԣ�ȶ�Ӧ��Ƶ��ֵ
* Returns:   0
* Description:
==============================================================*/
extern int  GNMA_calc_amplitude_margin( int sim_mode,  double *freq_point/*array*/,
									   double *magnitude/*array*/,  double *phase,
									   int nbr_fre_trace, double sample_period,
									   double bw/*arg60,��Ϊ��ʼƵ��*/,
									   double amp_stop_fr/*arg68*/,
									  int*if_found/*arg70*/,  double *ampl_mar/*arg74*/,
									   double *ampl_freq/*arg78*/ )
{
	int iErrorCode = 0;
#ifdef NEVER
	int iErrorLink[2] = {0, 0};
	char *psErrorText = NULL;
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, ">()");
#endif /* NEVER */

	int i = 0;
	int  iStart = 0;
	int iStop = 0;
	int iFlag = 0;
	int iAmpIndex = 0;
	double dTemp = 0.0;
	if(NULL == freq_point || NULL == magnitude || NULL == phase || NULL == if_found || NULL == ampl_mar || NULL == ampl_freq)
	{
		iErrorCode = GNMA_POINTER_ERR;
#ifdef NEVER
		psErrorText = ERAIcreateText("%s: GNMA_calc_amplitude_margin error.", __FUNCTION__);
		ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
		free(psErrorText);
		THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "freq_point value = %d, \
		magnitude value = %d, if_found = %d, phase = %d, ampl_mar = %d, ampl_freq = %d", freq_point,
		magnitude, if_found, phase, ampl_mar, ampl_freq);
#endif /* NEVER */
	}
	if(0 == iErrorCode)
	{
		if(nbr_fre_trace <=0 || sample_period < 4e-4 || bw <= 0/* || bw >=amp_stop_fr*/)
		{
			iErrorCode = GNMA_PARAM_ERR;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_amplitude_margin error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
			THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "nbr_fre_trace value = %d, \
			sample_period value = %e, bw = %e, amp_stop_fr = %e", nbr_fre_trace,
			sample_period, bw, amp_stop_fr);
#endif /* NEVER */
		}
	}
	if(0 == sim_mode)
	{
		if(0 == iErrorCode)
		{//�ҵ���ʼƵ�ʺ���ֹƵ�ʶ�Ӧ��index
			iStart = (int)(bw * (nbr_fre_trace -1) * 2 * sample_period);
			iStop = (int)(amp_stop_fr * (nbr_fre_trace -1) * 2 * sample_period) + 1;
		}
		if(0 == iErrorCode)
		{//�ҵ���λԣ�ȶ�Ӧ�����ϵ��±仯��index
			if( iStart < iStop)
			{
				iFlag = 1;
				for(i = iStart; i <= iStop; i++)
				{
					if(gnma_dbl_equal(phase[i], 0))
					{//�����ƵֵΪ��
						iAmpIndex = i;
						*if_found = 1;
						break;
					}
					else
					{//�����Ƶֵ��Ϊ��
						iFlag *= (int)(phase[i] / fabs(phase[i]));
						if(-1 == iFlag)
						{
							iAmpIndex = i;//��ʱ���Ϊ��λԣ��Ϊ��һ�θ���index
						//	printf("iAmpIndex = %d\n", iAmpIndex);
							*if_found = 1;
							break;
						}
					}
				}
			}
			else
			{
				iFlag = 1;
				for(i = iStart; i >= iStop; i--)
				{
					if(gnma_dbl_equal(phase[i], 0))
					{//�����ƵֵΪ��
						iAmpIndex = i;
						*if_found = 1;
						break;
					}
					else
					{//�����Ƶֵ��Ϊ��
						iFlag *= (int)(phase[i] / fabs(phase[i]));
						if(-1 == iFlag)
						{
							iAmpIndex = i;//��ʱ���Ϊ��λԣ��Ϊ��һ�θ���index
						//	printf("iAmpIndex = %d\n", iAmpIndex);
							*if_found = 1;
							break;
						}
					}
				}
			}
		}
		if(0 == iErrorCode && 0 == iAmpIndex)
		{
			*if_found = 0;
			iErrorCode = GNMA_SEARCH_FAIL;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_amplitude_margin error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
		if(0 == iErrorCode)
		{//��Ƶ��
			*ampl_freq = freq_point[iAmpIndex] -\
						phase[iAmpIndex] * (freq_point[iAmpIndex - 1] - freq_point[iAmpIndex]) / (phase[iAmpIndex - 1] - phase[iAmpIndex]);
		//	printf("*ampl_freq = %e\n", *ampl_freq);
			dTemp = *ampl_freq;
		}
		if(0 == iErrorCode)
		{//���ֵԣ��
			*ampl_mar = magnitude[iAmpIndex] + \
						(dTemp - freq_point[iAmpIndex]) * (magnitude[iAmpIndex - 1] - magnitude[iAmpIndex]) / (freq_point[iAmpIndex - 1] - freq_point[iAmpIndex]);
		//	printf("*ampl_mar = %e \n", *ampl_mar);
		}
	}
	else
	{
		//����ģʽ
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

