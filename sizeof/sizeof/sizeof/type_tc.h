#ifndef TYPE_TC_H
#define TYPE_TC_H

vector<double> vec_data_read_write;

//����һ��ȫ�ֱ���
int g_int = 132;

//�궨��һ��ָ�����
typedef int* SMEE_INT;

typedef enum
{
	enum_value_min = 0,
	enum_value_1,
	enum_value_2,
	enum_value_3,
	enum_value_4,
	enum_value_max
}enum_sizeof_value_test;

typedef struct
{
	int filler;
}struct_sizeof_value;

typedef int tttt[10];

//����һ������sizeof�ĺ���ģ��
template <typename Type>
int sizeof_calc(Type Input)
{
	//���enum��sizeof
	//������Ϊ4
	cout<<"sizeof enum = "<<sizeof(Input)<<endl;
	cout<<endl;	
	return sizeof(Input);	
}

typedef enum
{
	A_ENUM,
	B_ENUM
}enum_test;


typedef struct
{
	enum_test t;
}TH_STRUCT;

typedef struct
{
	int A_int;
}TH_STRUCT_INT;


enum weekday
{
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
};
enum name
{
	jin,
	shao,
	xun
};
struct name_day
{
	weekday enum_weekday;
	name enum_name;
};

#endif
