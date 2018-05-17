#include "stdafx.h"
#include "dec_to_hex.h"

int dec_to_hex(int i)
{
	cout<<"Begin ...."<<endl;
	//取余数作为最低位
	//定义一个变量记录除之后的数目
	int temp = 0;
	vector<int> iDetail_Number;
	while(0 != i%16)
	{	
		temp = i%16;
		iDetail_Number.push_back(temp);
		cout<<"TEMP = "<<temp<<endl;
		i = (i - temp)/16;
	}
	//
	//int final_num = 
	//
	return temp;
}