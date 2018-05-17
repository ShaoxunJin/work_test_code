#ifndef BOOST_H
#define BOOST_H

/***************
boost
***************/
#include "head_file.h"
#include "boost/tuple/tuple.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

#include <exception>
#include "boost/exception/all.hpp"
#include "boost/exception/enable_error_info.hpp"
#include "boost/throw_exception.hpp"
#include "boost/make_shared.hpp"
#include "boost/any.hpp"

//#include "boost/date_time/posix_time/posix_time.hpp"
//#include <boost/any.hpp>

//using namespace boost;
//void boost_test();
void boost_tuple();


struct Foo
{ 
	Foo( int _x );// : x(_x) {}
	~Foo();// { std::cout << "Destructing a Foo with x=" << x << "\n"; }
	int x;
	/* ... */
};

//下面这个是从boost来的example
typedef boost::shared_ptr<Foo> FooPtr;


struct FooPtrOps
{
	bool operator()(const FooPtr& a, const FooPtr& b);
	void operator()(const FooPtr& a);
};


void boost_for_each();

class BOOST_EXCEPTION_CLASS : virtual public exception, virtual public boost::exception
{
public:
	BOOST_EXCEPTION_CLASS(const char* message);
	~BOOST_EXCEPTION_CLASS();

	const char* error_msg();

protected:
private:
	const char* m_error_msg;
};

void xuda_share_ptr_test();

//解决weak_ptr环形依赖问题
class B;

class A
{
public:
	A();
	~A();
	boost::shared_ptr<B> b;//这里的b是 null   如果没有这个 默认能够自动进行对象的销毁

protected:
private:
};

//
class B
{
public:
	B();
	~B();
	boost::weak_ptr<A> a;//这是两个相互循环引用的
	//boost::shared_ptr<A> a;//这里的a是 null 如果没有这个 默认能够自动进行对象的销毁
protected:
private:
};

void test_weak_ptr();

template <typename T>
bool can_cast(boost::any &t);

template <typename T>
T& getReferrence(boost::any &t);

template <typename T>
T* getPoint(boost::any &t);

template <typename T>
bool can_cast(boost::any &t)
{
	return t.type() == typeid(T);
}

template <typename T>
inline T& getReferrence(boost::any &t)
{
	assert(can_cast<T>(t));
	return *boost::any_cast<T>(&t);
}


//这里只要是类型就可以  最终转换出来的就是*类型
template <typename T>
inline T* getPoint(boost::any &t)
{
	if (!can_cast<T>(t))
	{
		return NULL;
	}
	else
	{
		return boost::any_cast<T>(&t);
	}
}

void boost_any_test();


#endif