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
		static int fun();			//����Ҫ��staticɾ��������������еľͲ���ֱ�ӵ��ã�

	private:
		double distance_result(double,double,double);
	};
//��ȷ����ļ���һֱ��������֮ǰ�Ķ��Ƕ����Ա���г�ʼ�� ��˶��ǿ��е�
//������ֱ��ͨ���������жԷǾ�̬���ͽ��е��ã�
double distance_calculation::distance_result(double a, double b, double c)
{
	double distance = sqrt(a*a+b*b+c*c);
	cout<<"The distance = "<<distance<<endl;
	return distance;
}
//��ʼ����Ա����
int distance_calculation::fun()
{
	return 10;
}
//��ʼ����Ա����
int distance_calculation::int_a = 10;
double distance_calculation::a = 0.1;

int _tmain(int argc, _TCHAR* argv[])
{
	double a,b,c;

	//distance_calculation example_distance;//���Ŀ�ľ��Ǵ���һ����
	//�����˸���֮��Ϳ���ֱ�Ӳ���.������->���е����ڲ��ĳ�Ա

	cout<<"Please input three values of this points"<<endl;
	cin>>a;
	cin>>b;
	cin>>c;
	cout<<distance_calculation::fun()<<endl;//����ֱ�Ӳ��õ����������Ծ�̬��Ա���е���
	//���ڷǾ�̬��Ա���ǲ��ܽ��е��õ�
	return 0;
}

