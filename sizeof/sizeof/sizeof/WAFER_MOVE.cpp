#include "stdafx.h"
#include "WAFER_MOVE.h"


ILP_2_TK_RO::ILP_2_TK_RO(STATION_MOVE_WAFER_ENUM from_stn,
							STATION_MOVE_WAFER_ENUM to_stn,
							int from_slot /* = 0 */,
							int to_slot /* = 0 */)
							:m_eFromStn(from_stn)
							,m_eToStn(to_stn)
							,m_iFromSlot(from_slot)
							,m_iToSlot(to_slot)
{
	cout<<__FUNCTION__<<endl;
	//t_STATION_MOVE_WAFER_ENUM_str *tt_STATION_MOVE_WAFER_ENUM_str = NULL;
	//cout<<"From_station : "<<tt_STATION_MOVE_WAFER_ENUM_str->to_string(from_stn)<<endl;
	//cout<<"To_station : "<<tt_STATION_MOVE_WAFER_ENUM_str->to_string(to_stn)<<endl;
	//cout<<"From_slot : "<<from_stn<<endl;
	//cout<<"To_slot : "<<to_slot<<endl;
}

ILP_2_TK_RO::~ILP_2_TK_RO()
{
	cout<<__FUNCTION__<<endl;
}

void ILP_2_TK_RO::check_from_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void ILP_2_TK_RO::check_to_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void ILP_2_TK_RO::move_wafer()
{
	cout<<__FUNCTION__<<endl;
}


STATION_MOVE_WAFER_ENUM ILP_2_TK_RO::from_station()
{
	return m_eFromStn;
}

STATION_MOVE_WAFER_ENUM ILP_2_TK_RO::to_station()
{
	return m_eToStn;
}


TK_RO_2_PU::TK_RO_2_PU(STATION_MOVE_WAFER_ENUM from_stn,
					   STATION_MOVE_WAFER_ENUM to_stn,
					   int from_slot /* = 0 */,
					   int to_slot /* = 0 */)
{
	cout<<__FUNCTION__<<endl;

}

TK_RO_2_PU::~TK_RO_2_PU()
{
	cout<<__FUNCTION__<<endl;

}

void TK_RO_2_PU::check_from_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void TK_RO_2_PU::check_to_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void TK_RO_2_PU::move_wafer()
{
	cout<<__FUNCTION__<<endl;

}

PU_2_LR::PU_2_LR(STATION_MOVE_WAFER_ENUM from_stn,
					   STATION_MOVE_WAFER_ENUM to_stn,
					   int from_slot /* = 0 */,
					   int to_slot /* = 0 */)
{
	cout<<__FUNCTION__<<endl;

}

PU_2_LR::~PU_2_LR()
{
	cout<<__FUNCTION__<<endl;

}

void PU_2_LR::check_from_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void PU_2_LR::check_to_station_material(int* present)
{
	cout<<__FUNCTION__<<endl;

}

void PU_2_LR::move_wafer()
{
	cout<<__FUNCTION__<<endl;

}