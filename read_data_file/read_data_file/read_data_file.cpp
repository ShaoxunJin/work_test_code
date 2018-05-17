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
		FILE *ptr;									//����һ���ļ�ָ��
		const char *filename = ".\\read_data.txt"; //�����ļ����ַ�����ע����ļ�Ҫ������ͬdebugͬһ���ļ����У�
		//ptr = fopen(filename,"r");					//�����ļ����������Ϊָ��ptr��
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

//�������� C++ ���б�д�Ķ�ȡ�ļ���	
	if(language == 1)
	{
		//���뵱ǰ����Ŀ¼�µ��ļ���
		string filename;
		cout<<"Please input the filename"<<endl;
		cin>>filename;

		//���ļ�
		ifstream input_file(filename.c_str());

		//ÿ�δ����ļ�֮��Ҫ�����жϸ��ļ�ָ���Ƿ�Ϊ��
		if(!input_file)
		{
			cout<<"failed"<<endl;
			return -1;
		}

		//���������͵����ķ�ʽ���д洢��������ݣ�		
		vector<double> vector_data;
		double mid_data;
		while(!input_file.eof())
		{
			//�����Ƕ��ļ���input_file = cin��
			input_file>>mid_data;
			if(input_file.eof()) 
			{
				break;
			}
			vector_data.push_back(mid_data);
		}
		
		//����õ�������
		int data_size,i;
		data_size = vector_data.size();
		//cout<<"data_size = "<<data_size<<endl;
		for(i = 0;i < data_size;i++)
		{
			cout<<"pid_in = "<<vector_data[i]<<endl;
		}

		//����ȡ��������д�뵽�ļ���
		cout<<"Begign to write to file "<<endl;
		string filename_write;
		cout<<"Please input the written filename (which you can specify it or already exit it)"<<endl;
		cin>>filename_write;
		
		//д�����ļ�
		ofstream out_file(filename_write.c_str());
		if(!out_file)
		{
			cout<<"Open the written file failed"<<endl;
			cout<<"Please check the filename or the file path"<<endl;
			exit(1);
		}
		//��ʼд����
		for(i = 0; i < data_size;i++)
		{
			out_file<<vector_data[i]<<endl;
		}

		/*������ʹ������ķ�ʽ�洢����
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

