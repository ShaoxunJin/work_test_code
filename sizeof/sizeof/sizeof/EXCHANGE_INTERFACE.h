#ifndef EXCHANGE_INTERFACE_H
#define EXCHANGE_INTERFACE_H

#include "WR4T_WORKFLOW_tc.h"
#include "head_file.h"

namespace WRH
{
	class EXCHANGE_INTERFACE
	{
	public:
		EXCHANGE_INTERFACE();
		virtual ~EXCHANGE_INTERFACE();

	public:
		void set_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type);
		WR4T_EXCHANGE_TYPE_ENUM get_exchange_type();

		void set_swap_state(int swap_state);
		int get_swap_state();

	private:
		WR4T_EXCHANGE_TYPE_ENUM m_exchange_type;
		int m_swap_state;
	};
}

#endif