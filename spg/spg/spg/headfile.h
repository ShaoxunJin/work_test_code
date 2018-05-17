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

//���̱����ṹ����
typedef struct
{
	/*ʱ�������:���˶���ʼ�����Ĳ���������*/
	int cur_time;
	
	/*[spg_units] (�з���)���˶���ʼ������λ��*/
	int cur_pos_rel;
	
	/*[spg_units/sample] ǰ���ٶ�*/
	int prev_vel;
	
	/*[spg_units/sample] ��ǰ�ٶ�*/
	int cur_vel;
	
	/*[spg_units/sample^2] ��ǰ���ٶ�*/
	int cur_acc;
	
}RLSGMV_gen_data_struct;

//������ݽṹ
typedef struct
{
	  double position;
	  float velocity;
	  float acceleration;
}RLSGMV_spg_data_struct;

//��������е��ٶȡ����ٶ��Լ������׶�ʱ����Ϣ
typedef struct
{
	float vel_unit;
	float acc_unit;
	double start_pos;
	double pos_factor;
	int acc_sign;
	int switch_time[8];
}RLSGMV_loc_params_struct;

//ת����ļ��ٶȱ�
typedef struct
{
	int acc_tab_len;				//���ٶȱ���
	int acc_tab[RL_ACCEL_TABLE_LEN];	/*[spg_units/sample2] ���ٶȱ�*/
}RLSGMV_loc_table_struct;


#endif