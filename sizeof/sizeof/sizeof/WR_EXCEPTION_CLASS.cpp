#include "stdafx.h"
#include "EXCEPTION_CLASS.h"


struct my_error{};

namespace WRH
{

	WR_EXCEPTION_CLASS::WR_EXCEPTION_CLASS(int error_code,
										   int link_error,
										   const char* error_message,
										   std::exception* std_message)
										   :e_gather(error_code,link_error,error_message,std_message)
	{
		cout<<"Construct : "<<typeid(WR_EXCEPTION_CLASS()).name()<<endl;
		cout<<"error_code :"<<error_code<<endl;
		cout<<"link_error : "<<link_error<<endl;
		cout<<"error_message : "<<error_message<<endl;
	}

	WR_EXCEPTION_CLASS::~WR_EXCEPTION_CLASS()
	{
		cout<<"Destruct : "<<typeid(WR_EXCEPTION_CLASS()).name()<<endl;
	}

	void WR_EXCEPTION_CLASS::throw_exception_msg()
	{
		//try
		//{
			throw boost::enable_error_info(my_error())<<error_number(10)<<error_string("jinshaoxun");
		//}
		//catch (CMemoryException* e)
		//{
		//	
		//}
		//catch (CFileException* e)
		//{
		//}
		//catch (CException* e)
		//{
		//}
	}

	int WR_EXCEPTION_CLASS::error_code()
	{
		//cout<<"Get the error_code : "<<hex<<e_gather.get<0>()<<endl;
		return e_gather.get<0>();
	}

	int WR_EXCEPTION_CLASS::link_code()
	{
		//cout<<"Get the link_code : "<<e_gather.get<1>()<<endl;
		return e_gather.get<1>();
	}

	const char* WR_EXCEPTION_CLASS::error_msg()
	{
		//cout<<"Get the error_message : "<<e_gather.get<2>()<<endl;
		return e_gather.get<2>().c_str();
	}

	const std::exception* WR_EXCEPTION_CLASS::exception_message()
	{
		//cout<<"Get the exception_message : "<<endl;
		return e_gather.get<3>();
	}


	WR_SYSTEM_EXCEPTION_CLASS::WR_SYSTEM_EXCEPTION_CLASS(const char* msg, std::exception *std_msg)
		:WR_EXCEPTION_CLASS(WR4A_SYSTEM_ERROR,0,msg,std_msg)
	{
		cout<<" "<<typeid(WR_SYSTEM_EXCEPTION_CLASS()).name()<<endl;
		cout<<"error_code : "<<hex<<WR4A_SYSTEM_ERROR<<endl;
		cout<<"link_error : "<<0<<endl;
		cout<<"msg : "<<msg<<endl;

	}
	WR_SYSTEM_EXCEPTION_CLASS::~WR_SYSTEM_EXCEPTION_CLASS()
	{
		cout<<"Destruction : "<<typeid(WR_SYSTEM_EXCEPTION_CLASS).name()<<endl;
	}

	WR_PARAMETER_EXCEPTION_CLASS::WR_PARAMETER_EXCEPTION_CLASS(const char* msg, std::exception* std_msg)
		:WR_EXCEPTION_CLASS(WR4A_PARAMETER_ERROR, 0, msg, std_msg)
	{
		cout<<"Construct : "<<typeid(WR_PARAMETER_EXCEPTION_CLASS()).name()<<endl;
		cout<<"error_code : "<<hex<<WR4A_PARAMETER_ERROR<<endl;
		cout<<"link_error : "<<0<<endl;
		cout<<"error_message : "<<msg<<endl;
	}
	WR_PARAMETER_EXCEPTION_CLASS::~WR_PARAMETER_EXCEPTION_CLASS()
	{
	}

	WR_ILLEGAL_EXCEPTION_CLASS::WR_ILLEGAL_EXCEPTION_CLASS(const char* msg, std::exception* std_msg)
		:WR_EXCEPTION_CLASS(WR4A_ILLEGAL_CALL_ERROR, 0, msg, std_msg)
	{
		cout<<"Construct : "<<typeid(WR_ILLEGAL_EXCEPTION_CLASS()).name()<<endl;
		cout<<"error_code : "<<hex<<WR4A_ILLEGAL_CALL_ERROR<<endl;
		cout<<"link_error : "<<0<<endl;
		cout<<"error_message : "<<msg<<endl;
	}

	WR_ILLEGAL_EXCEPTION_CLASS::~WR_ILLEGAL_EXCEPTION_CLASS()
	{

	}
}