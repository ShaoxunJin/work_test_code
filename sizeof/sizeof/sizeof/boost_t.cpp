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
���� pair �����ͬ���͵Ĳ�������������
******************************************************************/
void boost_tuple()
{
	//���ǵ�һ�ֳ�ʼ����ʽ
	boost::tuple<int,double,string> t(1,2.1,"jinshaoxun");
	cout<<"First:"<<t.get<0>()<<endl;
	cout<<"Second:"<<t.get<1>()<<endl;
	cout<<"Third:"<<t.get<2>()<<endl;

	//�������ַ�ʽ����make_pair���й��죻
	boost::tuple<int,string,double> t_make_tuple = boost::make_tuple(2,"name = jinshaoxun",1111);
	cout<<"First:"<<get<0>(t_make_tuple)<<endl;
	cout<<"Second:"<<get<1>(t_make_tuple)<<endl;
	cout<<"Third:"<<get<2>(t_make_tuple)<<endl;

	//������֮��Ա������ܽ��и���ô ��ʵ֤���ǿ��Ը��ĵ�
	t_make_tuple = boost::make_tuple(3,"name = shaoxun jin",2222);
	cout<<"First:"<<get<0>(t_make_tuple)<<endl;
	cout<<"Second:"<<get<1>(t_make_tuple)<<endl;
	cout<<"Third:"<<get<2>(t_make_tuple)<<endl;

	//�������� ����������ֵ����
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

//���������ز�һ��Ҫ��h��ʵ�� ��cpp��ʵ��Ҳ����
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

	//����Ҳ��һ��container Ψһ�����������ﲻ��ʹ��same��memberԪ��
	set<FooPtr, FooPtrOps> foo_set;

	//����ÿ��push��������һ����ptr������ Ҳ���ǻ��Զ�����һ��ָ�������
	FooPtr foo_ptr(new Foo(2));	//���ʱ��use_cout���Ǵ���һ��1
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_vec.push_back(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	foo_set.insert(foo_ptr);
	cout<<"use_count:"<<foo_ptr.use_count()<<endl;
	//��������3��

	//����reset֮���ǽ�����ֵ����Ϊ1
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

	//������unique��Ŀ����˵�����ptr��use_countΪ1��
	boost::shared_ptr<int> spi(new int(123));
	assert(spi);
	assert(spi.unique());
	boost::shared_ptr<int> spi_2(new int(12));
	assert(spi_2.unique());
	assert(spi.unique());

	typedef vector<boost::shared_ptr<int> > vs;
	vs vec_share_ptr(10);//����ָ��vector������
	cout<<"size = "<<vec_share_ptr.size();
	int i = 0;
	//��10�� share_ptr���й���
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
1�����ֻ����A����������B�࣬�������õĻ���û������ģ����������������ڴ�ռ���ͷ��ڴ�ռ䣻
2��
*/
void test_weak_ptr()
{
	boost::shared_ptr<A> x(new A());
	cout<<"x.use_count() = "<<x.use_count()<<endl;
	x->b = boost::shared_ptr<B>(new B());
	cout<<"x.use_count() = "<<x.use_count()<<endl;
	cout<<"x->b.use_count() = "<<x->b.use_count()<<endl;
	x->b->a = x;//���ʱ�� �Ⱥ� ��ߵ�����x
	//����ǲ���weak_ptr����ʹ�õ���weak_ptr������
	//weak_ptr��Ҫ��share_ptr�н��и�ֵ�����ģ�
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