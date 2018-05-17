#ifndef COORDINATE_TRANSFORM_H
#define COORDINATE_TRANSFORM_H

#include "head_file.h"


/***��������***/
#define coordinate_read_filename ".\\read_coordinate.txt"
#define coordinate_write_filename ".\\write_coordinate.txt"

/************************************************************************/
/* �������Ͷ���                                                          */
/************************************************************************/
//typedef struct
//{
//	double x;
//	double y;
//}xy_vect;

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
void coordinate_transform();

void transform_calculate(double angle, xy_vect src, xy_vect* dst);

void PUAC_eccentricity_angle_calculation(xy_vect eccentricity_xy,
										 SMEE_DOUBLE *eccentricity_angle);

#endif