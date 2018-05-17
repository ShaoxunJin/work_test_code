// fft.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "GNMA.h"
#include "WRGN_if.h"
#include "WRGN_tc.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int iErrorCode = OK;
	int num;
	double inputdata[2048], outputdata[2048];
	int i_data = 0;
	int error_code;

	//��ȡ���������ļ�
	const char *filename_read = ".\\tf_test_data.txt";
	const char *str = __FILE__;
	FILE *file = NULL;
	file = fopen(filename_read,"r");
	if(NULL == file)
		{
			cout<<"open file error"<<endl;
			iErrorCode = 1;
		}

	while(EOF != fscanf(file,"%d\t%lf\t%lf\n", &num, &inputdata[i_data], &outputdata[i_data]))
		{
			i_data++;
		}

	int nbr_freq_points;				//Ƶ�ʵ����
	double sample_period = 0.0004;

	//����Ƶ�ʵ���
	error_code = GNMA_freq_size(num+1, 1, &nbr_freq_points);

	//�������������֮��Ӧ���Ǽ���Ƶ��
	int nbr_frames = 1;
	double pdFreqs[1025];
	double pdPxx[1025];
	double pdPyy[1025];
	GNMA_complex_type psPxy[1025];
	error_code = GNMA_spectrum(num+1, nbr_frames, nbr_freq_points, sample_period,inputdata,outputdata,
								pdFreqs, pdPxx, pdPyy, psPxy);
	
	//���׺ͻ��׼�����ϣ�������Խ��д��������ȡ��Ƶ����Ƶ�Լ�����ԣ�
	double pdMagnitude[1025];
	double pdPhase[1025];
	double pdCoherence[1025];
	error_code = GNMA_transfer(nbr_freq_points, pdPxx, pdPyy, psPxy,
							   pdMagnitude, pdPhase, pdCoherence);

	cout<<error_code<<endl;
	return 0;
}