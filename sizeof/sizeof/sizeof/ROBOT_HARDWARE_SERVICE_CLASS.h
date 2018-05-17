#ifndef ROBOT_HARDWARE_SERVICE_CLASS_H
#define ROBOT_HARDWARE_SERVICE_CLASS_H

namespace WRH
{
	class ROBOT_HARDWARE_SERVICE_CLASS
	{
	public:
		ROBOT_HARDWARE_SERVICE_CLASS();
		virtual ~ROBOT_HARDWARE_SERVICE_CLASS();
		
		void get_wafer(int station, int slot, bool *present);
		void move_to_retract(int station, int slot);
		void put_wafer(int station, int slot, bool *present);
		void swap_pin(int station, int first_arm, int next_arm, int slot);
		void swap_pickup(int station, int first_arm, int next_arm, int slot);
	private:

	};
}



#endif