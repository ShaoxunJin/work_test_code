#ifndef WG_STATION_MODEL_CALSS_H
#define WG_STATION_MODEL_CALSS_H

#include "head_file.h"
#include "boost/shared_ptr.hpp"
#include "STATION_MODEL_ABSTRACT_INTERFACE.h"

namespace WRH
{
	class WG_STATION_MODEL_CALSS : public STATION_MODEL_ABSTRACT_INTERFACE
	{
	public:
		WG_STATION_MODEL_CALSS(const char* stn);
		~WG_STATION_MODEL_CALSS();
		const char* get_wg_station_name();

	private:
		const char* m_station_name;

	};
}

#endif