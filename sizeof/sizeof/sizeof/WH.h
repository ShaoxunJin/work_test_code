/******************************************************************
1����Ҫ�����WHӦ�ò�Ĵ���������ʹ��
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

//�ṹ�����нṹ��
struct struct_contain_struct
{
	int a;
	struct_contain_struct();
};

ostream& operator<<(ostream& os, WH4A_LOC_ENUM loc);
const char * WHenum2str(const WH4A_LOC_ENUM& t);


//class WH : public boost::enable_shared_from_this compile failed.
//enable_shared_from_this�����ģ���� ���Ҫ�ں������<WH>
class WH : public boost::enable_shared_from_this<WH>
{
public:
	WH(int i_nbr, WH4A_LOC_ENUM from, WH4A_LOC_ENUM to);
	WH(int i_nbr);
	WH(char* name);
	WH();
	~WH();

	//��̬������Ա������ȷ���� ����������Ϊ����ĳ��Ƚ��и�ֵ
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

	//���ز�����
	int operator+(int nbr);
	int operator*(int nbr);

	boost::shared_ptr<WH> function_return_wh();
	void optimise_route(WH4A_LOC_ENUM from, WH4A_LOC_ENUM to);
	void reset_m_matrix();
	WH4A_LOC_ENUM from();
	WH4A_LOC_ENUM to();

	//�ݹ麯������
	void digui_function(int input);

	//���Աģ�� ����ģ������������ ������ʵ�ʵ��õ�ʱ��ֻ����һ������
	//�ο�GCS REFLECTION_WRAPPER_CLASS
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

	//��ֵ���캯��
	WH& operator=(const WH& rhs);
	char *pBuffer;//ָ��̬������ڴ� �����Ļ�������������ط��������붯̬�ڴ� �Ǿ��ڹ��캯�����

protected:
private:
	//��ֵ���캯��������˽�б����� Ŀ����Ϊ���ڶ���֮��ĸ�ֵ�����в�����Ĭ�ϵĸ�ֵ���죨ǳ������
	//WH& operator=(const WH&);
	int m_nbr;
	vector<SMEE_BOOL> vec_bool;
	vector< boost::shared_ptr<WH> > m_link;

	//�����������ʶ��ǰ��λ֮���Ƿ�����Ĳ���
	//��Ҫ����ʵ�ʵ�Ӳ�����������ȷ��
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

	//��������ַ���ָ�� �������е�ʱ��ᱨ undefined
	function_out;
}

void tt_digui_for();

void tt_digui_result();

//boost::test
//boost::any ������������ͣ�
//boost::any_cast(any&& operand)ͨ��any_castת��Ϊ���������
//����ǰ������֪���������

//�����T����һ�� ���������Ĳ���ֵ��
//�����T���Ͳ�һ�� �����T��ֵ
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

//����ģʽ����ʵ��
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
//Product::��Ʒ���װ�ӿڣ������Ʒ�ĳ���ӿ�
//ConcreteProductA�������Ʒ��ʵ��product
//ConcreteProductB�������Ʒ��ʵ��product
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

//��ֵ���캯��
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

//����۲���Ҫȥ��ȡ����ĵ�״̬
//�������Ҫ��������Ķ���
class SUBJECT;//���������û�з���ǰ��Ļ� ��Ҫ�����������ǰ���������
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

//subject���ʱ��Ҫע�᲻ͬ�Ĺ۲����
//������ʱ��һ��Ҫ������observe
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