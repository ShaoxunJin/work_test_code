#ifndef _HEADFILE_H_
#define _HEADFILE_H_
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int RLSGMV_p_generate(RLSGMV_spg_data_struct *spg_data_ptr,RLSGMV_step_event_enum *step_event_ptr);

#define RL_ACCEL_TABLE_LEN 256
#define RL_JERK_TABLE_LEN 256

//过程变量结构定义
typedef struct
{
	/*时间计数器:从运动开始以来的采样周期数*/
	int cur_time;
	
	/*[spg_units] (有符号)从运动开始以来的位移*/
	int cur_pos_rel;
	
	/*[spg_units/sample] 前次速度*/
	int prev_vel;
	
	/*[spg_units/sample] 当前速度*/
	int cur_vel;
	
	/*[spg_units/sample^2] 当前加速度*/
	int cur_acc;
	
}RLSGMV_gen_data_struct;

//输出数据结构
typedef struct
{
	  double position;
	  float velocity;
	  float acceleration;
}RLSGMV_spg_data_struct;

//计算过程中的速度、加速度以及各个阶段时间信息
typedef struct
{
	float vel_unit;
	float acc_unit;
	double start_pos;
	double pos_factor;
	int acc_sign;
	int switch_time[8];
}RLSGMV_loc_params_struct;

//转换后的加速度表
typedef struct
{
	int acc_tab_len;				//加速度表长度
	int acc_tab[RL_ACCEL_TABLE_LEN];	/*[spg_units/sample2] 加速度表*/
}RLSGMV_loc_table_struct;


#endif