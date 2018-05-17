// write_to_file.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>	//用于文件操作
#include "read_file.h"

using namespace std;

#define aaaa 10000

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *ptr_file;
	const char *filename = ".\\write_data.txt";
	ptr_file = fopen(filename, "w");
	int a[4] = {1,2,3};
	if(ptr_file == NULL)
	{
		printf("Open file failed\n");
	}
	
	//注意需要写入数据的格式和指定的写入的格式要统一；
	for(int i = 0; i < 3;i++)
	{
		fprintf(ptr_file,"%4d\n",a[i]);
		cout<<a[i]<<endl;
	}

	if(NULL != ptr_file)
	{
		fclose(ptr_file);
		ptr_file = NULL;
	}
	//
	cout<<"FileName :"<<endl;
	char OutFileName[100];
	cin>>OutFileName;
	ofstream OutFile(OutFileName, ios::app);
	if(!OutFileName)
	{
		cerr<<"This file not exist !"<<endl;
	}
	for (int i = 0; i < 3; i++)
	{
		OutFile<<a[i]<<endl;
	}
	OutFile.close();

	cout<<"a = "<<a<<endl;

	read_from_file();

	system("pause");
	return 0;
}

