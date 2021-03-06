// notch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include "notch.h"
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
	ifstream input_file("in.txt");
	if(!input_file)
	{
		cout<<"Open the original data file failed"<<endl;
		system("pause");
		return -1;
	}

	//下面采用向量和迭代的方式进行存储和输出数据；
	vector<double> vector_in_data;
	double in_data;
	int i = 0;
	while(!input_file.eof())
	{	
		input_file>>in_data;
		if(input_file.eof())
			break;
		vector_in_data.push_back(in_data);
		//cout<<"i = "<<i<<" "<<in_data<<endl;
		i++;		
	}
		
	int data_size;
	data_size = vector_in_data.size();
	cout<<"data_size = "<<data_size<<endl;

	double input[50001];
	double result[50001];

	for(i = 0;i < data_size;i++)
	{
		input[i] = vector_in_data[i];
	}
	
	m_calculation(freq_zero, freq_pole, beta_zero, beta_pole,
				  sample_time, data_size, input, result);

	system("pause");
	return 0;
}