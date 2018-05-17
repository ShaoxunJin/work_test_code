#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include "m_calculation.h"
using namespace std;

int  m_calculation(double Freq, double Damping, double Sample_time, int length, double input_data[], double output_data[])
{
	double M,N,A1,A2,B0,B1,B2;
	M = 2 * PI * Freq;
	N = 2 * Damping;

	B0 = (M*M * Sample_time*Sample_time)/(4 + M*M * Sample_time*Sample_time);
	B1 = (2 * M*M * Sample_time*Sample_time)/(4 + M*M * Sample_time*Sample_time);
	B2 = B0;
	A1 = (2*M*N*Sample_time + 2*M*M * Sample_time*Sample_time - 8)/(4 + M*M * Sample_time*Sample_time);
	A2 = (M*M * Sample_time*Sample_time - 2*M*N*Sample_time +4)/(4 + M*M * Sample_time*Sample_time);
	
	double X1,X2;
	for(int j = 0; j < length; j++)
	{
		if(j == 0)
		{
			X2 = 0; X1 = 0;
			output_data[j] = B0 * input_data[j] + X1;
		}
		else if(j == 1)
		{
			X2 = 0;
			X1 = B1*input_data[j-1] - A1*output_data[j-1] +X2;
			output_data[j] = B0*input_data[j] + X1;
		}
		else
		{
			X2 = B2*input_data[j-2]  - A2*output_data[j-2];		
			X1 = B1*input_data[j-1] - A1*output_data[j-1] +X2;
			output_data[j] = B0*input_data[j] + X1;
		}
		cout<<"j = "<<j<<"  "<<output_data[j]<<endl;
	}
	
	//将结果写入到文件中
	ofstream out_file("out.txt");
	if(!out_file)
	{
		cout<<"Open the file failed "<<endl;
		cout<<"Check the filename or the filepath"<<endl;
	}

	for(int m = 0; m < length; m++)
	{
		out_file<<output_data[m]<<endl;
		//cout<<"m = "<<m<<" "<<output_data[m]<<endl;
	}
	system("pause");
	return 0;
}
