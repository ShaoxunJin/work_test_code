#include "stdafx.h"
#include "boost.h"

using namespace boost;

//void boost_test()
//{
//	using boost::any;
//	vector<boost::any> values;
//	values.push_back(1);
//	values.push_back(2);
//
//	vector<boost::any>::iterator values_iter;
//	for (values_iter = values.begin(); values_iter < values.end(); values_iter++)
//	{
//		cout<<"values = "<<boost::any_cast<int>(*values_iter)<<endl;
//	}
//}

/******************************************************************
类似 pair 多个不同类型的参数进行组合配对
******************************************************************/
void boost_tuple()
{
	//这是第一种初始化方式
	boost::tuple<int,double,string> t(1,2.1,"jinshaoxun");
	cout<<"First:"<<t.get<0>()<<endl;
	cout<<"Second:"<<t.get<1>()<<endl;
	cout<<"Third:"<<t.get<2>()<<endl;

	//下面这种方式类似make_pair进行构造；
	boost::tuple<int,string,double> t_make_tuple = boost::make_tuple(2,"name = jinshaoxun",1111);
	cout<<"First:"<<get<0>(t_make_tuple)<<endl;
	cout<<"Second:"<<get<1>(t_make_tuple)<<endl;
	cout<<"Third:"<<get<2>(t_make_tuple)<<endl;

	//构造了之后对变量还能进行更改么 事实证明是可以更改的
	t_make_tuple = boost::make_tuple(3,"name = shaoxun jin",2222);
	cout<<"First:"<<get<0>(t_make_tuple)<<endl;
	cout<<"Second:"<<get<1>(t_make_tuple)<<endl;
	cout<<"Third:"<<get<2>(t_make_tuple)<<endl;

	//返回引用 可以用作左值操作
	int i1 = 4;
	string i2 = "jin";
	double i3 = 0.1;
	boost::tuple<int,string,double> t_tie = boost::tie(i1, i2, i3);
	boost::tuple<int,string,double> t_tuple = boost::make_tuple(i1,i2,i3);
	i1 = 123;
	i2 = "shaoxun";
	i3 = 0.123;
	t_tie.get<0>() = i1;
	t_tie.get<1>() = i2;
	t_tie.get<2>() = i3;
	t_tuple.get<0>() = i1;
	t_tuple.get<1>() = i2;
	t_tuple.get<2>() = i3;

	cout<<"This is the tie of tuple ...."<<endl;
	cout<<"t_tie First:"<<get<0>(t_tie)<<endl;
	cout<<"t_tie Second:"<<get<1>(t_tie)<<endl;
	cout<<"t_tie Third:"<<get<2>(t_tie)<<endl;

	cout<<"t_tuple First:"<<get<0>(t_tuple)<<endl;
	cout<<"t_tuple Second:"<<get<1>(t_tuple)<<endl;
	cout<<"t_tuple Third:"<<get<2>(t_tuple)<<endl;
}

Foo::Foo(int _x)
:x(_x)
{
	cout<<"This is the construction : "<<typeid(Foo).name()<<endl;
	cout<<"x = "<<x<<endl;
};

Foo::~Foo()
{
	cout<<"This is the destruction : "<<typeid(Foo).name()<<endl;
};

//操作符重载不一定要在h中实现 在cpp中实现也可以
bool FooPtrOps::operator()(const FooPtr& a, const FooPtr& b)
{
	return a->x > b->x;
}

void FooPtrOps::operator ()(const FooPtr &a)
{
	cout<<a->x<<endl;
}

