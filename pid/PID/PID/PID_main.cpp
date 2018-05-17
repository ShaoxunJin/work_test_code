// PID.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "PID.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//输入当前工程目录下的文件名
	/*
	string filename;
	cout<<"Please input the filename"<<endl;
	cin>>filename;
	*/

	//打开文件
	ifstream input_file("pid_in.txt");
	if(!input_file)
	{
		cout<<"failed"<<endl;
		system("pause");
		return -1;
	}

	//下面采用向量和迭代的方式进行存储和输出数据；
	vector<double> vector_pid_in_data;
	double pid_in_data;
	int i = 0;
	while(!input_file.eof())
	{	
		input_file>>pid_in_data;
		if(input_file.eof())
			break;
		vector_pid_in_data.push_back(pid_in_data);
		//cout<<"i = "<<i<<" "<<pid_in_data<<endl;
		i++;		
	}
		
	int data_size;
	data_size = vector_pid_in_data.size();
	cout<<"data_size = "<<data_size<<endl;
	
	double result_increment[2001];
	double result_absolute[2001];
	double input[2001];
	for(i = 0;i < data_size;i++)
	{
		input[i] = vector_pid_in_data[i];
	}

	double sample_time = 0.005;
	m_calculate_PID(0,0,5,data_size, sample_time, input, result_increment, result_absolute);

	/*
	for(i = 0;i < data_size;i++)
	{
		cout<<"pid_in = "<<vector_data[i]<<endl;
	}
	*/
	//pid_out calculation


	system("pause");
	return 0;
}

 