#include "stdafx.h"

#include "WRAPSN.h"


WRAPPU::WRAPPU(const char* class_name, WR_106_EXCHANGE_METHOD_ENUM method)
:m_name(class_name)
,m_exchange_method(method)
{
	cout<<"Construct... "<<typeid(WRAPPU).name()<<endl;
}


WRAPPU::~WRAPPU()
{
	cout<<"Destruct... "<<typeid(WRAPPU).name()<<endl;
}

void WRAPPU::set_exchange_method(WR_106_EXCHANGE_METHOD_ENUM method)
{
	this->m_exchange_method = method;
}

WR_106_EXCHANGE_METHOD_ENUM WRAPPU::get_exchange_method()
{
	return this->m_exchange_method;
}

int WRAPPU::send_wafer()
{
	function_in;
	switch(this->m_exchange_method)
	{
	case WR_106_EXCHANGE_PUT_GET_DIRECT:
		put_wafer_direct();
		break;
	case WR_106_EXCHANGE_PICKUP:
		move_to_exchange();
		break;
	case WR_106_EXCHANGE_PUT_GET_CUSTOM:
		put_wafer_custom();
		break;
	default:
		break;
	}

	function_out;
	return 0;
}

int WRAPPU::receive_wafer()
{
	function_in;
	switch(this->m_exchange_method)
	{
	case WR_106_EXCHANGE_PUT_GET_DIRECT:
		get_wafer_direct();
		break;
	case WR_106_EXCHANGE_PICKUP:
		move_to_exchange();
		break;
	case WR_106_EXCHANGE_PUT_GET_CUSTOM:
		get_wafer_custom();
		break;
	default:
		break;
	}

	function_out;
	return 0;
}


