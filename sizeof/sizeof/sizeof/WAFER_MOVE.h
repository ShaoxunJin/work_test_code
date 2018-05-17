#ifndef WAFER_MOVE_H
#define WAFER_MOVE_H

#include "head_file.h"
#include "ENUM_REGISTER.h"
#include "STATION_BASE_CLASS.h"

class ILP_2_TK_RO : public STATION_BASE_CLASS
{
public:
	explicit ILP_2_TK_RO(STATION_MOVE_WAFER_ENUM from_stn, 
						STATION_MOVE_WAFER_ENUM to_stn,
						int from_slot = 0,
						int to_slot = 0);
	~ILP_2_TK_RO();

	//下面最好是继承每个设备 每个设备分别进行对物料的check
	void check_from_station_material(int* present);
	void check_to_station_material(int* present);
	void move_wafer();

	STATION_MOVE_WAFER_ENUM from_station();
	STATION_MOVE_WAFER_ENUM to_station();

protected:
private:
	STATION_MOVE_WAFER_ENUM m_eFromStn;
	STATION_MOVE_WAFER_ENUM m_eToStn;
	int m_iFromSlot;
	int m_iToSlot;
};

class TK_RO_2_PU : public STATION_BASE_CLASS
{
public:
	explicit TK_RO_2_PU(STATION_MOVE_WAFER_ENUM from_stn, 
					STATION_MOVE_WAFER_ENUM to_stn,
					int from_slot = 0,
					int to_slot = 0);
	~TK_RO_2_PU();
	void check_from_station_material(int* present);
	void check_to_station_material(int* present);
	void move_wafer();

protected:
private:
	STATION_MOVE_WAFER_ENUM m_eFromStn;
	STATION_MOVE_WAFER_ENUM m_eToStn;
	int m_iFromSlot;
	int m_iToSlot;

};

class PU_2_LR : public STATION_BASE_CLASS
{
public:
	explicit PU_2_LR(STATION_MOVE_WAFER_ENUM from_stn,
					STATION_MOVE_WAFER_ENUM to_stn,
					int from_slot = 0,
					int to_slot = 0);
	~PU_2_LR();
	void check_from_station_material(int* present);
	void check_to_station_material(int* present);
	void move_wafer();

private:
	STATION_MOVE_WAFER_ENUM m_eFromStn;
	STATION_MOVE_WAFER_ENUM m_eToStn;
	int m_iFromSlot;
	int m_iToSlot;
};


#endif