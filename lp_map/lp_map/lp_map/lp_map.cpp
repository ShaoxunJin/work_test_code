// lp_map.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include"map.h"
//#include<vector>
//#include<algorithm>
//#include<functional>
#include<stdio.h>
#include<iostream>
#define my_string(s) #s
#define connect(x,y) x##y
#include<time.h>
#include "enum2str.h"

using namespace std;

int main(int argv,char argc[])
{
	int rtn = OK;
	const char *filename = ".\\WC_scan_raw.dat";
	const char *file_matrix_name = ".\\WC_scan_raw_.dat";
	const char *str = __FILE__;
	FILE *file = NULL;
	FILE *file_matrix = NULL;

	double matrix[2000];
	double actual_position[MAX_DATA_LENGTH];
	double actual_sn[MAX_DATA_LENGTH];
	WHLP_SLOT_INFO_ENUM cur_slot[WH4A_MAX_SLOT_NBR];

	int num = 0;
	char *ptr = NULL;
	char buf[100];
	time_t current_time;	//显示系统自定义时刻到当前时刻的时间间隔
	current_time = time(0);
	cout<<"current_time : sec = "<<current_time<<endl;
	file = fopen(filename,"r");
	file_matrix = fopen(file_matrix_name,"r");

	if(NULL == file)		//如果打开文件失败 则报错
	{
		cout<<"open file error!"<<endl;
		rtn = ERROR;
	}
	if(NULL == file_matrix)
	{
		cout<<"open matrix_file error!"<<endl;
		
	}

	if(0 != (ptr = fgets(buf,100,file)))	//这里是为了获取dat文件前面的字符串，99个加上\0 文件的指针自动指向下一行
	{
		cout<<"buf = "<<buf<<endl;
	}

	int i = 0;
	while(EOF != fscanf(file,"%d\t%lf\t%lf\n",&num,&actual_position[i],&actual_sn[i]))
	{
		i++;
		cout<<num<<endl;
	}
	
	int j = 0;
	double a,b,c,d = 0.0;
	while (EOF != fscanf(file_matrix,"%lf\t%lf\n", &a, &b))
	{
		cout<<"a = "<<a<<"b = "<<b<<endl;
		++j;
		
	}
	for (int m = 0; m < 4; ++m)
	{
		//cout<<"matrix["<<m<<"] = "<<matrix[m]<<endl;
	}

	//for(int k = 0;k < 10;k++)
	//{
	//	cout<<"actual_position["<<k<<"] = "<<actual_position[k]<<"actual_sn["<<k<<"] = "<<actual_sn[k]<<endl;
	//}
	//cout<<"actual_position["<<1219<<"] = "<<actual_position[1218]<<"actual_sn["<<1219<<"] = "<<actual_sn[1218]<<endl;
	//cout<<"actual_position["<<num<<"] = "<<actual_position[num - 1]<<"actual_sn["<<num<<"] = "<<actual_sn[num - 1]<<endl;

	cout<<"num = "<<num<<endl;

	m_resolve_slot_state(num,actual_position,actual_sn,cur_slot);

	for(int j = 0;j<25;j++)
	{
		if(cur_slot[j] == 1)
		cout<<"slot["<<j<<"]"<<"="<<cur_slot[j]<<" "<<enum2str(cur_slot[j])<<endl;
	}
	cout<<"*****************分界线********************"<<endl;
	for(int j = 0;j<25;j++)
	{

		if(cur_slot[j] != 1)
		cout<<"slot["<<j<<"]"<<"="<<cur_slot[j]<<" "<<enum2str(cur_slot[j])<<"     please check it"<<endl;
	}

	cout<<my_string(abcdef)<<endl;
	int xy = 10;
	cout<<connect(x,y)<<endl;
	cout<<"line"<<__LINE__<<" "<<__FILE__<<" "<<__DATE__<<" "<<__TIME__<<endl;
	cout<<str<<endl;
	fclose(file);
	file = NULL;
	//while(1);
	system("pause");
	return 0;
}