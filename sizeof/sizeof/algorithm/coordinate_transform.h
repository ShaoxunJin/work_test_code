#ifndef COORDINATE_TRANSFORM_H
#define COORDINATE_TRANSFORM_H

#include "head_file.h"


/***常量定义***/
#define coordinate_read_filename ".\\read_coordinate.txt"
#define coordinate_write_filename ".\\write_coordinate.txt"

/************************************************************************/
/* 数据类型定义                                                          */
/************************************************************************/
//typedef struct
//{
//	double x;
//	double y;
//}xy_vect;

/************************************************************************/
/* 函数声明                                                             */
/************************************************************************/
void coordinate_transform();

void transform_calculate(double angle, xy_vect src, xy_vect* dst);

void PUAC_eccentricity_angle_calculation(xy_vect eccentricity_xy,
										 SMEE_DOUBLE *eccentricity_angle);

#endif