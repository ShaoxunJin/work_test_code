#ifndef SIZE_OF_H
#define SIZE_OF_H

#include "head_file.h"

/******************************************************************
结构体地址进行偏移
******************************************************************/

typedef struct
{
	int a;
	int b;
}WRHIOMC_AX_MCS_STRUCT;

typedef struct
{
	WRHIOMC_AX_MCS_STRUCT LP_Z;
	WRHIOMC_AX_MCS_STRUCT LP_SWING;
	WRHIOMC_AX_MCS_STRUCT LP_DOCK;
	WRHIOMC_AX_MCS_STRUCT LP_LATCH;
	WRHIOMC_AX_MCS_STRUCT LP_LATCH_KEY;
	WRHIOMC_AX_MCS_STRUCT LP_MAPPER;
}WIMC_FILE_STRUCT;

typedef enum
{
	WMMC_RO_STATION_MIN = 0,
	WMMC_RO_STATION_A = 'a',
	WMMC_RO_STATION_B = 'B',
	WMMC_RO_STATION_C = 'C',
	WMMC_RO_STATION_D = 'D',
	WMMC_RO_STATION_E = 'E',
	WMMC_RO_STATION_F = 'F',
	WMMC_RO_STATION_G = 'G',
	WMMC_RO_STATION_H = 'H',
	WMMC_RO_STATION_I = 'I',
	WMMC_RO_STATION_J = 'J',
	WMMC_RO_STATION_K = 'K',
	WMMC_RO_STATION_L = 'L',
	WMMC_RO_STATION_HOME,
	WMMC_RO_STATION_MAX
}WMMC_RO_STATION_ENUM;

typedef enum
{
	WM4A_AXIS_MIN = 0,
	WM4A_AXIS_Z,
	WM4A_AXIS_R,
	WM4A_AXIS_C,
	WM4A_AXIS_V,
	WM4A_AXIS_MAX
}WM4A_AXIS_ID_ENUM;


/************************************************************************
用于测试类class中的sizeof大小
类 sizeof 大小的几个原则：
1、针对一个类，sizeof是针对类所创建的实例；
	比如static类型的是归属所有实例对象，则该static不会被列入类的sizeof中；

	因此在类本体没有创建对象的情况下，如果对类本身进行sizeof则存在如下几种情况：
	1 空类（只有构造和析构函数）也要进行实例化，分配一个字节的内存空间以示存在；
	2 根据其他具体的成员来进行sizeof累加，但是成员函数属于所有类对象不进行sizeof；
	3 类遵循字节对齐原则，存放地址也是先public 然后是private，因此首先对public进行四字节对齐then private；
	4 类中存在虚函数则类中存在虚函数表地址，该地址占用一定的sizeof(int)，如果存在多个virtual，则占用同一个虚函数列表；
	5 对于继承中存在一些私有成员变量，则父类中的私有成员变量继续占用子类的内存空间，子类的大小必须是在父类基础上进行累加；
	6 对于虚继承，增加一个指向父类的虚继承指针；
/************************************************************************/
class SIZEOFCLASS_BASE
{
public:
	SIZEOFCLASS_BASE();
	virtual ~SIZEOFCLASS_BASE();
	//~SIZEOFCLASS_BASE();
	void test_trace_in(char *in_message);
	//void test_trace_out(char *out_message);
	void test_SIZEOFCLASS(int *nbr);
	virtual void test_trace_out();//one byte
	virtual void test_trace_out_1();
	char SIZEOFCLASS_char[13];
	int static_nbr;//one byte
private:
	int m_nbr;//one byte
	
};

class SIZEOFCLASS_BASE_1
{
public:
	SIZEOFCLASS_BASE_1();
	~SIZEOFCLASS_BASE_1();
	virtual void fcn_test_sizeof_class_base_1();//one byte
};

class SIZEOFCLASS_DERIVE : virtual public SIZEOFCLASS_BASE, public SIZEOFCLASS_BASE_1
{
public:
	SIZEOFCLASS_DERIVE();
	~SIZEOFCLASS_DERIVE();
	//virtual void fcn_test_sizeof_derive();
	virtual void test_trace_out_1();

	char derive_char[103];
	int derive_nbr;

private:
	char deriveCharPrivate[3];
};

int size_of_test(char);
int size_of_test(int);
int size_of_test(double);
int size_of_array(void);
//int size_of_class();

//枚举中自定义字符变量
void enum_char_test();
void HWPP_AP_nbr_test();

void arrar_sizeof_test();

const char* enum2str(const WM4A_AXIS_ID_ENUM& t);

ostream& operator<<(ostream& os, const WRHIOMC_AX_MCS_STRUCT& status);
ostream& operator<<(ostream& os, const WM4A_AXIS_ID_ENUM& axis);

#endif