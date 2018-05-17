// class_static.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

class distance_calculation
	{
	public:
		double b,c;
		static double a;
		static int int_a;
		static int fun();			//这里要是static删除的最后主函数中的就不能直接调用；

	private:
		double distance_result(double,double,double);
	};
//明确下面的几个一直到主函数之前的都是对类成员进行初始化 因此都是可行的
//而不是直接通过类名进行对非静态类型进行调用；
double distance_calculation::distance_result(double a, double b, double c)
{
	double distance = sqrt(a*a+b*b+c*c);
	cout<<"The distance = "<<distance<<endl;
	return distance;
}
//初始化成员函数
int distance_calculation::fun()
{
	return 10;
}
//初始化成员函数
int distance_calculation::int_a = 10;
double distance_calculation::a = 0.1;

int _tmain(int argc, _TCHAR* argv[])
{
	double a,b,c;

	//distance_calculation example_distance;//这个目的就是创建一个类
	//创建了该类之后就可以直接采用.或者是->进行调用内部的成员

	cout<<"Please input three values of this points"<<endl;
	cin>>a;
	cin>>b;
	cin>>c;
	cout<<distance_calculation::fun()<<endl;//这里直接采用的是最初的类对静态成员进行调用
	//对于非静态成员则是不能进行调用的
	return 0;
}

