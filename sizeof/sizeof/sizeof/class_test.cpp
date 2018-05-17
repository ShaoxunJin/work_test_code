#include "stdafx.h"
#include "head_file.h"
#include "class_test.h"
double xxxxx = 123.0;
//类成员构造函数
class_jinshaoxun::class_jinshaoxun(int nbr, const char* name_)
				 :ddddd(10)
				 ,private_number(nbr)
				 ,_name(name_)
{
	//private_number = 1121;
	//ddddd = 10.0;
	//_name = "jinshaoxun";
}

class_jinshaoxun::~class_jinshaoxun()
{

}

//double class_jinshaoxun::xxxxxs = 123;

int class_jinshaoxun::call_private_number()
{
	return private_number;
}

const char *class_jinshaoxun::call_private_char() const
{
	return _name;
}

int class_jinshaoxun::operator [](int index)
{
	return vec[index];
}

//类测试函数
void class_debug(void)
{
	cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
	class_jinshaoxun class_jin(12,"hahhah");
	//定义一个类对象（实例） 通过该类中的公有接口调用私有成员；
	cout<<"private_number = "<<class_jin.call_private_number()<<endl;
	cout<<"private_char = "<<class_jin.call_private_char()<<endl;
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
}

void class_jinshaoxun::static_function()
{
	cout<<"This is static member function !"<<endl;
}

CLASS_JINSHAOXUN_DERIVE::CLASS_JINSHAOXUN_DERIVE(int nbr, const char* name_): class_jinshaoxun(nbr, name_)
{
	cout<<"This is "<<typeid(CLASS_JINSHAOXUN_DERIVE).name()<<" construction !"<<endl;
}

CLASS_JINSHAOXUN_DERIVE::~CLASS_JINSHAOXUN_DERIVE()
{
	cout<<"This is "<<typeid(CLASS_JINSHAOXUN_DERIVE).name()<<" deconstruction !"<<endl;
}

void CLASS_JINSHAOXUN_DERIVE::cout_base_class_member_fcn()
{
	static_function();
	//cout<<"xxxxx = "<<xxxxx<<endl;
}

xxxx::xxxx(int nbr) : m_nbr(nbr)
{
	cout<<__FUNCTION__<<m_nbr<<endl;
}

xxxx::~xxxx()
{
	cout<<__FUNCTION__<<endl;
}