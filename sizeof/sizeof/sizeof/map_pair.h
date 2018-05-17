#ifndef MAP_PAIR_H
#define MAP_PAIR_H
#include "head_file.h"


// 硅片工位枚举
typedef enum
{
	WH4A_LOC_MIN = 0,
	WH4A_LOC_PORT,
	WH4A_LOC_LOAD_ROBOT,
	WH4A_LOC_UNLOAD_ROBOT,
	WH4A_LOC_PREALIGNER,
	WH4A_LOC_DISCHARGE,
	WH4A_LOC_WAFER_STAGE_CHUCK1,
	WH4A_LOC_WAFER_STAGE_CHUCK2,
	WH4A_LOC_TRACK,//track工位不维护物料状态。
	WH4A_LOC_MAX
} WH4A_LOC_ENUM;

void map_pair_pair_test(void);
void map_pair_station_string_2_enum(const string& loc);
const char* enum2str(const WH4A_LOC_ENUM& t);

void map_compare();

void multi_map_compare();


#endif
