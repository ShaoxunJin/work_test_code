// spg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "headfile.h"

//全局变量用于存储数据

//转换后的加速度表，这个是最基本的数据；
//后续数据都是按照这个来参考计算；
static RLSGMV_loc_table_struct mv_loc_table;

//计算过程中需要使用到的一些变量
static RLSGMV_loc_params_struct mv_loc_params;

//计算过程实时变化的量包括速度、加速度等信息
static RLSGMV_gen_data_struct mv_gen_data; 


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

