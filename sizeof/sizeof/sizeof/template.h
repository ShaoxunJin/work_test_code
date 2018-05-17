#ifndef TEMPLATE_H
#define TEMPLATE_H

//#include "head_file.h"
#include "size_of.h"
#include <map>
#include <algorithm>
using namespace std;

typedef map<int, int> map_int_int;

typedef struct
{
	int iTemplateMcA;
	int iTemplateMcB;
	int iTemplateMcC;
	char cTemplateMcD[4];
}TEMPLATE_MC_STRUCT;

//重载一个操作符 同时输出《TEMPLATE_MC_STRUCT》中的所有参数信息
ostream& operator<<(ostream& os, TEMPLATE_MC_STRUCT& mc);

template <typename type>
type min_calculation(type T1, type T2)
{
	/*return T1 < T2 ? T1 : T2;*/
	if (T1 < T2)
	{
		return T1;
	}
	else if (T1 >= T2)
	{
		return T2;
	}
}

void template_function();

/************************************************************************/
/*类模板
/************************************************************************/
//创建一个类模板包含int double char string 的类模板
//针对类模板进行实例化
//实际在main函数中进行
/*
 *	模板类
 */
template <typename TYPE_1, typename TYPE_2>
class template_TYPE
{
public:
	template_TYPE(TYPE_1 TYPE_NBR, typename TYPE_2);
	~template_TYPE();

	string class_name();

	//返回TYPE_1的引用
	TYPE_2& return_type();
	//创建map
	map<TYPE_1, TYPE_2> m_map;

//private:
	TYPE_1 m_type_1;
	TYPE_2 m_type_2;
};

//这里必须要在类名之后添加<TYPE_1>才能编译通过
//同时inline函数必须放置在h文件中（模板类文件必须放置在头文件中）
//尽量使用初始化列表进行初始化成员变量
template <typename TYPE_1, typename TYPE_2>
template_TYPE<TYPE_1, TYPE_2>::template_TYPE(TYPE_1 TYPE_NBR_1, TYPE_2 TYPE_NBR_2)
							   :m_type_1(TYPE_NBR_1)
							   ,m_type_2(TYPE_NBR_2)
{
	cout<<"\n>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
	cout<<"Construct template class"<<endl;
	cout<<"TYPE_1:type = "<<typeid(TYPE_1).name()<<endl;
	cout<<"TYPE_2:type = "<<typeid(TYPE_2).name()<<endl;
}

template <typename TYPE_1, typename TYPE_2>
inline template_TYPE<TYPE_1, TYPE_2>::~template_TYPE()
{
	cout<<"Deconstruct template class"<<endl;
}

template <typename TYPE_1, typename TYPE_2>
string template_TYPE<TYPE_1, TYPE_2>::class_name()
{
	//cout<<"template_class_name : "<<typeid(TYPE_1).name()<<endl;
	//cout<<"template_class_name ;"<<endl;
	return typeid(TYPE_1).name();
}

template <typename TYPE_1, typename TYPE_2>
TYPE_2& template_TYPE<TYPE_1, TYPE_2>::return_type()
{
	return m_type_2;
}


//仿函数
template<typename type_1, typename type_2>
class value_finder
{
public:
	value_finder(type_1 value_1, type_2 value_2)
		: m_value_1(value_1)
		, m_value_2(value_2)											
	{
		cout<<"This is Contruction ......"<<endl;
		cout<<"m_value_1 = "<<m_value_1<<endl;
		cout<<"m_value_2 = "<<m_value_2<<endl;
	}
	//常量引用 目的是在函数体内不想改变传进来的对象
	bool operator()(typename const std::map<type_1, type_2>::value_type& p)
	{
		return p.second == m_value_2;
	}

private:
	const type_1 m_value_1;
	const type_2 m_value_2;
};


/******************************************************************
MAP CUSTOM
当map采用自定义的custom类型作为key的时候需要对map中的默认执行的顺序
进行设置 采用operator()仿函数的方式实现
下面分别是key为pair类型和struct类型来进行传递
******************************************************************/

struct comp 
{
	typedef std::pair<int, int> value_type;
	bool operator()(const value_type &ls, const value_type &rs)
	{
		return ls.first < rs.first || (ls.first == rs.first && ls.second < rs.second);
	}
};

//以自定义类型struct作为自定义类型插入到map中
struct st_comp_custom
{
	int a, b;
	st_comp_custom(int x, int y):a(x), b(y){}
	st_comp_custom():a(0),b(0){}

