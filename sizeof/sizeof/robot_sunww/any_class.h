//#ifndef any_class_h_
//#define any_class_h__

#ifndef ANY_CLASS_H
#define ANY_CLASS_H

#include <iostream>
namespace _SUNWW
{

	class any
	{
	public:
		any():content(0)
		{

		}
		template<typename ValueType> 
		any(const ValueType & value):content(new holder<ValueType>(value))
		{
		
		}
		any(const any & other):content(other.content ? other.content->clone() : 0)
		{

		}
		~any()
		{
			delete content;
		}
	public:
		any & swap(any & rhs)
		{
			std::swap(content,rhs.content);
			return *this;
		}
		template<typename ValueType> 
		any & operator=(const ValueType & rhs)
		{
			any(rhs).swap(*this);
			return *this;
		}
		any operator=(any rhs)
		{
			rhs.swap(*this);
			return *this;
		}
	public:
		bool empty() const
		{
			return !content;
		}
		const std::type_info & type() const
		{
			return content ? content->type():typeid(void);
		}
		class placeholder
		{
		public:
			virtual ~placeholder()
			{

			}
			virtual const std::type_info & type() const = 0;
			virtual placeholder * clone() const = 0;
		protected:
		private:
		};

		template<typename ValueType >
		class holder:public placeholder
		{
		public:
			holder(const ValueType & value):held(value)
			{

			}
		public:
			virtual const std::type_info & type() const
			{
				return typeid(ValueType);
			}
			virtual placeholder* clone () const
			{
				return new holder(held);
			}
		public:
			ValueType held;
		private:
			holder & operator =(const holder &);

		};

	private:
		/*template<typename ValueType>
		friend ValueType & any_cast(any & val);

		template<typename ValueType>
		friend ValueType * unsafe_any_cast(any *);*/

	public:
		placeholder* content;
	};

	template<typename ValueType>
	ValueType any_cast( any & val )
	{
		ValueType* rtn = any_cast<ValueType>( &val);
		return *rtn;
	}
	template<typename ValueType>
	ValueType* any_cast( any * val )
	{

		return val && val->type() == typeid(ValueType) ? &static_cast<any::holder<ValueType> * >(val->content)->held : 0 ;
	}
}
#endif // any_class_h__