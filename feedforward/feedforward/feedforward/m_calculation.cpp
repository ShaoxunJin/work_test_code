#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include "feedforward.h"
using namespace std;

int m_calculation(double Sample_time, double Ts, double Tao,int length, double input_data[], double output_data[])
{
	double B0,B1,A1;
	A1 = 1;
	B0 = (Sample_time - 2*(2*Ts - Tao))/Sample_time;
	B1 = (Sample_time + 2*(2*Ts - Tao))/Sample_time;

	double X;
	
	for(int j = 0; j < length; j++)
	{
		if(j == 0)
		{
			X = 0;
			output_data[j] = 2*input_data[j]/Sample_time;
		}
		else
		{
			output_data[j] = 2*(input_data[j] - input_data[j-1])/Sample_time - output_data[j-1];
			//output_data[j] = input_data[j]/Sample_time - input_data[j-1]/Sample_time ;
		}
		cout<<"j = "<<j<<" Input = "<<input_data[j]<<" result = "<<output_data[j]<<endl;
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