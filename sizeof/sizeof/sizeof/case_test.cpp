//case_test
#include "stdafx.h"
//#include <iostream>
//#include <sstream>
//#include <stdio.h>
//using namespace std;
#include "case_test.h"

int i_static_nbr = 623;

//���ڲ���case
void case_test(int a)
{
	ostringstream os;
	os.str("");
	os<<"Current data = "<<a;
	switch(a)
	{
	case 0:
		os.str("");
		os<<"Current data = "<<a;
		cout<<os.str()<<endl;
		a += 1;
	case 1:
		os.str("");
		os<<"Current data = "<<a;
		cout<<os.str()<<endl;
		a += 1;
	case 2:
		os.str("");
		os<<"Current data = "<<a;
		cout<<os.str()<<endl;
		a += 1;
	default:
		os.str("");
		os<<"Current data = "<<a;
		cout<<"Invalid Switch Case NO.!"<<endl;
		break;
	}
	return;
}

/******************************************************************
1�������ڲ�����static��������ݽ��洢�ھ�̬��������ÿ�ε���������֮������ݲ�û�м�ʱ�ͷ�
static�ھֲ�����������������������������ǲ���ʹ�õģ�
ֻ�о�̬ȫ�ֱ����ſ���ʹ�ã�
2���´��������ʹ�øú��� ��ñ����������µı�����ֵ����ʹ�ã�
3����������ݱ����ڸ�ģ���ڣ�������ݿ��Ա���ģ���ڵ����к���ʹ�ã���ÿ�ε��ö������µ�ֵ��
4��static�����ı���ֻ����е�һ�εĳ�ʼ����
5���漰�����е�staticһ����Ҳ����ֻ��һ�ݣ�
6�����������static ����ʹ��extern��һ��ģ��������������һ��ģ���������ı���
7������Ϊȫ�ֱ�����static���ε�ȫ�ֱ��� ��������ǰ����ͨ����ӡ�extern�����η������ø�ȫ�ֱ���
��static���ε���ֻ���ڱ�ģ����ʹ��
8��ȫ�ֱ���Ҳֻ�г�ʼ��һ�Σ��������ڲ��ϸ��µĻ����Ͻ��е��ã�
******************************************************************/
void static_test()
{	
	//cout<<"i_static_nbr : "<<i_static_nbr<<endl;
	//for (int i = 0 ;i < 10; ++i)
	//{
	//	i_static_nbr++;
	//	cout<<"i_static_nbr : "<<i_static_nbr<<endl;
	//}
	static int i_static_test_nbr = 0;
	cout<<__FUNCTION__<<" = "<<i_static_test_nbr<<endl;
	++i_static_test_nbr;
}


//�βδ������ָ������²���ָ��ָ�������û�з����仯
