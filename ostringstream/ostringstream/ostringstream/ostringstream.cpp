// ostringstream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

class Graph
	{
	public:
		Graph() {s_gCount++;}
		int x;
		~Graph(){s_gCount--;}
		void function();
		//virtual int drawOut();
		int getTotalCount() {return s_gCount;}
	private:
		int m_x;
		int m_y;
		int s_gCount;
	private:
		int private_num ;
	};
void Graph::function()
{
	char *string = "The function is OK";
	cout<<string<<endl;
	//return string;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 6;
	int s_gCount = 10;
	char *name = "jinshaoxun";
	ostringstream os;//定义输出流 目的是将不同类型的数据放置在一起进行输出
	//这里有两种定义方式
	//1、ostringstream os		这一种方式比较简单 网上貌似见到最多的就是这一种
	//2、ostringstream os("")  因项目中使用的都是第二种 还是尽量使用第二种
	os<<name<<"   "<<num;
	cout<<os.str()<<endl;

	os.str("");			//其实这个目的是清空os内存储的内容,在后续的输出中一定要进行os.str("")
	os<<num<<"   "<<name ;
	cout<<os.str()<<endl;

	cout<<"Test"<<endl;
	/*下面是用Graph定义一个A类；
	Graph A;
	A.x = 10;
	cout<<A.x<<endl;
	A.function();
	*/

	//下面需要采用继承的方式进行一些简单的理解；
	class A:public Graph
	{
	public:
		char *name;
		int fun()
		{
			return 10000;
		}
		int num;

	};
	A body;
	body.num = 10;
	cout<<body.num<<endl;
	cout<<body.fun()<<endl;
	body.function();

	cout<<"Sizeof(int) = "<<sizeof(int)<<endl;

	cout<<"/ = "<<(1./3)<<endl;
	cout<<"sizeof(0xff80000000) = "<<sizeof(0xff80000000)<<endl;


	double theta = atan2(1.0,1.0);
	cout<<"theta = "<<theta/3.1415926*180<<endl;

	system("pause"); 
	return 0;
}