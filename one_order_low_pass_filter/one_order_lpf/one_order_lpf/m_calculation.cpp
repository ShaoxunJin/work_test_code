#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "one_order_lpf.h"
using namespace std;

int m_calculation(double Freq, double Sample_time, int length, double input_data[], double output_data[])
{
	double A,B;
	A = PI * Freq * Sample_time/(1 + PI * Sample_time * Freq);
	B = (Sample_time * PI *Freq - 1)/(1 + Sample_time * PI * Freq);

	for(int j = 0; j < length; j++)
	{
		if(j == 0)
		{
			output_data[j] = A * input_data[j]; 
			//cout<<"j = "<<j<<" "<<"input_data = "<<input_data[j]<<"  output_data = "<<output_data[j]<<endl;
		}
		else
		{
			output_data[j] = A * (input_data[j] + input_data[j-1]) - B * output_data[j-1];
			//cout<<"j = "<<j<<" "<<"input_data = "<<input_data[j]<<"  output_data = "<<output_data[j]<<endl;
		}
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
