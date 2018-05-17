#ifndef _MODEL_SEARCH_H_
#define _MODEL_SEARCH_H_

#include "head_file.h"

/* XY 平面内的向量 */
typedef struct
{
	SMEE_DOUBLE x1;
	SMEE_DOUBLE x2;
} xx_vect;


//double sigma = 0.25;
//int e[2][2] = {{1,0},{0,1}};
/******************************************************************
计算Y值
******************************************************************/
double MODEL_SEARCH_calculate_Y(xx_vect x_init, double sigma, int cycle);

/******************************************************************
f(var) = x^2 + y^2
******************************************************************/
double MODEL_SEARCH_function_value(xx_vect var);


#endif