//case_test
#include "stdafx.h"
//#include <iostream>
//#include <sstream>
//#include <stdio.h>
//using namespace std;
#include "case_test.h"

int i_static_nbr = 623;

//用于测试case
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
1、函数内部声明static，则该数据将存储在静态数据区，每次当函数结束之后该数据并没有及时释放
static在局部变量声明的情况下在其他函数内是不能使用的；
只有静态全局变量才可以使用；
2、下次如果继续使用该函数 则该变量根据最新的保存数值继续使用；
3、如果该数据保存在该模块内，则该数据可以被该模块内的所有函数使用，且每次调用都是最新的值；
4、static声明的变量只会进行第一次的初始化；
5、涉及到类中的static一样，也就是只有一份；
6、如果声明了static 则不能使用extern从一个模块来调用在另外一个模块中声明的变量
7、声明为全局变量和static修饰的全局变量 区别在于前者能通过添加“extern”修饰符来调用该全局变量
用static修饰的是只能在本模块中使用
8、全局变量也只有初始化一次，后续是在不断更新的基础上进行调用；
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


//形参传入的是指针情况下测试指针指向的内容没有发生变化
