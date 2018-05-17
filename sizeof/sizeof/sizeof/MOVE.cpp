#include "stdafx.h"
#include "MOVE.h"

void move_wafer()
{
	t_STATION_MOVE_WAFER_ENUM_str tt_STATION_MOVE_WAFER_ENUM_str;
	ILP_2_TK_RO tt(STATION_TK_ILP,STATION_WH_LR,0,0);
	int present = 0;
	tt.check_from_station_material(&present);
	tt.check_to_station_material(&present);
	cout<<tt_STATION_MOVE_WAFER_ENUM_str.to_string(tt.from_station())<<endl;
	cout<<tt_STATION_MOVE_WAFER_ENUM_str.to_string(tt.to_station())<<endl;

};