#ifndef CARTENSIAN_TO_POLAR_H
#define CARTENSIAN_TO_POLAR_H

#include "head_file.h"

typedef struct
{
	double x;
	double y;
}cartensian_cs_struct;

typedef struct  
{
	double r;
	double theta;
}polar_cs_struct;

polar_cs_struct cartensian_to_polar(cartensian_cs_struct);

#endif
