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

//��������Ǵ�boost����example
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

//���weak_ptr������������
class B;

class A
{
public:
	A();
	~A();
	boost::shared_ptr<B> b;//�����b�� null   ���û����� Ĭ���ܹ��Զ����ж��������

protected:
private:
};

//
class B
{
public:
	B();
	~B();
	boost::weak_ptr<A> a;//���������໥ѭ�����õ�
	//boost::shared_ptr<A> a;//�����a�� null ���û����� Ĭ���ܹ��Զ����ж��������
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


//����ֻҪ�����;Ϳ���  ����ת�������ľ���*����
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