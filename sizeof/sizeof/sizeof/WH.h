/******************************************************************
1、主要是针对WH应用层的代码仿真测试使用
******************************************************************/
#ifndef WH_H
#define WH_H

#include "head_file.h"
#include "boost/shared_ptr.hpp"
#include "boost/any.hpp"
#include "boost/function.hpp"
#include "boost/functional/factory.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/bind.hpp"
#include "map_pair.h"

#define function_in cout<<">>>>>>"<<__FUNCTION__<<endl;
#define function_out cout<<"<<<<<<<"<<__FUNCTION__<<endl;

#define _WH_DEBUG_INFO_

template <typename T>
T& type_change(boost::any &para);

//结构体中有结构体
struct struct_contain_struct
{
	int a;
	struct_contain_struct();
};

ostream& operator<<(ostream& os, WH4A_LOC_ENUM loc);
const char * WHenum2str(const WH4A_LOC_ENUM& t);


//class WH : public boost::enable_shared_from_this compile failed.
//enable_shared_from_this这个是模板类 因此要在后面跟上<WH>
class WH : public boost::enable_shared_from_this<WH>
{
public:
	WH(int i_nbr, WH4A_LOC_ENUM from, WH4A_LOC_ENUM to);
	WH(int i_nbr);
	WH(char* name);
	WH();
	~WH();

	//静态常量成员变量是确定的 可以用来作为数组的长度进行赋值
	static const int iArrayNbr = 10;
	int array[iArrayNbr];
	
	typedef deque<WH4A_LOC_ENUM> ROUTE_LOC;
	typedef pair<unsigned int, unsigned int> WH_PAIR_UI_UI;
	typedef vector<WH_PAIR_UI_UI> WH_VECTOR_PAIR_UI_UI;
	
	static WH_VECTOR_PAIR_UI_UI wh_memory_section;

	SMEE_BOOL result();
	void add_link(boost::shared_ptr<WH> ptr);
	SMEE_BOOL out_put_type(boost::any &para);

	void getNbr(int *number);

	//重载操作符
	int operator+(int nbr);
	int operator*(int nbr);

	boost::shared_ptr<WH> function_return_wh();
	void optimise_route(WH4A_LOC_ENUM from, WH4A_LOC_ENUM to);
	void reset_m_matrix();
	WH4A_LOC_ENUM from();
	WH4A_LOC_ENUM to();

	//递归函数测试
	void digui_function(int input);

	//类成员模板 测试模板中两个参数 但是在实际调用的时候只给了一个参数
	//参考GCS REFLECTION_WRAPPER_CLASS
	template<typename TYPE_1, typename TYPE_2>
	static void tt_template_two_parameters(TYPE_1 T1, TYPE_2 T2);

	char* tt_strcpy(char* Dest, const char* Src);

	//result motion is finish test
	typedef boost::shared_ptr<WH> WH_PTR;
	void add_attch_link(WH_PTR wh_ptr);
	SMEE_BOOL motion_is_finished();
	std::list<WH_PTR> m_attached_link;
	int m_motion_finished;

	SMEE_BOOL motion_result();

	//赋值构造函数
	WH& operator=(const WH& rhs);
	char *pBuffer;//指向动态申请的内存 这样的话则必须在其他地方给他申请动态内存 那就在构造函数里吧

protected:
private:
	//赋值构造函数声明在私有变量中 目的是为了在对象之间的赋值过程中不采用默认的赋值构造（浅拷贝）
	//WH& operator=(const WH&);
	int m_nbr;
	vector<SMEE_BOOL> vec_bool;
	vector< boost::shared_ptr<WH> > m_link;

	//这个是用来标识当前工位之间是否允许的操作
	//需要根据实际的硬件情况来进行确定
	SMEE_BOOL m_matrix[WH4A_LOC_MAX][WH4A_LOC_MAX];
	WH4A_LOC_ENUM m_from;
	WH4A_LOC_ENUM m_to;
	void m_optimise_route(WH4A_LOC_ENUM from,
						WH4A_LOC_ENUM to,
						ROUTE_LOC& route_loc);
	void m_cancel_buff_pos_as_route( WH4A_LOC_ENUM from, WH4A_LOC_ENUM to );

	void m_dfs(WH4A_LOC_ENUM loc,
		WH4A_LOC_ENUM target,
		SMEE_BOOL searched[WH4A_LOC_MAX],
		ROUTE_LOC& dfs_route,
		ROUTE_LOC& optimize_route);
	int m_recursion(int input);
};
template<typename TYPE_1, typename TYPE_2>
void WH::tt_template_two_parameters(TYPE_1 T1, TYPE_2 T2)
{
	function_in;

	ostringstream os;
	os<<"TYPE_1 : "<<typeid(T1).name()<<",TYPE_2 : "<<typeid(T2).name()<<endl;
	os<<"TYPE_1 value : "<<T1<<",TYPE_2 value : "<<T2<<endl;
	cout<<os.str()<<endl;

	//如果采用字符串指针 则在运行的时候会报 undefined
	function_out;
}

void tt_digui_for();

void tt_digui_result();

//boost::test
//boost::any 声明任意的类型；
//boost::any_cast(any&& operand)通过any_cast转换为任意的类型
//但是前提是你知道这个类型

//如果和T类型一样 则输出后面的参数值；
//如果和T类型不一样 则输出T的值
template<typename T>
T any_test(boost::any any_value, T t_value)
{
	if(any_value.type() == typeid(t_value))
	{
		return boost::any_cast<T>(any_value);
	}
	else
	{
		return t_value;
	}
};

string& any_test_1(int para);

