#ifndef ALGORIHTM_H
#define ALGORITHM_H

#include "head_file.h"

#define load_repeate_file ".\\load_repeate.txt"

#define zero_line 0.000001


void Cross_Matrix(double* Matrix_Src, int src_width, int src_height, double* Matrix_Dst);


void RLMATH_1st_lowpass_Z_cov(float lowpass_freq,
							  float sample_period,
							  float* a_factor_ptr,
							  float* b_factor_ptr);


void RLMATH_1st_notch_Z_cov(SMEE_FLOAT zero_freq,
							 SMEE_FLOAT pole_freq,
							 SMEE_FLOAT sample_period,
							 SMEE_FLOAT* a_factor_ptr,
							 SMEE_FLOAT* b_factor_ptr);

void least_squares(int nbr);

void least_squares_second_order(vector<double> x, vector<double> y);

//国家验收的数据处理
double max_data(double buffer[],int nbr,int *max_index);

double min_data(double buffer[],int nbr,int *min_index);

double avr_data(double buffer[],int nbr);

double cur_data(double buffer[],int nbr);

void data_process();


#endif