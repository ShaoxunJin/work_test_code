#include "stdafx.h"
#include "WG_STATION_MODEL_CLASS.h"

namespace WRH
{
	WG_STATION_MODEL_CALSS::WG_STATION_MODEL_CALSS(const char* stn)
		:m_station_name(stn)
	{
		cout<<"Current Station : "<<m_station_name<<endl;
		//STATION_MODEL_ABSTRACT_INTERFACE::m_station_name = WR4T_STATION_MODEL_WG;
	}

	WG_STATION_MODEL_CALSS::~WG_STATION_MODEL_CALSS()
	{

	}

	const char* WG_STATION_MODEL_CALSS::get_wg_station_name()
	{
		return m_station_name;
	}

}