//工厂模式抽象实现
template <typename T_ID, typename T_OBJECT>
class ObjectFactory
{
public:
	typedef boost::function<T_OBJECT* ()> CreateObjectType;
	typedef std::map<T_ID, CreateObjectType> ObjectCreator_map;

	void RegisterObjectCreator(const T_ID& id, const CreateObjectType& objectCreator)
	{
		mapObjectCreator[id] = objectCreator;
	}

	T_OBJECT* makeObject(const T_ID& id)
	{
		ObjectCreator_map::iterator iter = mapObjectCreator.find(id);
		if (iter != mapObjectCreator.end())
		{
			return (iter->second)();
		}
		else
		{
			return NULL;
		}
	}
private:
	ObjectCreator_map mapObjectCreator;
};
//
//Product::产品类封装接口，定义产品的抽象接口
//ConcreteProductA：具体产品类实现product
//ConcreteProductB：具体产品类实现product
class Product
{
public:
	explicit Product()
	{
	};
	virtual ~Product()
	{
	};
	virtual void do_something() = 0;
protected:
private:
};

typedef boost::shared_ptr<Product> ptrProduct;

class ProductA : public Product
{
public:
	ProductA();
	~ProductA();
	void do_something();
};

class ProductB : public Product
{
public:
	ProductB();
	~ProductB();
	void do_something();
};

void factor_function_test();

struct compare_operate_less
{
	int operator++(int nbr)
	{
		return ++nbr;
	}

	bool operator()(int left, int right) const
	{
		return left < right;
	}
	
};

struct compare_operate_plus
{
	int operator++(int nbr)
	{
		return ++nbr;
	}
};


class Y : public boost::enable_shared_from_this<Y>
{
public:
	boost::shared_ptr<Y> f()
	{
		return shared_from_this();
	}

	void fcn_out(const string _string)
	{
		cout<<__FUNCTION__<<_string<<endl;
	}
};


//boost::bind & boost::function & callback
class Manager
{
public:
	Manager();

	void registerCallBack(boost::function<void (int)> f);
	void runCallBack(int i);
	void subscribe_runCallBack(boost::function<void (int)> f, int i);
	void fcn(int i);

protected:
private:
	vector<boost::function<void (int)>> fds;
};

class Node : public boost::enable_shared_from_this<Node>
{
public:
	Node();
	Node(Manager *managerPtr);
	void A(int i);
	void B(int i);
	void C(int i);
	void start();

	Manager *pManager;
};

class Obj : public boost::enable_shared_from_this<Obj>
{
public:
	Obj(Manager * pManager);
	void start();
	void fun_1(int i);
	void fun_2(int i);

private:
	Manager* managerPtr;
};

void test_callback();

typedef void (*ptrFun)(int);

void myFun1(int i = 1);
void myFun2(int i = 2);
void myFun3(int i = 3);

void myCallBackFun(ptrFun fp, int);

//赋值构造函数
class OPERATOR_EQUAL_CLASS
{
public:
	OPERATOR_EQUAL_CLASS(int iNbr);
	~OPERATOR_EQUAL_CLASS();
	
	//OPERATOR_EQUAL_CLASS& operator=(const OPERATOR_EQUAL_CLASS& rhs);

	char* pBUFFER;
	int iSize;

protected:
private:
};

class TT_STATIC
{
public:
	//static int iStaticNbr;
	TT_STATIC()
	{
		cout<<__FUNCTION__<<endl;
	}

	~TT_STATIC()
	{
		cout<<__FUNCTION__<<endl;
	}
	
protected:
private:
	
};

//subject observe pattern
class OBSERVE
{
public:
	OBSERVE(){}
	virtual ~OBSERVE(){}
	virtual void update(int) = 0;
	int currentState;
};

//具体观察类要去获取主题的的状态
//因此这里要依赖具体的对象
class SUBJECT;//如果类声明没有放在前面的话 则要在这里进行下前向的声明；
class ConcreteOBSERVE_1 : public OBSERVE
{
public:
	ConcreteOBSERVE_1(SUBJECT* pSubject);
	~ConcreteOBSERVE_1();

	void update(int new_value);
	
private:
	SUBJECT *m_pSubjec_1;
	int m_ObserveState;
};

class ConcreteOBSERVE_2 : public OBSERVE
{
public:
	ConcreteOBSERVE_2(SUBJECT* pSubject);
	~ConcreteOBSERVE_2();

	void update(int new_value);
	
private:
	SUBJECT* m_pSubject_2;
	int m_ObserveState;
};

//subject这个时候要注册不同的观察对象
//因此这个时候一定要依赖于observe
class SUBJECT
{
public:
	SUBJECT(){}
	virtual ~SUBJECT(){}

	virtual void registerSubject(OBSERVE*) = 0;
	virtual void removeSubject(OBSERVE*) = 0;
	virtual void notify() = 0;
};

class ConcreteSUBJECT : public SUBJECT
{
public:
	ConcreteSUBJECT(int state);
	~ConcreteSUBJECT();

	void registerSubject(OBSERVE* pObserve);
	
	void removeSubject(OBSERVE* pObserve);
	
	void notify();
	
	void setState(int state);
	
	int& getState();

private:
	list<OBSERVE*> m_ObserveList;
	int m_state;
};


void test_subject_observe();


class BASE
{
public:
	BASE(int iNbr)
	{
		cout<<__FUNCTION__<<" = "<<iNbr<<endl;
	}
	virtual ~BASE(){}
protected:
private:
};

class BASE_DERIVE : public BASE
{
public:
	BASE_DERIVE(int iNbr) : BASE(iNbr)
	{
		cout<<__FUNCTION__<<" = "<<iNbr<<endl;
	}
	~BASE_DERIVE(){}
};


#endif