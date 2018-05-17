#include "stdafx.h"
#include "EXCHANGE_INTERFACE.h"

namespace WRH
{
	EXCHANGE_INTERFACE::EXCHANGE_INTERFACE()
	{
		cout<<"Construct : "<<typeid(EXCHANGE_INTERFACE()).name()<<endl;
	}

	EXCHANGE_INTERFACE::~EXCHANGE_INTERFACE()
	{
		cout<<"Destruct : "<<typeid(EXCHANGE_INTERFACE()).name()<<endl;

	}

	void EXCHANGE_INTERFACE::set_exchange_type(WR4T_EXCHANGE_TYPE_ENUM type)
	{
		this->m_exchange_type = type;
	}

	WR4T_EXCHANGE_TYPE_ENUM EXCHANGE_INTERFACE::get_exchange_type()
	{
		return this->m_exchange_type;
	}

	void EXCHANGE_INTERFACE::set_swap_state(int swap_state)
	{
		this->m_swap_state = swap_state;
	}

	int EXCHANGE_INTERFACE::get_swap_state()
	{
		return this->m_swap_state;
	}

}