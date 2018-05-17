#include "stdafx.h"
#include "template.h"

MC_INSTANCE(TEMPLATE_MC_STRUCT)

void template_function()
{
	cout<<sizeof(min_calculation(1.0, 2.0))<<endl;
	cout<<sizeof(min_calculation(1, 5))<<endl;
	cout<<5.0 * min_calculation(1.0, 2.0)<<endl;
	double a = 5.123456;
	cout<<a<<endl;
	cout<<setprecision(4)<<a<<endl;
	cout<<setiosflags(ios::fixed)<<setprecision(2)<<a<<endl;
	cout<<setiosflags(ios::fixed)<<setprecision(4)<<a<<endl;  //采用固定小数点数输出
}

void custom_map()
{
	function_in;
	//这里要有类型比较
	std::map<std::pair<int, int>, int, comp> m_map_pair_int;
	m_map_pair_int.insert(std::make_pair(std::make_pair(1, 2), 12));
	m_map_pair_int.insert(std::make_pair(std::make_pair(5, 6), 56));
	m_map_pair_int.insert(std::make_pair(std::make_pair(2, 5), 25));
	//这里产生迭代的时候也要有com
	//std::map<std::pair<int, int>, int, comp>::iterator iter = m_map_pair_int.find(std::make_pair(2,5));
	std::map<std::pair<int, int>, int, comp>::iterator iter = m_map_pair_int.begin();
	while (iter != m_map_pair_int.end())
	{
		cout<<dec<<iter->second<<endl;
		++iter;
	}
	if (m_map_pair_int.end() == iter)
	{
		cout<<"find failed !!!!"<<endl;
	}
	else
	{
		cout<<"find success !"<<endl;
	}

	std::map<st_comp_custom, int, st_comp_custom> m_map_st_int;
	m_map_st_int.insert(std::make_pair(st_comp_custom(1,2), 12));
	m_map_st_int.insert(std::make_pair(st_comp_custom(5,6), 56));
	m_map_st_int.insert(std::make_pair(st_comp_custom(3,4), 34));

	std::map<st_comp_custom, int, st_comp_custom>::iterator iter_st = m_map_st_int.begin();
	while ( iter_st != m_map_st_int.end())
	{
		cout<<iter_st->first.a<<","<<iter_st->first.b<<","<<iter_st->second<<endl;
		++iter_st;
	}

	function_out;
}

void vector_delete()
{
	vector<int> vec_delete(5);
	cout<<vec_delete.size()<<endl;
	int iNbr = static_cast<int>(vec_delete.size());
	for (int i = 0; i < iNbr; ++i)
	{
		vec_delete[i] = i;
		cout<<"i = "<<i<<endl;
	}

	for (vector<int>::iterator iter = vec_delete.begin();
		iter != vec_delete.end();)
	{
		cout<<*iter<<endl;
		if (2 == *iter)
		{
			iter = vec_delete.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iNbr = static_cast<int>(vec_delete.size());
	for(int i = 0; i < iNbr; ++i)
	{
		cout<<i<<":"<<vec_delete[i]<<endl;
	}
}


ostream& operator<<(ostream&os, TEMPLATE_MC_STRUCT& mc)
{
	os<<"mc.iTemplateMcA = "<<mc.iTemplateMcA<<endl
		<<"mc.iTemplateMcB = "<<mc.iTemplateMcB<<endl
		<<"mc.iTemplateMcC = "<<mc.iTemplateMcC<<endl
		<<"mc.cTemplateMcD = "<<mc.cTemplateMcD<<endl;

	return os;
}

void test_template_mc_changed()
{
	function_in;
	TEMPLATE_MC_STRUCT mc_original = {1,2,3,"jin"};
	TEMPLATE_MC_STRUCT mc_update = {4,5,6,"xun"};
	cout<<mc_original;

	MC_PARSE_START(TEMPLATE_MC_STRUCT);
	MC_SET_PARAMETER(iTemplateMcA, iTemplateMcC);
	MC_SET_CHANGED(TEMPLATE_MC_STRUCT);
	MC_PARSE_END;

	mc_original = MC_CHANGED(mc_original, mc_update);
	cout<<mc_original;

	//initialize vector and map
	VECTOR_INITIALIZE::VECTOR_MAKE_UI_UI_PAIR tt_vector_map = VECTOR_INITIALIZE::VECTOR_MAKE_UI_UI_PAIR();
	cout<<"tt_vector_map.size() = "<<tt_vector_map.size()<<endl;
	tt_vector_map.push_back(make_pair(-1,-1));
	tt_vector_map.push_back(make_pair(-2,-3));
	tt_vector_map.push_back(make_pair(-4,-5));
	cout<<"tt_vector_map.size() = "<<tt_vector_map.size()<<endl;
	for (VECTOR_INITIALIZE::VECTOR_MAKE_UI_UI_PAIR::iterator iter = tt_vector_map.begin();
		iter != tt_vector_map.end();
		++iter)
	{
		cout<<"first = "<<static_cast<int>((*iter).first)<<", second = "<<(*iter).second<<endl;
	}

	function_out;
}