#include "stdafx.h"
#include "headfile.h"
class Base
	{
	public:
		Base();		
		~Base();
		int x;
		char *base_class_string;
		static int base_static_x;
		int base_int_function();
		char *base_char_function();
		static char *base_static_char_function();
		//virtual int drawOut();
		//int getTotalCount() {return s_gCount;}
	private:
		int private_num ;
		char *private_string;
	};
//构造函数和析构函数
Base::Base()
{
	x = 0; 
	private_num = 7879;
	private_string = "Telephone Number";
	cout<<"Construction Base"<<endl;
}

Base::~Base()
{cout<<"Destruction Base"<<endl;}

int Base::base_int_function()
{return private_num;}

//静态变量或者成员函数可以直接定义
int base_static_x = 1819;
char *base_static_char_function()
{
	char *name = "jinshaoxun";
	return name;
}

char *Base::base_char_function()
{return private_string;}

//继承
class Derive_class: public Base
{
public:
	Derive_class(){cout<<"Construction Derive_class"<<endl;}
	~Derive_class(){cout<<"Destruction Derive_class"<<endl;}
	int derive_num;
	char *derive_string;
	static int derive_static_num;
	static char *derive_static_string;
	void derive_function();
	int derive_int_function();
	char *derive_char_function();
};
int derive_static_num = 9787;
char *derive_static_string = "Derive Jinshaoxun";

int Derive_class::derive_int_function()
{return derive_num;}

char *Derive_class::derive_char_function()
{
	char *derive_name = "Derive_class";
	return derive_name;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Test Begin ..."<<endl;
	cout<<"Static Number & Function..."<<endl;
	cout<<"Static_string = "<<base_static_char_function()<<endl;
	//cout<<"Static_string = "<<Base::char_function()<<endl;	//非静态变量调用错误；
	cout<<"Static_number = "<<base_static_x<<endl;
	cout<<endl;

	cout<<"Define New Class on base"<<endl;
	Base class_base;
	class_base.base_class_string = "JINSHAOXUN";
	cout<<"New class name = "<<class_base.base_class_string<<endl;
	class_base.x = 1;
	cout<<"Member Number = "<<class_base.x<<endl;
	cout<<class_base.base_char_function()<<endl;
	cout<<class_base.base_int_function()<<endl;

	cout<<endl;
	cout<<"Derive New Class on base"<<endl;
	cout<<"Derive_static_num = "<<derive_static_num<<endl;
	cout<<"Derive Jinshaoxun = "<<derive_static_string<<endl;

	cout<<endl;
	Derive_class derive_class;
	derive_class.derive_string = "derive_class";

	cout<<"define a new class on derive_class"<<endl;
	cout<<"New derive name = "<<derive_class.derive_string<<endl;
	cout<<"New derive number = "<<derive_class.derive_num<<endl;
	cout<<"New derive static string = "<<derive_static_string<<endl;
	cout<<"New derive static num = "<<derive_static_num<<endl;
	derive_class.derive_num = 4;
	cout<<"New int fucntion value = "<<derive_class.derive_int_function()<<endl;
	cout<<"New char fucntion value = "<<derive_class.derive_char_function()<<endl;
	
	//下面需要采用继承的方式进行一些简单的理解，如果不加public属性则默认是private继承；
	/*
	class Derive:public Base
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
	*/
	cout<<"\n"<<endl;
	system("pause");
 	return 0;
}