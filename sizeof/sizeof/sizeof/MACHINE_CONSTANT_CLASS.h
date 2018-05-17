#ifndef MACHINE_CONSTANT_CLASS_H
#define MACHINE_CONSTANT_CLASS_H
#include "head_file.h"
#include "WRMC_WORKFLOW_tc.h"
#include "WR4T_WORKFLOW_tc.h"
#include "STATION_MODEL_ABSTRACT_INTERFACE.h"

namespace WRH
{
	//жьтьоб╡ывВ╥Ш
	ostream& operator<<(ostream& os, const WRMC_ROBOT_STRUCT mc);

	class MACHINE_CONSTANT_CLASS
	{
	public:
		MACHINE_CONSTANT_CLASS();
		~MACHINE_CONSTANT_CLASS();

		static MACHINE_CONSTANT_CLASS* get_instance();
		void download_mc();
		void update_mc();
		void set_mc(WRMC_ROBOT_STRUCT mc);
		WRMC_ROBOT_STRUCT* get_mc();
		const WRMC_STATION_PARAMTER_STRUCT* get_station_config(WR4T_STATION_MODEL_ENUM station);
		void print_mc();

	private:
		void verify_mc(const WRMC_ROBOT_STRUCT& mc);
		static MACHINE_CONSTANT_CLASS* m_instance;

		WRMC_ROBOT_STRUCT* m_mc;
	};
}
#endif