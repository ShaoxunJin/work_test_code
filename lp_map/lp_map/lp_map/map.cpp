#include<stdafx.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<stdio.h>
#include"map.h"
using namespace std;

#define RAW 0

int m_resolve_slot_state(int sample_nbr, double *pos_data, double *sn_data, WHLP_SLOT_INFO_ENUM slot[WH4A_MAX_SLOT_NBR])
{
	const char *func = "m_resolve_slot_state";
	int rtn = OK;
	/////////////////////机器常数////////////////////////
	double top_slot = 0.0496538;
	double pitch = 0.01001864167;
	double normal_inserted_area = 0.4;
	
	//new
	double normal_insert_high = 0.2;
	double normal_insert_low = 0.35;

	int doubled_min = 9;
	/////////////////////////////////////////////////////
	// 入口参数信息
	vector<double> scan_data;   // 定义scan_data为double型向量空间

	int detected_int[MAX_DATA_LENGTH];
	double *position = (double *)pos_data;
	//cout<<"position = "<<position[5]<<endl;
	for(int i = 0;i < sample_nbr;i++)
	{
		detected_int[i] = (int)sn_data[i];
	}
	int *detected = detected_int;
	//cout<<"detected = "<<detected[1218]<<endl;
	for (int i = 0; i < sample_nbr; i++, ++detected, ++position)
	{
		if (*detected)
		{
			scan_data.push_back(*position);//这里是把=1的位置放入到了scan_data里面；
		}
	}

	//This is sensor = 1 data_size
	cout<<"(scan_data sensor = 1.)nbr =  "<<scan_data.size()<<endl;

	double norminal_position = top_slot + (WH4A_MAX_SLOT_NBR - 1) * pitch;//正常放置片槽中心位置
	double normal_insert_area = normal_inserted_area * pitch;			//正常放置片占用空间范围

	int pre_total_count = 0;		//
	int lower_total_count = 0;		//
	int current_slot_count = 0;		//硅片存在区域扫描值
	const char *slot_info = 0;
	int great_top_slot_count = 0;

	great_top_slot_count = count_if(scan_data.begin(), scan_data.end(),
			bind2nd(greater<double>(), top_slot));
	cout<<"great_top_slot = "<<great_top_slot_count<<endl;
	cout<<"normal_insert_area = "<<normal_insert_area<<endl;
	cout<<"pitch = "<<pitch<<endl<<endl;

	for (int i_slot = 0; i_slot < WH4A_MAX_SLOT_NBR; ++i_slot)
	{
		/******************************************************************
		原始计算方式
		******************************************************************/
		if(RAW)
		{
			lower_total_count = count_if(scan_data.begin(), scan_data.end(),
				bind2nd(greater<double>(), norminal_position + normal_insert_area));
			current_slot_count = count_if(scan_data.begin(), scan_data.end(),
				bind2nd(greater<double>(), norminal_position - normal_insert_area)) - lower_total_count;
		}
		else
		{
			//下面根据normal_position位置重新进行更改；
			lower_total_count = count_if(scan_data.begin(), scan_data.end(),
				bind2nd(greater<double>(), norminal_position + normal_insert_low * pitch));
			current_slot_count = count_if(scan_data.begin(), scan_data.end(),
				bind2nd(greater<double>(), norminal_position - normal_insert_high * pitch)) - lower_total_count;
		}

		cout<<"slot_number = "<<i_slot + 1<<endl;
		cout<<"norminal_position = "<<norminal_position<<endl;
		cout<<"norminal_position_high = "<<norminal_position - normal_insert_area<<endl;
		cout<<"norminal_position_low = "<<norminal_position + normal_insert_area<<endl;
		cout<<"pre_total_count = "<<pre_total_count<<endl;
		cout<<"lower_total_count = "<<lower_total_count<<endl;
		cout<<"current_slot_count = "<<current_slot_count<<endl;


		if (lower_total_count - pre_total_count > 0)
		{
			cout<<"Slot : "<<i_slot<<" Cross Slot Happen !"<<endl;
			slot[i_slot] = WHLP_CROSS_SLOT;
			//下面这个目的是cross_slot情况下不会只有一槽发生跨槽现象
			//跨槽会涉及到上下两槽 就算是前面这一槽正常 后面这一槽会对其信息重新进行设置
			if (i_slot != 0)
			{
				cout<<"Slot : "<<i_slot<<" Cross Slot Happen !"<<endl;
				slot[i_slot - 1] = WHLP_CROSS_SLOT;
			}
			cout<<"slot["<<i_slot<<"] = "<<enum2str(slot[i_slot])<<endl;
		}
		else if (current_slot_count == 0)
		{
			slot[i_slot] = WHLP_NO_WAFER;
			cout<<"slot["<<i_slot<<"] = "<<enum2str(slot[i_slot])<<endl;

		}
		else if (current_slot_count < doubled_min)
		{
			slot[i_slot] = WHLP_NORMALLY_INSERT;
			cout<<"slot["<<i_slot<<"] = "<<enum2str(slot[i_slot])<<endl;
		}
		else
		{
			slot[i_slot] = WHLP_DOUBLE_SLOT;
			cout<<"slot["<<i_slot<<"] = "<<enum2str(slot[i_slot])<<endl;

		}
		pre_total_count = current_slot_count + lower_total_count;
		norminal_position -= pitch;

		cout<<"\r"<<endl;

	}
	// 出口参数信息
	return rtn;
}