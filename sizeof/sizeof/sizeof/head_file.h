#ifndef _HEAD_FILE_H_
#define _HEAD_FILE_H_
/******************************************************************
					共用头文件
******************************************************************/

#include "stdafx.h"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>//此头文件的目的是使用ostringstream & istringstream
#include <string.h>
#include <vector>
#include <deque>
#include <set>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iomanip>	//I/O流控制文件 用于格式化输出
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <utility>
#include <list>
#include <typeinfo>
#include "smee.h"
//#include "WRMC_tc.h"
#include "WR4A_tc.h"
#include "WC4A_tc.h"

using namespace std;

//case 逻辑测试

void function_in(const char* fun_name);

void function_out(const char* fun_name);


#endif