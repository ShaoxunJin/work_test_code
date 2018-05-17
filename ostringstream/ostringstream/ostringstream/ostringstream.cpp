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
	ostringstream os;//��������� Ŀ���ǽ���ͬ���͵����ݷ�����һ��������
	//���������ֶ��巽ʽ
	//1��ostringstream os		��һ�ַ�ʽ�Ƚϼ� ����ò�Ƽ������ľ�����һ��
	//2��ostringstream os("")  ����Ŀ��ʹ�õĶ��ǵڶ��� ���Ǿ���ʹ�õڶ���
	os<<name<<"   "<<num;
	cout<<os.str()<<endl;

	os.str("");			//��ʵ���Ŀ�������os�ڴ洢������,�ں����������һ��Ҫ����os.str("")
	os<<num<<"   "<<name ;
	cout<<os.str()<<endl;

	cout<<"Test"<<endl;
	/*��������Graph����һ��A�ࣻ
	Graph A;
	A.x = 10;
	cout<<A.x<<endl;
	A.function();
	*/

	//������Ҫ���ü̳еķ�ʽ����һЩ�򵥵���⣻
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