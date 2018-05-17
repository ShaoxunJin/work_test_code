#ifndef SIZE_OF_H
#define SIZE_OF_H

#include "head_file.h"

/******************************************************************
�ṹ���ַ����ƫ��
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
���ڲ�����class�е�sizeof��С
�� sizeof ��С�ļ���ԭ��
1�����һ���࣬sizeof���������������ʵ����
	����static���͵��ǹ�������ʵ���������static���ᱻ�������sizeof�У�

	������౾��û�д������������£�������౾�����sizeof��������¼��������
	1 ���ֻࣨ�й��������������ҲҪ����ʵ����������һ���ֽڵ��ڴ�ռ���ʾ���ڣ�
	2 ������������ĳ�Ա������sizeof�ۼӣ����ǳ�Ա����������������󲻽���sizeof��
	3 ����ѭ�ֽڶ���ԭ�򣬴�ŵ�ַҲ����public Ȼ����private��������ȶ�public�������ֽڶ���then private��
	4 ���д����麯�������д����麯�����ַ���õ�ַռ��һ����sizeof(int)��������ڶ��virtual����ռ��ͬһ���麯���б�
	5 ���ڼ̳��д���һЩ˽�г�Ա�����������е�˽�г�Ա��������ռ��������ڴ�ռ䣬����Ĵ�С�������ڸ�������Ͻ����ۼӣ�
	6 ������̳У�����һ��ָ�������̳�ָ�룻
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

//ö�����Զ����ַ�����
void enum_char_test();
void HWPP_AP_nbr_test();

void arrar_sizeof_test();

const char* enum2str(const WM4A_AXIS_ID_ENUM& t);

ostream& operator<<(ostream& os, const WRHIOMC_AX_MCS_STRUCT& status);
ostream& operator<<(ostream& os, const WM4A_AXIS_ID_ENUM& axis);

#endif