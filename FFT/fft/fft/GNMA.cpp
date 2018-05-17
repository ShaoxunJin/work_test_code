/**********************************
* Copyright (C) 2009,  上海微电子装备有
* All rights reserved.
*  产品号  : SS A600/102
*  所属组件 :  GN
*  模块名称 :  GNMA
*  文件名称 :  GNMA.cpp
*  概要描述 :  通用数据库
*  历史记录 :
*  版本    日期     作者    内容
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
* Description:   比较两个double型的数是否相等
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
* Description:   本fft算法根据清华版《数字信号处理教程》第二版(程佩青著)改写(修改了它的部分错误)
 	用雷格算法实现位倒序
摘自清华版《数字信号处理教程》第二版(程佩青著)第185页--实现反向进位加法（倒位序二进制数的下面一个数是上面一个数的最高位加1并由高位向低位进位而得到的）
实现方法：x（i）表示存放原自然顺序输入数据的内存单元，x（j）表示存放倒位序数的内存单元。i，j都是从0开始。
若已知某个倒位序数j，要求下一个倒位序数，则应先判断j的最高位是否为0，这可以与k=N/2比较，因为N/2的二进制表示肯定是“10000...”。
如果k>j，说明j的最高位为0，只要把该位变为1（j加上N/2即可），就得到了下一个倒位序数（x（i+1）与x（j）交换）。
如果k<=j，说明j的最高位为1，只要把该位变为0（j-N/2即可）；
然后还需判断次高位（与N/4比较），若次高位为0，这将该位变为1（j+N/4即可），其他位不变，则得到下一个倒位序数，若次高位是1，这将该位变为0（j-N/4即可），然后还需判断再下一位，
这可以与k=N/8比较，.......依次进行，总会碰到某位为0，这是把0改为1，得到下一个倒位序数。求出新的倒位序数j以后，仅当i<j时进行变址交换。
注意x（0）和x（N-1）是不需要进行变址交换的，因为其和原自然顺序是一样的。
======================================================*/
static int bit_invert(GNMA_complex_type psInput[], int iNbr_fft)
{
	int iErrorCode = 0;
//	int iErrorLink[2] = {0, 0};
//	char *psErrorText = NULL;

	GNMA_complex_type sSwap = {0.0, 0.0};

	int NV2 = iNbr_fft / 2;//倒序j用来与该值相比较
	//int NM1 = iNbr_fft - 1;//可变址的数据个数,第0个和第iNbr_fft-1个不用倒位变址
	int i = 0;//原序
	int j = 0;//对应的倒序
	int k = 0;//表示某位为1
	//NM1 = NM1;//暂时不用，为避免警告而写

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
		{//只有原序小于倒位序数时才交换
			//printf("%d-->%d\n",i,j);
			sSwap = psInput[j];
			psInput[j] = psInput[i];
			psInput[i] = sSwap;

		}
		//下面是求下一个序列
		k = NV2;//第一次为N/2 表示最高位为1
		while(j >= k)
		{//代表倒位序数j某位为1，则向低位进位
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
*   -input:  	int iNbr_fft,  输入数据的个数，为2的幂次方
			GNMA_complex_type *psInput_str, 输入数据
			GNMA_fourier_direction eFourier_dir  FFT或者iFFT
*   -input/output:  GNMA_complex_type psInput[]
* -output:  GNMA_complex_type *psOut_str,  FFT结果
* Returns:   0/Error
* Description: fft DIT 基2算法
摘自清华版《数字信号处理教程》第二版(程佩青著)第185页---L级递推计算（2^L =N）
特点：
1：每级有N/2个碟形结，第一级的N/2个碟形结都是同一种碟形运算，也就是说，其系数都相同，为W（0，N）=exp（-2pi*0/N）。
   第二级的N/2个碟形结共有两种碟形运算，一种系数为W（0，N），一种系数为W（2，N），每种各有N/4个碟形结。这样可看出，
   第L级的N/2个碟形结共有2^(L-1)=N/2种碟形运算，即有N/2个不同的运算系数，分别为W(0,N),W(1,N),……，W(N/2-1，N),也就是说，
   第M级有2^(M-1)种蝶形运算（M= 1，2，……，L），他们是W（k，2^M），k=0，1，……，2^(M-1)-1。
2：由最后一级每向前推进一级，则系数取后级系数中偶数序数的那一半。
3：蝶形结两个节点的间距为2^(M-1),M为所在的级数,也就是每向前推进一级,间距就变成原间距的1/2。
整个过程分三个循环递推：
外层的一个循环控制L（2^L=N）级的顺序运算，内层的两个循环控制同一级（M相同）各蝶形结的运算，其中最内一层循环控制同一种（即W（r，N）中r相同）蝶形结的运算，
而中间一层循环控制不同种（即W（r，N）中r不同）蝶形结的运算。I，IP是一个蝶形结的两个节点。
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

	int m = 0;//m = 1,2,…,L, L = Log(2,N),蝶形运算中的级数，循环变量
	int j = 0;
	int i = 0;//蝶形结中的第一个节点
	int ip = 0;//蝶形结中的第二个节点
	int n = iNbr_fft;
	int L = 1;//级数
	int nbr_butfly = 1;//蝶形结的类型个数，同一蝶形结两点之间的间距
	int dist_betwn_butfly = 2;//蝶形结之间的距离
	double a = 0.0;
	double b = 0.0;
	double pi = 4.0*atan(1.0);
	GNMA_complex_type W = {1.0, 0.0};//蝶形算子
	GNMA_complex_type Wl = {0.0, 0.0};//蝶形算子增量
	GNMA_complex_type sTemp = {0.0, 0.0};

	//用递推方法计算fft
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

	//付利叶反变换，先输入取共轭，再计算fft，最后对结果取共轭，并乘以1/N
	if((INVERT == eFourier_dir) && (0 == iErrorCode))
	{

		for(i = 0; i < n; i++)
		{
			psInput_str[i].Im *= (-1);
		}
	}

	//计算付利叶算法的级数
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

	//对输入数据进行位倒叙
	if(0 == iErrorCode)
	{
		iErrorCode = bit_invert(psInput_str, iNbr_fft);
	}

	if(0 == iErrorCode)
	{

		for(m = 1; m <= L; m++)
		{//级数循环
			W.Re = 1; W.Im = 0; // W0

			//exp(pi/l)
			Wl.Re = cos(pi / pow(2, (double)m-1.0));
			Wl.Im = -sin(pi / pow(2, (double)m-1.0));// Wl, W = W0*Wl
			for(j = 0; j < nbr_butfly; j++)
			{//不同蝶形结，系数不同的蝶形结，步进值为1。
				for(i = j; i + nbr_butfly < n; i += dist_betwn_butfly)//教材中第二个参数是：i < n
				{//相同蝶形结运算，步进值为蝶形结间距，dist_betwn_butfly=2^M
					ip = i + nbr_butfly;

					//复数运算
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

				//系数递推公式
				//W = W*Wl;

				a = W.Re * Wl.Re - W.Im * Wl.Im;
				b = W.Re * Wl.Im + W.Im * Wl.Re;
				W.Re = a;
				W.Im = b;

			}
			dist_betwn_butfly *= 2;//初始等于2
			nbr_butfly *= 2;		 //初始等于1
		}
	}

	//如果是付利叶反变换，则取共轭、乘以1/N
	if((0 == iErrorCode) && (INVERT == eFourier_dir))
	{
		for(i = 0; i < n; i++)
		{
			psInput_str[i].Im *= (-1 / iNbr_fft);//取共轭
			psInput_str[i].Re *= 1 / iNbr_fft;	//1/N
		}//n
	}

	//如果第三个参数不为空，则给它结果
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
* Description:   本函数配合GNMA_spectrum函数，其功能是：*nr_freq_points输出为N＋1，其中N是所有小于 nr_points / nr_frames 的
   形如 2^X 的数中最大的。*nr_freq_points 是 GNMA_spectrum 所输出的数组的大小。
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
*   -input:  	int iNbr_points,  数据个数
			int iNbr_frames,  数据帧数
			int iNbr_freq_points, 频率点数
			double dSample_period, 采样周期
			double *pdX, 第一路输入数据
			double *pdY 第二路输入数据
*   -input/output:
* -output:  	double *pdFreqs,  频率点数组
			double *pdPxx,  第一路数据的功率谱自谱数组
			double *pdPyy,  第二路数据功率谱自谱数组
			GNMA_complex_type *psPxy 两路数据功率谱互谱数组
* Returns:   0
* Description:   本函数现对输入数据加窗截断,再进行傅立叶变换,最后计算他们的自谱和互谱
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
	//int frame = iNbr_frames;//付利叶变换的帧
	int i = 0;
	int j = 0;
	double dBit = 0.0;
	double *hanning = NULL;
	GNMA_complex_type *x_win = NULL;
	GNMA_complex_type *y_win = NULL;
	GNMA_complex_type *x_fft = NULL;
	GNMA_complex_type *y_fft = NULL;
	if(0 == iErrorCode)
	{//判断iNbr_points，iNbr_frames，iNbr_freq_points，dSample_period的有效性
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
	{//验证fft_points是否为2的N次幂
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

	//给他们分配内存
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

	//对输入的pdX、pdY加窗
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

		//对不满足fft_points的数据，进行补0
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

	//输出hanning
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

	//输出x_win
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

	//对加窗后的数据进行fft计算
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
	
	
	//输出x_fft
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
	//输出y_fft
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

	//根据公式计算功率谱,按帧进行求平均
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

	//输出pxx
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

	//输出pyy
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

	//输出pxy
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
*   -input:  	int iNbr_freq_points,  频率点个数
			double *pdPxx, 第一路数据的自谱
			double *pdPyy, 第二路数据的自谱
			GNMA_complex_type *psPxy,两路数据的互谱
*   -input/output:
* -output:  	double *pdMagnitude, 传递函数的幅值
			double *pdPhase,  相位
			double *pdCoherence 相关性
* Returns:   0
* Description:   根据两路数据的自谱和互谱,计算他们的传递函数伯特曲线
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

			//相关性(实部的平方+虚部的平方)/自谱的乘积
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
		//幅值
		pdMagnitude[i] = 20*log10(dTemp_amp);

		//相位
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
			{	//atan2的范围是[-pi，pi)。而A公司用的范围是[-2pi，2pi)。
				//通过数据发现，A公司对数据做了处理，
				//即将atan2求出的值与前一值的差和atan2在[-2pi，2pi)内的另一值与前一值的差比较。
				//如果这个差值相等，则取atan2求得值
				//如果前者大于后者，则取atan2在[-2pi，2pi)内的另一值。
				//如果后者的差值大于540，也取atan2在[-2pi，2pi)内的另一值。
				//经验证，计算结果和A公司一致，至于原因，有待考证。
				//by 郑教增20080818
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

	//输出幅值
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

	//输出相位
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

	//输出相关性
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
*   -input:  	double *input, 数据
			int input_size, 数据长度
			int filter_window, MA的窗长度,前面filter_window/2, 当前点，后面filter_window/2-1
*   -input/output:
* -output:  	double *mov_avg,  MA  滑动平均
			double *mov_std_dev MSD
* Returns:   0
* Description:   根据两路数据的自谱和互谱,计算他们的传递函数伯特曲线
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
		//输入有效性判断
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
			//内存判断
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
*   -input:  	double *pdData,数据首地址
			int iNumber, 数据个数
			int iSizeOfItem  数据所属类型的大小
*   -input/output:
* -output:  	double *pdMean,  均值
			double *pdStdDev 方差
* Returns:   0
* Description:   计算数组的平均值,和方差
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
*   -input:  	double *pdData,数据首地址
			int iNumber, 数据个数
			int iSizeOfItem  数据所属类型的大小
*   -input/output:
* -output:  	double *pDPeak  峰值
* Returns:   0
* Description:   计算数组的峰值
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
*   -input:  	double *pdData,数据首地址
			int iNumber, 数据个数
			int iSizeOfItem  数据所属类型的大小
*   -input/output:
* -output:  	double *pdMax  最大值
* Returns:   0
* Description:   计算数组的最大值
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
*   -input:  	double *pdData,数据首地址
			int iNumber, 数据个数
			int iSizeOfItem  数据所属类型的大小
*   -input/output:
* -output:  	double *pdMin  最小值
* Returns:   0
* Description:   计算数组的最小值
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
*   -input:  	double *pdData,数据首地址
			int iNumber, 数据个数
			int iSizeOfItem  数据所属类型的大小
*   -input/output:
* -output:  	double *pdMean,  均值
			double *pdStdDev,  方差
			double *pdPeak, 峰值
			double *pdMin  最小值
			double *pdMax,  最大值
			double *pdMean3Sigma
* Returns:   0
* Description:   计算数组的统计值
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
*   -input: 	int sim_mode,  仿真模式
			double *freq_point 频率点
			 double *magnitude 幅值数组
			 int nbr_fre_trace,频率点个数
			 double sample_period, 采样周期
			 double start_fr 搜索起始频率
			 double stop_fr 搜索终止频率
*   -input/output:
* -output:  	 int *if_found,是否找到
			double *bw/带宽值
* Returns:   0
* Description:   搜索带宽大小，即幅值大小穿过零点对应的频率值
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
	//根据开始频率点和结束频率点计算出start_index,stop_index
	/************************************/
		if(0 == iErrorCode)
		{
			iStartIndex = (int)(start_fr * (nbr_fre_trace - 1) * 2 * sample_period);
			//printf("start_index = %d \n",iStartIndex);
			iStopIndex = (int)(stop_fr * (nbr_fre_trace - 1) * 2 * sample_period)+1;
			//printf("stop_index = %d \n",iStopIndex);
		}
	/**************************************/
	//从start_index的幅值开始寻找从正穿越到负的index-1，和index
	/******************************************************/
		iTemp = 1;
		for (i = iStartIndex; i <= iStopIndex && 0 == iErrorCode; i++)
		{
			if(gnma_dbl_equal(magnitude[i], 0))
			{//如果幅频值为零
				iBwIndex = i;
				*if_found = 1;
				break;
			}
			else
			{//如果幅频值不为零
				iTemp *= (int)(magnitude[i] / fabs(magnitude[i]));
				if(-1 == iTemp)
				{	//此时所对应的幅值为首个负值。已找到
					iBwIndex = i;
				//	printf("iBwIndex = %d \n",iBwIndex);
					*if_found = 1;
					break;
				}
			}
		}
		if(0 == iBwIndex && 0 == iErrorCode)
		{//没有找到带宽频率点
			*if_found = 0;
			iErrorCode = GNMA_SEARCH_FAIL;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_bandwidth error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
	/*****************************************/
	//根据index-1，index，寻找对应的频率点，对这两个频率斜线交零点。得到带宽频率点
	/***************************************************/
		if(0 == iErrorCode && 1 == *if_found)
		{
			*bw = freq_point[iBwIndex - 1] - \
				 magnitude[iBwIndex - 1] * (freq_point[iBwIndex] - freq_point[iBwIndex - 1]) / (magnitude[iBwIndex] - magnitude[iBwIndex - 1]);
		}
	}
	else
	{
		//仿真模式
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

/** ======================================================
* Include:
* Function: GNMA_calc_bandwidth
* Parameters:
*   -input: 	int sim_mode,  仿真模式
			double *freq_point 频率点
			 double *magnitude 幅值数组
			 int nbr_fre_trace,频率点个数
			 double sample_period, 采样周期
			 double start_fr 搜索起始频率
			 double stop_fr 搜索终止频率
*   -input/output:
* -output:  	 int *if_found,是否找到
			double *ph_mar 相位裕度
			double *ph_fre 相位裕度对应的频率值
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
	//根据开始频率点和结束频率点计算出start_index,stop_index
	/************************************/
		if(0 == iErrorCode)
		{
			iStartIndex = (int)(start_fr * (nbr_fre_trace - 1) * 2 * sample_period);
			//printf("start_index = %d \n",iStartIndex);
			iStopIndex = (int)(stop_fr * (nbr_fre_trace - 1) * 2 * sample_period)+1;
			//printf("stop_index = %d \n",iStopIndex);
		}
	/**************************************/
	//从start_index的幅值开始寻找从正穿越到负的index-1，和index
	/******************************************************/
		iTemp = 1;
		for (i = iStartIndex; i <= iStopIndex && 0 == iErrorCode; i++)
		{
			if(gnma_dbl_equal(magnitude[i], 0.0))
			{//如果幅频值为零
				iBwIndex = i;
				*if_found = 1;
				break;
			}
			else
			{//如果幅频值不为零
				iTemp *= (int)(magnitude[i] / fabs(magnitude[i]));
				if(-1 == iTemp)
				{	//此时所对应的幅值为首个负值。已找到
					iBwIndex = i;
				//	printf("iBwIndex = %d \n",iBwIndex);
					*if_found = 1;
					break;
				}
			}
		}
		if(0 == iBwIndex && 0 == iErrorCode)
		{//没有找到带宽频率点
			*if_found = 0;
			iErrorCode = GNMA_SEARCH_FAIL;
#ifdef NEVER
			psErrorText = ERAIcreateText("%s: GNMA_calc_phase_margin error.", __FUNCTION__);
			ERAIlogError(iErrorCode, 0, psErrorText, __FILE__, __LINE__);
			free(psErrorText);
#endif /* NEVER */
		}
	/*****************************************/
	//根据index-1，index，寻找对应的频率点，对这两个频率斜线交零点。得到带宽频率点
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
		{//找到带宽了，就要计算相频裕度值
			*ph_mar = phase[iBwIndex] + \
						(dF - freq_point[iBwIndex]) * (phase[iBwIndex - 1] - phase[iBwIndex]) / (freq_point[iBwIndex - 1] - freq_point[iBwIndex]);
			//printf("phase[%d] = %e \n", iBwIndex, phase[iBwIndex]);
			//printf("phase[%d] = %e \n", iBwIndex-1, phase[iBwIndex - 1]);
		}
	}
	else
	{
		//仿真模式
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}
/** ======================================================
* Include:
* Function: GNMA_calc_amplitude_margin
* Parameters:
*   -input: 	int sim_mode,  仿真模式
			double *freq_point 频率点
			 double *magnitude 幅值数组
			 int nbr_fre_trace,频率点个数
			 double sample_period, 采样周期
			double bw,做为启始频率
			double amp_stop_fr 终止频率
*   -input/output:
* -output:  	 int *if_found,是否找到
			double *ampl_mar幅值裕度
			double *ampl_freq 幅值裕度对应的频率值
* Returns:   0
* Description:
==============================================================*/
extern int  GNMA_calc_amplitude_margin( int sim_mode,  double *freq_point/*array*/,
									   double *magnitude/*array*/,  double *phase,
									   int nbr_fre_trace, double sample_period,
									   double bw/*arg60,做为启始频率*/,
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
		{//找到起始频率和终止频率对应的index
			iStart = (int)(bw * (nbr_fre_trace -1) * 2 * sample_period);
			iStop = (int)(amp_stop_fr * (nbr_fre_trace -1) * 2 * sample_period) + 1;
		}
		if(0 == iErrorCode)
		{//找到相位裕度对应的零上到下变化的index
			if( iStart < iStop)
			{
				iFlag = 1;
				for(i = iStart; i <= iStop; i++)
				{
					if(gnma_dbl_equal(phase[i], 0))
					{//如果相频值为零
						iAmpIndex = i;
						*if_found = 1;
						break;
					}
					else
					{//如果相频值不为零
						iFlag *= (int)(phase[i] / fabs(phase[i]));
						if(-1 == iFlag)
						{
							iAmpIndex = i;//此时这个为相位裕度为第一次负的index
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
					{//如果相频值为零
						iAmpIndex = i;
						*if_found = 1;
						break;
					}
					else
					{//如果相频值不为零
						iFlag *= (int)(phase[i] / fabs(phase[i]));
						if(-1 == iFlag)
						{
							iAmpIndex = i;//此时这个为相位裕度为第一次负的index
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
		{//求频率
			*ampl_freq = freq_point[iAmpIndex] -\
						phase[iAmpIndex] * (freq_point[iAmpIndex - 1] - freq_point[iAmpIndex]) / (phase[iAmpIndex - 1] - phase[iAmpIndex]);
		//	printf("*ampl_freq = %e\n", *ampl_freq);
			dTemp = *ampl_freq;
		}
		if(0 == iErrorCode)
		{//求幅值裕度
			*ampl_mar = magnitude[iAmpIndex] + \
						(dTemp - freq_point[iAmpIndex]) * (magnitude[iAmpIndex - 1] - magnitude[iAmpIndex]) / (freq_point[iAmpIndex - 1] - freq_point[iAmpIndex]);
		//	printf("*ampl_mar = %e \n", *ampl_mar);
		}
	}
	else
	{
		//仿真模式
	}
	//THAI_Trace("TM", THAI_TRACE_INT, __FUNCTION__, "<(0x%x)", iErrorCode);
	return iErrorCode;
}