	//仿函数实现比较
	//默认情况下 map中的less是true 而下面返回的是进行降序
	bool operator()(const st_comp_custom& a, const st_comp_custom& b)
	{
		return a.a > b.a || (a.a == b.a && a.b > b.b);
	}

	//friend bool operator<(const st_comp_custom& a, const st_comp_custom& b);
};

//inline bool st_comp_custom::operator<(const st_comp_custom& a, const st_comp_custom& b)
//{
//	return a.a < b.a || (a.a == b.a && a.b < b.b);
//}


void custom_map();

void vector_delete();

/******************************************************************
definition
******************************************************************/
template<typename MC_STRUCT_TYPE>
struct MC_TEMPLATE
{
	typedef pair<unsigned int, unsigned int> MEMORY_SECTION;
	typedef vector<MEMORY_SECTION> MEMORY_SECTION_ARRAY;
	static MEMORY_SECTION_ARRAY memory_section_array;
	static SMEE_BOOL changed_flag;
	static MC_STRUCT_TYPE mc_changed(MC_STRUCT_TYPE old_mc, MC_STRUCT_TYPE new_mc);
};

template<typename MC_STRUCT_TYPE>
MC_STRUCT_TYPE MC_TEMPLATE<MC_STRUCT_TYPE>::mc_changed(MC_STRUCT_TYPE old_mc, MC_STRUCT_TYPE new_mc)
{
	MC_STRUCT_TYPE* mc_original = changed_flag ? &old_mc : &new_mc;
	MC_STRUCT_TYPE* mc_update = changed_flag ? &new_mc : &old_mc;

	//下面这个vector中的变量什么时候开始变动了？？？
	for (MEMORY_SECTION_ARRAY::iterator it = memory_section_array.begin();
		it != memory_section_array.end();
		++it)
	{
		//这一步是什么原理
		memcpy(reinterpret_cast<char*>(mc_original) + it->first,
			reinterpret_cast<char*>(mc_update) + it->first,it->second);
	}
	return *mc_original;
}

template<typename MC_STRUCT_TYPE>
MC_STRUCT_TYPE MC_CHANGED(MC_STRUCT_TYPE old_mc, MC_STRUCT_TYPE new_mc)
{
	return MC_TEMPLATE<MC_STRUCT_TYPE>::mc_changed(old_mc, new_mc);
}

//初始化模板类的静态成员变量 同时对类模板进行实例化
#define MC_INSTANCE(mc_struct_type) \
	template <>\
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY MC_TEMPLATE<mc_struct_type>::memory_section_array = \
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY();\
	SMEE_BOOL MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_FALSE;

/*
* 开始解析机器常数
*/
#define MC_PARSE_START(mc_struct_type) \
{ \
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY& section_array = MC_TEMPLATE<mc_struct_type>::memory_section_array; \
	mc_struct_type t; \
	unsigned int start_add = reinterpret_cast<unsigned int>(&t);\
	section_array.clear();

/******************************************************************
1、开始设置多个参数
******************************************************************/
#define MC_SET_PARAMETER(start_parameter, end_parameter) \
	assert(reinterpret_cast<unsigned int>(&(t.start_parameter)) <= reinterpret_cast<unsigned int>(&(t.end_parameter)));\
	section_array.push_back(make_pair(reinterpret_cast<unsigned int>(&(t.start_parameter)) - start_add,\
	reinterpret_cast<unsigned int>(&(t.end_parameter)) + sizeof(t.end_parameter) - reinterpret_cast<unsigned int>(&(t.start_parameter))));

/******************************************************************
设置单个参数
******************************************************************/
#define MC_SET_SIGNLE_PARAMETER(parameter) \
	MC_SET_PARAMETER(parameter, parameter);

/******************************************************************
设置是否变更的标志位
******************************************************************/
#define MC_SET_CHANGED(mc_struct_type) \
	MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_TRUE;

#define MC_SET_UNCHANGED(mc_struct_type) \
	MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_FALSE;

#define MC_PARSE_END }


/******************************************************************
具体使用方式：
MC_INSTANCE(type)
MC_PARSE_START
MC_SET_CHANGED
MC_SET_SIGNLE_PARAMETER
MC_SET_PARAMETER
MC_PARSE_END

return MC_CHANGED();
下面是具体的使用例子
******************************************************************/


void test_template_mc_changed();


struct VECTOR_INITIALIZE
{
	typedef pair<unsigned int, unsigned int> MAKE_UI_UI_PAIR;
	typedef vector<MAKE_UI_UI_PAIR> VECTOR_MAKE_UI_UI_PAIR;
};


#endif
