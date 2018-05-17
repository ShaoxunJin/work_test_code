// hanning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include "smee_type.h"
#include "GNMA.h"
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <iostream>
using namespace std;

#define PI 3.141592653589793
#define NULL 0


int _tmain(int argc, _TCHAR* argv[])
{
	int fft_points = 2048;
	int iNbr_points = 2048;
	double hanning[2048];
	
	int i;

	//计算hanning 便于同matlab的进行比较；
	for(i = 0;i < fft_points; i++)
	{
		hanning[i] = (1.0 - cos(i* GNMA_PI * 2 / fft_points)) / 2;
	}

	//输出 hanning 值
	char *filename_write_hanning = ".\\hanning.txt";
	FILE *file_write_ptr_hanning = NULL;	
	file_write_ptr_hanning = fopen(filename_write_hanning,"w");
	if(file_write_ptr_hanning == NULL)
	{
		cout<<"Open file failed"<<endl;
	}

	for(i= 0 ;i < fft_points;i++)
	{
		fprintf(file_write_ptr_hanning,"%.25lf\n",hanning[i]);
		cout<<hanning[i]<<endl;
	}


	return 0;
}