void boost_for_each()
{
	vector<FooPtr> foo_vec;

	//下面也是一种container 唯一的区别是这里不能使用same的member元素
	set<FooPtr, FooPtrOps> foo_set;

	//下面每个push都会增加一个对ptr的引用 也就是会自动增加一个指针的引用
	FooPtr foo_ptr(new Foo(2));	//这个时候use_cout就是存在一个1
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_vec.push_back(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_set.insert(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	//被共用了3次

	//重新reset之后是将引用值重置为1
	foo_ptr.reset(new Foo(3));
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_vec.push_back(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_set.insert(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;

	foo_ptr.reset(new Foo(5));
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_vec.push_back(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_set.insert(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;

	foo_ptr.reset(new Foo(4));
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	//foo_vec.push_back(foo_ptr);
	foo_vec.push_back(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	//foo_set.insert(foo_ptr);
	foo_set.insert(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;//

	cout<<"foo_vector:"<<endl;
	for_each(foo_vec.begin(), foo_vec.end(), FooPtrOps());
	cout<<"\nfoo_set:"<<endl;
	for_each(foo_set.begin(), foo_set.end(), FooPtrOps());

};

BOOST_EXCEPTION_CLASS::BOOST_EXCEPTION_CLASS(const char* message)
{
	m_error_msg = message;
	cout<<"Construction : "<<typeid(BOOST_EXCEPTION_CLASS()).name()<<" success !"<<endl;
}

BOOST_EXCEPTION_CLASS::~BOOST_EXCEPTION_CLASS()
{
	cout<<"Destruction : "<<typeid(BOOST_EXCEPTION_CLASS()).name()<<" success !"<<endl;
}

const char* BOOST_EXCEPTION_CLASS::error_msg()
{
	return m_error_msg;
}

void xuda_share_ptr_test()
{
	int *pSharePtr = new int(100);
	cout<<"*pSharePtr = "<<*pSharePtr<<endl;
	
	//pSharePtr = new int[3];
	//pSharePtr = pSharePtr + 1;
	//delete pSharePtr;
	//*pSharePtr = 111;

	//这里是unique的目的是说明这个ptr的use_count为1；
	boost::shared_ptr<int> spi(new int(123));
	assert(spi);
	assert(spi.unique());
	boost::shared_ptr<int> spi_2(new int(12));
	assert(spi_2.unique());
	assert(spi.unique());

	typedef vector<boost::shared_ptr<int> > vs;
	vs vec_share_ptr(10);//这是指定vector的数量
	cout<<"size = "<<vec_share_ptr.size();
	int i = 0;
	//给10个 share_ptr进行构造
	for (vs::iterator iter = vec_share_ptr.begin();
		iter != vec_share_ptr.end();
		++iter,++i)
	{
		*iter = boost::shared_ptr<int>(new int(i));
		cout<<""<<**iter<<endl;
	}
	
	boost::shared_ptr<vector<int> > sv(new vector<int>(5));
	for (int i = 0; i < 5; ++i)
	{
		sv->operator [](i) = i;
	}
	cout<<"sv->size() = "<<sv->size()<<endl;
	//vector<int>::iterator iter = sv->begin();
	int j = 0;
	for (vector<int>::iterator iter = sv->begin();
		iter != sv->end();
		++iter, ++j)
	{
		cout<<sv->operator [](j)<<endl;
		//++j;
	}
	cout<<"sv.use_count() = "<<sv.use_count()<<endl;
}

A::A()
{
	cout<<__FUNCTION__<<endl;
}

A::~A()
{
	cout<<__FUNCTION__<<endl;
}

B::B()
{
	cout<<__FUNCTION__<<endl;
}

B::~B()
{
	cout<<__FUNCTION__<<endl;
}

/*
1、如果只有在A类中引用了B类，单向引用的话是没有问题的；可以正常的申请内存空间和释放内存空间；
2、
*/
void test_weak_ptr()
{
	boost::shared_ptr<A> x(new A());
	cout<<"x.use_count() = "<<x.use_count()<<endl;
	x->b = boost::shared_ptr<B>(new B());
	cout<<"x.use_count() = "<<x.use_count()<<endl;
	cout<<"x->b.use_count() = "<<x->b.use_count()<<endl;
	x->b->a = x;//这个时候 等号 左边的用了x
	//如果是采用weak_ptr，则使用的是weak_ptr来分享；
	//weak_ptr是要从share_ptr中进行赋值过来的；
	cout<<"x.use_count() = "<<x.use_count()<<endl;
	cout<<"x->b.use_count() = "<<x->b.use_count()<<endl;
}


void boost_any_test()
{
	function_in;

	boost::any any_i(10);
	cout<<boolalpha<<can_cast<int>(any_i)<<endl;
	cout<<boolalpha<<can_cast<string>(any_i)<<endl;

	cout<<"point = "<<&any_i<<endl;
	cout<<"getPoint<int>(any_i) = "<<getPoint<int>(any_i)<<endl;
	cout<<"getReferrence<int>(any_i) = "<<++getReferrence<int>(any_i)<<endl;

	function_out;
}