#ifndef EXCEPTION_CLASS_H
#define EXCEPTION_CLASS_H


#include "head_file.h"
#include <exception>
#include "boost/shared_ptr.hpp"
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include "boost/exception/enable_error_info.hpp"

#define WR_POINTER_NULL_ERROR 108

#define  DEFINE_ERROR_INFO(type,name) typedef boost::error_info<struct tag##name, type> name

namespace WRH
{
	typedef boost::tuple<const char*, int> ERROR_GROUP;
	typedef boost::error_info<struct tage_error_number, int> error_number;
	typedef boost::error_info<struct tage_error_string, string> error_string;
	class WR_EXCEPTION_CLASS : virtual public exception,
							virtual public boost::exception
	{
	public:
		WR_EXCEPTION_CLASS(int error_code,
							int link_error,
							const char* error_message,
							std::exception* std_message);
		
		virtual ~WR_EXCEPTION_CLASS() throw();//最后的throw是未了说明该函数不跑出任何异常

		void throw_exception_msg();
		
		//模板只能在h文件中实现 so不能放置在cpp中
		template<typename T>
		WR_EXCEPTION_CLASS& operator << (T value)
		{
			ostringstream os;
			os<<value;
			e_gather.get<2>().append(os.str().c_str());
			return *this;
		}

		/*template<typename T>
		WR_EXCEPTION_CLASS* operator<<(T value)
		{
			ostringstream os;
			os<<value;
			e_gather.get<2>().append(os.str().c_str());
			return *this;
		}*/

		int error_code();
		int link_code();
		const char* error_msg();
		const std::exception * exception_message();

		typedef int t_error_link;
		typedef int t_error_code;
		typedef boost::tuple<t_error_code, t_error_link, string, std::exception*> error_gather;
	
	private:
		error_gather e_gather;
	};

	class WR_SYSTEM_EXCEPTION_CLASS : public WR_EXCEPTION_CLASS
	{
	public:
		WR_SYSTEM_EXCEPTION_CLASS(const char* msg, std::exception *std_msg);
		~WR_SYSTEM_EXCEPTION_CLASS();

	private:
	};

	class WR_PARAMETER_EXCEPTION_CLASS : public WR_EXCEPTION_CLASS
	{
	public:
		WR_PARAMETER_EXCEPTION_CLASS(const char* msg, std::exception* std_msg);
		~WR_PARAMETER_EXCEPTION_CLASS();
	};

	class WR_ILLEGAL_EXCEPTION_CLASS : public WR_EXCEPTION_CLASS
	{
	public:
		WR_ILLEGAL_EXCEPTION_CLASS(const char* msg, std::exception* std_msg);
		~WR_ILLEGAL_EXCEPTION_CLASS();
	};

	class WR_POINT_EXCEPTION_CHECK : public WR_EXCEPTION_CLASS
	{
	public:
		WR_POINT_EXCEPTION_CHECK(int error_code,
								int error_link,
								const char* msg,
								std::exception *std_msg)
								:WR_EXCEPTION_CLASS(error_code, error_link,msg, std_msg)
		{

		}

		template<typename T>
		void operator()(typename boost::shared_ptr<T> pointer)
		{
			if (NULL == pointer)
			{
				throw boost::enable_error_info(*this);
			}
		}


		template<typename T>
		void operator()(typename T pointer)
		{
			if (NULL == pointer)
			{
				throw boost::enable_error_info(*this);
			}
		}

		~WR_POINT_EXCEPTION_CHECK() throw()
		{
		}
	};
}

#endif