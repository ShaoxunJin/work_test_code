#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include "notch.h"
using namespace std;

int m_calculation(double Freq_zero, double Freq_pole, double Beta_zero, double Beta_pole,
				  double Sample_time, int length, double input_data[], double output_data[])
{
	double B0,B1,B2,A1,A2,F_zero,F_pole;
	F_zero = PI * Sample_time * Freq_zero;
	F_pole = PI * Sample_time * Freq_pole;
	B0 = (Freq_pole*Freq_pole)*(1+2*F_zero*Beta_zero+F_zero*F_zero)/(Freq_zero*Freq_zero)/(1+2*F_pole*Beta_pole+F_pole*F_pole);
	B1 = (Freq_pole*Freq_pole)*(2*F_zero*F_zero-2)/(Freq_zero*Freq_zero)/(1+2*F_pole*Beta_pole+F_pole*F_pole);
	B2 = (Freq_pole*Freq_pole)*(1-2*F_zero*Beta_zero+F_zero*F_zero)/(Freq_zero*Freq_zero)/(1+2*F_pole*Beta_pole+F_pole*F_pole);
	A1 = (2*F_pole*F_pole-2)/(1+2*F_pole*Beta_pole+F_pole*F_pole);
	A2 = (1-2*F_zero*Beta_pole+F_pole*F_pole)/(1+2*F_pole*Beta_pole+F_pole*F_pole);

	double X1,X2;
	int time = 1;
	//考虑到simulink模型中设置了5个notch模型
	while(time < 5)
	{
		for(int j = 0; j < length; j++)
		{
			//第一次计算
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
		}
		//第一次循环结束之后将output_data值赋给input_data重新进行计算，总共后续还有计算4次
		for(int n = 0; n < length; n++)
		{
			input_data[n] = output_data[n];
		}

		time++;
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
