#ifndef CLASS_TEST_H
#define CLASS_TEST_H

//构造函数函数带参数
//在创建类对象过程可直接在声明对象的时候对构造函数参数进行赋值


//定义一个类
class class_jinshaoxun
{
public:
	class_jinshaoxun(int nbr, const char* name_);//构造函数
	~class_jinshaoxun();//析构函数
	int call_private_number();
	const char *call_private_char() const;
	int public_number;
	const int ddddd;
	static double xxxxx;

	static void static_function();
	
	int vec[10];
	int operator[](int index);

private:
	int m_call_private();
	int private_number;
	const char *_name;
};

void class_debug(void);

class CLASS_JINSHAOXUN_DERIVE : public class_jinshaoxun
{
public:
	CLASS_JINSHAOXUN_DERIVE(int nbr, const char* name_);
	~CLASS_JINSHAOXUN_DERIVE();
	void cout_base_class_member_fcn();

};



class xxxx
{
public:
	xxxx(int nbr);
	~xxxx();
	int m_nbr;
};

#endif