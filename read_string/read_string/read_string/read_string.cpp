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

	const char *filename = ".\\WH_lp1_scan_raw1.dat";//ע����ļ�Ҫ������ͬdebugͬһ���ļ�����
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
	//�������ַ�
	while(!feof(file))
	{
		str_result[i] = fgetc(file);
		printf("%c\n",str_result[i]);
		i++;
	}*/
	//����ڲ��������ݽ��и�ʽ����ȡ
	
	//������Ҫ�Ƚ��ļ���ʼ���ַ������ж�ȡ
	//ͬʱ��Ҫע��˴�������ַ�����һ��Ҫ�������е��ַ������� ����������ݶ�ȡ����
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
		fscanf(file,"%d\t%lf\t%d\n",&num[i],&position[i],&sensor[i]);//ת���ַ� �Զ�ת������һ���ַ���ʼλ��
		cout<<num[i]<<" "<<position[i]<<" "<<sensor[i]<<endl;
		i++;
	}

	/*���ַ���
	while(!feof(file))
	{
		fgets(str_result,100,file);
		printf("%s\n",str_result);
		i++;
	}	*/
	fclose(file);
	return 0;
}