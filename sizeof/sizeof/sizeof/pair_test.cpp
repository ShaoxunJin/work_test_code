#include "stdafx.h"
#include "map_pair.h"
#include "WH.h"

void map_pair_pair_test(void)
{
	//定义个pair类型
	/************************************************************************/
	/* 如下是采用typedef进行定义的 
	/* 采用personal_info作为一种类型来定义一个A和B
	/* 建议都采用typedef进行
	/************************************************************************/
	typedef pair<string,int> personal_info;
	personal_info A = make_pair("A",65);
	personal_info B = make_pair("B",66);
	cout<<"A.name = "<<A.first<<", A.No = "<<A.second<<endl;
	cout<<"B.name = "<<B.first<<", B.No = "<<B.second<<endl;

	/************************************************************************/
	/*如下是直接用pair进行定义一个personal_info
	/************************************************************************/
	//pair<string,int> personal_info;
	//personal_info = make_pair("A",65);
	//cout<<"personal_info.name = "<<personal_info.first<<", personal_info.No = "<<personal_info.second<<endl;
//auto_ptr
	map<string,int> map_jin;
	map_jin.insert(make_pair("C",67));
	map_jin.insert(make_pair("A",1111));
	map_jin.insert(make_pair("B",66));

	//这里可以查看下map是否执行sort操作
	map<string,int>::iterator it;
	for(it = map_jin.begin(); it != map_jin.end(); ++it)
	{
		cout<<"first = "<<it->first<<",second = "<<it->second<<endl;
	}
	//output
	/*first = A,second = 1111	
	first = B,second = 66
	first = C,second = 67	*/

	//it = map_jin.find("A");
	//if(it != map_jin.end())
	//{
	//	cout<<"A = "<<(*it).second<<endl;
	//	cout<<"A = "<<it->second<<endl;
	//}
	cout<<"map_jin.operator [](A) = "<<map_jin.operator []("A")<<endl;

	//std::list<int> dd;
}

void map_pair_station_string_2_enum(const string& loc)
{
	function_in(__FUNCTION__);
	pair<string, WH4A_LOC_ENUM> s_initialize[] = 
	{
		pair<string,WH4A_LOC_ENUM>("PORT", WH4A_LOC_PORT),
		pair<string,WH4A_LOC_ENUM>("LOAD_ROBOT", WH4A_LOC_LOAD_ROBOT),
		pair<string,WH4A_LOC_ENUM>("UNLOAD_ROBOT",WH4A_LOC_UNLOAD_ROBOT),
		pair<string,WH4A_LOC_ENUM>("PREALIGNER",WH4A_LOC_PREALIGNER),
		pair<string,WH4A_LOC_ENUM>("DISCHARGE",WH4A_LOC_DISCHARGE),
		pair<string,WH4A_LOC_ENUM>("WAFER_STAGE_CHUCK1",WH4A_LOC_WAFER_STAGE_CHUCK1),
		pair<string,WH4A_LOC_ENUM>("WAFER_STAGE_CHUCK2",WH4A_LOC_WAFER_STAGE_CHUCK2),
		pair<string,WH4A_LOC_ENUM>("TRACK",WH4A_LOC_TRACK)
	};
	
	map<string, WH4A_LOC_ENUM> string2enum(&s_initialize[0], &s_initialize[8]);
	map<string, WH4A_LOC_ENUM>::iterator iter = string2enum.find(loc);
	if (iter != string2enum.end())
	{
		cout<<enum2str(iter->second)<<endl;
	}
	else
	{
		cout<<"Find "<<loc<<" failed !"<<endl;
	}

	function_out(__FUNCTION__);
}


const char* enum2str(const WH4A_LOC_ENUM& t)
{
	const char* str = NULL;
	switch (t)
	{
	case WH4A_LOC_PORT: str = "WH4A_LOC_PORT";break;
	case WH4A_LOC_LOAD_ROBOT: str = "WH4A_LOC_LOAD_ROBOT";break;
	case WH4A_LOC_UNLOAD_ROBOT: str = "WH4A_LOC_UNLOAD_ROBOT";break;
	case WH4A_LOC_PREALIGNER: str = "WH4A_LOC_PREALIGNER";break;
	case WH4A_LOC_DISCHARGE: str = "WH4A_LOC_DISCHARGE";break;
	case WH4A_LOC_WAFER_STAGE_CHUCK1: str = "WH4A_LOC_WAFER_STAGE_CHUCK1";break;
	case WH4A_LOC_WAFER_STAGE_CHUCK2: str = "WH4A_LOC_WAFER_STAGE_CHUCK2";break;
	case WH4A_LOC_TRACK: str = "WH4A_LOC_TRACK";break;
	default:str = "INVALIDE ENUM VALUE,PLEASE CHECK";break;
	}

	return str;
}


void map_compare()
{
	map< int, string, compare_operate_less> tt_map;
	tt_map.insert(make_pair(3,"3"));
	tt_map.insert(make_pair(1,"1"));
	tt_map.insert(make_pair(2,"2"));
	cout<<"tt_map.size() = "<<tt_map.size()<<endl;
	for (map<int, string, compare_operate_less>::iterator iter = tt_map.begin();
		iter != tt_map.end();
		++iter)
	{
		cout<<iter->second<<endl;
	}
}

void multi_map_compare()
{
	cout<<">>>"<<__FUNCTION__<<endl;
	multimap<int, string> map_multi;
	map_multi.insert(make_pair(5, "2"));
	map_multi.insert(make_pair(3, "3"));
	map_multi.insert(make_pair(3, "33"));
	map_multi.insert(make_pair(5, "22"));
	int i = 0;
	for (multimap<int, string>::iterator iter = map_multi.begin();
		iter != map_multi.end();
		++iter, ++i)
	{
		cout<<"i = "<<i<<",first = "<<iter->first<<",second = "<<iter->second<<endl;
	}

	
	multimap<int, string>::iterator iter = map_multi.find(5);
	cout<<"map_multi.count(5) = "<<map_multi.count(5)<<endl;
	if (iter != map_multi.end())
	{
		cout<<"first = "<<iter->first<<", second = "<<iter->second<<endl;
	}
	else
	{
		printf("Find Error !\n");
	}


	cout<<"<<<"<<__FUNCTION__<<endl;
}