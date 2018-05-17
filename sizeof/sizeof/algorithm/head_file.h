#ifndef _HEAD_FILE_H_
#define _HEAD_FILE_H_

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>//此头文件的目的是使用ostringstream & istringstream
#include <string.h>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iomanip>	//I/O流控制文件 用于格式化输出
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <utility>
#include <math.h>
#include "smee.h"

using namespace std;

//case 逻辑测试
#define RL_PI 3.14159265358979

//typedef enum
//{
//	SMEE_FALSE = 0,
//	SMEE_TRUE
//}SMEE_BOOL;

#define OK 0
//#define SMEE_FLOAT float
//#define SMEE_DOUBLE double
#define sample 0.0004


void function_in(const char* fun_name);
void function_out(const char* func_name);

#endif