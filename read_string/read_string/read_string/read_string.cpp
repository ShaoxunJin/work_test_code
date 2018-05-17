// read_data_file.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *file;
	char str_result[100];

	const char *filename = ".\\WH_lp1_scan_raw1.dat";//注意该文件要放置在同debug同一个文件夹中
	file = fopen(filename,"r");
	int n = 0;
	int i = 0;
	char *name = "jinshaoxun";
	cout<<name<<endl;

	if(NULL == file)
	{
		printf("open file error\n");
	}

	/*
	//读单个字符
	while(!feof(file))
	{
		str_result[i] = fgetc(file);
		printf("%c\n",str_result[i]);
		i++;
	}*/
	//针对内部具体数据进行格式化读取
	
	//这里需要先将文件开始的字符串进行读取
	//同时需要注意此处定义的字符串中一定要大于文中的字符串长度 否则后续数据读取错误
	char str[100];
	if(0 != fgets(str,10,file))
	{
		cout<<str<<endl;
	}

	int num[10];
	double position[10];
	int sensor[10];
	while(!feof(file))
	{
		fscanf(file,"%d\t%lf\t%d\n",&num[i],&position[i],&sensor[i]);//转义字符 自动转换到下一个字符起始位置
		cout<<num[i]<<" "<<position[i]<<" "<<sensor[i]<<endl;
		i++;
	}

	/*读字符串
	while(!feof(file))
	{
		fgets(str_result,100,file);
		printf("%s\n",str_result);
		i++;
	}	*/
	fclose(file);
	return 0;
}