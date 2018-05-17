// read_data_file.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define language 0	//0:language c;  1:language c++;

int _tmain(int argc, _TCHAR* argv[])
{
	if(language == 0)
	{
		FILE *ptr;									//定义一个文件指针
		const char *filename = ".\\read_data.txt"; //定义文件名字符串，注意该文件要放置在同debug同一个文件夹中，
		//ptr = fopen(filename,"r");					//将该文件名打开命令定义为指针ptr；
		ptr = fopen(filename,"w");
		int n = 1;
		cout<<"jinshaoxun"<<endl;
		fprintf(ptr,"%08d",n);
		//while(!feof(ptr))
		//{
		//	//fscanf(ptr,"%d",&n);
		//	printf("%d\n",n);
		//}
		fclose(ptr);
		system("pause");
	}

//下面是用 C++ 进行编写的读取文件；	
	if(language == 1)
	{
		//输入当前工程目录下的文件名
		string filename;
		cout<<"Please input the filename"<<endl;
		cin>>filename;

		//打开文件
		ifstream input_file(filename.c_str());

		//每次创建文件之后要进行判断该文件指针是否为空
		if(!input_file)
		{
			cout<<"failed"<<endl;
			return -1;
		}

		//采用向量和迭代的方式进行存储和输出数据；		
		vector<double> vector_data;
		double mid_data;
		while(!input_file.eof())
		{
			//这里是读文件，input_file = cin；
			input_file>>mid_data;
			if(input_file.eof()) 
			{
				break;
			}
			vector_data.push_back(mid_data);
		}
		
		//输出得到的数据
		int data_size,i;
		data_size = vector_data.size();
		//cout<<"data_size = "<<data_size<<endl;
		for(i = 0;i < data_size;i++)
		{
			cout<<"pid_in = "<<vector_data[i]<<endl;
		}

		//将读取到的数据写入到文件中
		cout<<"Begign to write to file "<<endl;
		string filename_write;
		cout<<"Please input the written filename (which you can specify it or already exit it)"<<endl;
		cin>>filename_write;
		
		//写数据文件
		ofstream out_file(filename_write.c_str());
		if(!out_file)
		{
			cout<<"Open the written file failed"<<endl;
			cout<<"Please check the filename or the file path"<<endl;
			exit(1);
		}
		//开始写数据
		for(i = 0; i < data_size;i++)
		{
			out_file<<vector_data[i]<<endl;
		}

		/*下面是使用数组的方式存储数据
		int data[100];		
		int i=0;
		while(!input_file.eof())
		{
			input_file>>data[i];
			cout<<"read data = "<<data[i]<<endl;
			i++;
		}
		*/
		system("pause");
	}
	return 0;
}

