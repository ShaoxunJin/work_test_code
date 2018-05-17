// PID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


int m_calculate_PID(double kp, double ki, double kd, int length,
					double sample_time, double pid_in[],double out_data_increment[], double out_data_absolute[])
{
	double p_out, i_out, d_out;
	double previous_pid_absolute = 0, pid_sum_absolute = 0;

	//位置式PID
	for(int j = 0;j < length; ++j)
	{
		pid_sum_absolute += pid_in[j];		
		p_out = kp * pid_in[j];
		i_out = ki * pid_sum_absolute * sample_time;
		d_out = kd *(pid_in[j] - previous_pid_absolute)/sample_time;

		previous_pid_absolute = pid_in[j];
		out_data_absolute[j] = p_out + i_out + d_out;
	}

	//增量式PID
	double delta[2001] = {0.0};
	for (int k = 0; k < length; ++k)
	{
		if(k == 0)
		{
			delta[k] = kp*pid_in[k] + ki*pid_in[k]*sample_time + kd*pid_in[k]/sample_time;
			out_data_increment[k] = delta[k];
		}
		else if (k == 1)
		{
			delta[k] = kp*(pid_in[k] - pid_in[k-1]) + ki*pid_in[k]*sample_time + kd*(pid_in[k] - 2*pid_in[k-1])/sample_time;
			out_data_increment[k] = out_data_increment[k-1] + delta[k];
		}
		if (k >= 2)
		{
			delta[k] = kp*(pid_in[k] - pid_in[k-1]) + ki*pid_in[k]*sample_time + kd*(pid_in[k] - 2*pid_in[k-1] + pid_in[k-2])/sample_time;
			out_data_increment[k] = out_data_increment[k-1] + delta[k];
		}
	}

	//将结果写入文件
	ofstream write_file("pid_result.txt");
	write_file<<"PID_Absolute"<<"\t"<<"PID_Increment"<<endl;

	for(int m = 0; m < length; m++)
	{
		write_file<<out_data_absolute[m]<<"\t"<<out_data_increment[m]<<endl;
	}
	
	system("pause");
	return 0;
}