#ifndef MEMORY_OPERATIOIN_H
#define MEMORY_OPERATIOIN_H

#include "head_file.h"

void memcpy_test(void);
void memset_test(void);

typedef struct
{
	int iStruct;
	double dStruct;
}MEMSET_STRUCT;

typedef struct  
{
	bool home_actived;
	bool forward_actived;
	bool reserve_actived;
	int filler;
}HW4T_WR_HOME_LIMIT_STRUCT;


typedef struct  
{
	bool home_actived;
	bool forward_actived;
	bool reserve_actived;
	int filler;
}WR4T_HOME_LIMIT_STRUCT;

//用于结构体构造之后是否需要memset
void memset_struct_test(MEMSET_STRUCT *memset_struct);

void memcpy_for_struct();


#endif