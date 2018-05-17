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

//����һ�������� ͬʱ�����TEMPLATE_MC_STRUCT���е����в�����Ϣ
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
/*��ģ��
/************************************************************************/
//����һ����ģ�����int double char string ����ģ��
//�����ģ�����ʵ����
//ʵ����main�����н���
/*
 *	ģ����
 */
template <typename TYPE_1, typename TYPE_2>
class template_TYPE
{
public:
	template_TYPE(TYPE_1 TYPE_NBR, typename TYPE_2);
	~template_TYPE();

	string class_name();

	//����TYPE_1������
	TYPE_2& return_type();
	//����map
	map<TYPE_1, TYPE_2> m_map;

//private:
	TYPE_1 m_type_1;
	TYPE_2 m_type_2;
};

//�������Ҫ������֮�����<TYPE_1>���ܱ���ͨ��
//ͬʱinline�������������h�ļ��У�ģ�����ļ����������ͷ�ļ��У�
//����ʹ�ó�ʼ���б���г�ʼ����Ա����
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


//�º���
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
	//�������� Ŀ�����ں������ڲ���ı䴫�����Ķ���
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
��map�����Զ����custom������Ϊkey��ʱ����Ҫ��map�е�Ĭ��ִ�е�˳��
�������� ����operator()�º����ķ�ʽʵ��
����ֱ���keyΪpair���ͺ�struct���������д���
******************************************************************/

struct comp 
{
	typedef std::pair<int, int> value_type;
	bool operator()(const value_type &ls, const value_type &rs)
	{
		return ls.first < rs.first || (ls.first == rs.first && ls.second < rs.second);
	}
};

//���Զ�������struct��Ϊ�Զ������Ͳ��뵽map��
struct st_comp_custom
{
	int a, b;
	st_comp_custom(int x, int y):a(x), b(y){}
	st_comp_custom():a(0),b(0){}

	//�º���ʵ�ֱȽ�
	//Ĭ������� map�е�less��true �����淵�ص��ǽ��н���
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

	//�������vector�еı���ʲôʱ��ʼ�䶯�ˣ�����
	for (MEMORY_SECTION_ARRAY::iterator it = memory_section_array.begin();
		it != memory_section_array.end();
		++it)
	{
		//��һ����ʲôԭ��
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

//��ʼ��ģ����ľ�̬��Ա���� ͬʱ����ģ�����ʵ����
#define MC_INSTANCE(mc_struct_type) \
	template <>\
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY MC_TEMPLATE<mc_struct_type>::memory_section_array = \
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY();\
	SMEE_BOOL MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_FALSE;

/*
* ��ʼ������������
*/
#define MC_PARSE_START(mc_struct_type) \
{ \
	MC_TEMPLATE<mc_struct_type>::MEMORY_SECTION_ARRAY& section_array = MC_TEMPLATE<mc_struct_type>::memory_section_array; \
	mc_struct_type t; \
	unsigned int start_add = reinterpret_cast<unsigned int>(&t);\
	section_array.clear();

/******************************************************************
1����ʼ���ö������
******************************************************************/
#define MC_SET_PARAMETER(start_parameter, end_parameter) \
	assert(reinterpret_cast<unsigned int>(&(t.start_parameter)) <= reinterpret_cast<unsigned int>(&(t.end_parameter)));\
	section_array.push_back(make_pair(reinterpret_cast<unsigned int>(&(t.start_parameter)) - start_add,\
	reinterpret_cast<unsigned int>(&(t.end_parameter)) + sizeof(t.end_parameter) - reinterpret_cast<unsigned int>(&(t.start_parameter))));

/******************************************************************
���õ�������
******************************************************************/
#define MC_SET_SIGNLE_PARAMETER(parameter) \
	MC_SET_PARAMETER(parameter, parameter);

/******************************************************************
�����Ƿ����ı�־λ
******************************************************************/
#define MC_SET_CHANGED(mc_struct_type) \
	MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_TRUE;

#define MC_SET_UNCHANGED(mc_struct_type) \
	MC_TEMPLATE<mc_struct_type>::changed_flag = SMEE_FALSE;

#define MC_PARSE_END }


/******************************************************************
����ʹ�÷�ʽ��
MC_INSTANCE(type)
MC_PARSE_START
MC_SET_CHANGED
MC_SET_SIGNLE_PARAMETER
MC_SET_PARAMETER
MC_PARSE_END

return MC_CHANGED();
�����Ǿ����ʹ������
******************************************************************/


void test_template_mc_changed();


struct VECTOR_INITIALIZE
{
	typedef pair<unsigned int, unsigned int> MAKE_UI_UI_PAIR;
	typedef vector<MAKE_UI_UI_PAIR> VECTOR_MAKE_UI_UI_PAIR;
};


#endif
