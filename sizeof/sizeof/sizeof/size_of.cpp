#include "stdafx.h"
#include "size_of.h"

int size_of_test(char size_num)
{
	ostringstream os("");
	os<<endl<<"Sizeof test is begin..."<<endl;
	cout<<os.str();

	int result = sizeof(size_num);
	cout<<"sizeof("<<dec<<size_num<<") = "<<result<<endl;

	os.str("");
	os<<"Sizeof test is end..."<<endl<<endl;

	cout<<os.str();

	return result;
}
 
int size_of_test(int size_num)
{
	ostringstream os("");
	os<<endl<<"Sizeof test is begin..."<<endl;
	cout<<os.str();

	int result = sizeof(size_num);
	cout<<"sizeof("<<dec<<size_num<<") = "<<result<<endl;

	os.str("");
	os<<"Sizeof test is end..."<<endl<<endl;
	cout<<os.str();
	
	return result;
}

int size_of_test(double size_num)
{
	ostringstream os("");
	os<<endl<<"Sizeof test is begin..."<<endl;
	cout<<os.str();

	int result = sizeof(size_num);
	cout<<"sizeof("<<dec<<size_num<<") = "<<result<<endl;

	os.str("");
	os<<"Sizeof test is end..."<<endl<<endl;
	cout<<os.str();

	return result;
}

WM4A_AXIS_ID_ENUM array_enum_test[] =
{
	WM4A_AXIS_Z,
	WM4A_AXIS_R,
	WM4A_AXIS_C,
};

int size_of_array()
{
	cout<<"size_of_enum_array = "<<sizeof(array_enum_test)<<endl;
	cout<<"NO. of array = "<<sizeof(array_enum_test)/sizeof(WM4A_AXIS_ID_ENUM)<<endl;
	return 1;
}

SIZEOFCLASS_BASE::SIZEOFCLASS_BASE()
{
	test_trace_in("IN>>>>>>>>>>>>>");
	cout<<"SIZEOFCLASS_BASE construct success !"<<endl;
}

SIZEOFCLASS_BASE::~SIZEOFCLASS_BASE()
{
	//test_trace_in("OUT<<<<<<");
	cout<<"SIZEOFCLASS_BASE deconstruct success !"<<endl;
}

void SIZEOFCLASS_BASE::test_trace_in(char *in_message)
{
	cout<<"in_message = "<<in_message<<endl;
}

//void SIZEOFCLASS_BASE::test_trace_out(char *out_message)
void SIZEOFCLASS_BASE::test_trace_out()
{
	cout<<"out_message = "<<endl;
}

void SIZEOFCLASS_BASE::test_trace_out_1()
{

}

SIZEOFCLASS_DERIVE::SIZEOFCLASS_DERIVE()
{
	cout<<"SIZEOFCLASS_DERIVE construct successful !"<<endl;
}

SIZEOFCLASS_DERIVE::~SIZEOFCLASS_DERIVE()
{
	cout<<"SIZEOFCLASS_DERIVE deconstruct successful !"<<endl;
}

void SIZEOFCLASS_DERIVE::test_trace_out_1()
{
	cout<<"......."<<endl;
}

SIZEOFCLASS_BASE_1::SIZEOFCLASS_BASE_1()
{
	cout<<"SIZEOFCLASS_BASE_1 construct successful !"<<endl;
}

SIZEOFCLASS_BASE_1::~SIZEOFCLASS_BASE_1()
{
	cout<<"SIZEOFCLASS_BASE_1 deconstruct successful !"<<endl;
}

void SIZEOFCLASS_BASE_1::fcn_test_sizeof_class_base_1()
{
	
}

void enum_char_test()
{
	struct
	{
		WMMC_RO_STATION_ENUM ro_station;
	}ro;
	ro.ro_station = WMMC_RO_STATION_A;
	//cout<<"WMMC_RO_STATION_A = "<<ro.ro_station<<endl;
	//printf("WMMC_RO_STATION_A = %c",ro.ro_station);
	return;
}

void HWPP_AP_nbr_test()
{
	cout<<"Begin to test for HWPP_AP_nbr_test >>>>>"<<endl;
	
	int iTestNbr = 1;
	
	while(false)
	{
		cout<<"Current Test Time : "<<iTestNbr<<endl;
		if (iTestNbr != 1)
		{
			if ((iTestNbr-1) % 20 == 0)
			{
				cout<<"Pause......."<<endl;
			}
		}
		++iTestNbr;
	}
	cout<<"End to test for HWPP_AP_nbr_test <<<<<"<<endl;
}

void arrar_sizeof_test()
{
	//����ƫ�Ʋ���
	//һ��intռ�ռ�4 byte�� 4*8 = 32 bit
	//16���Ʊ�ʾ 0x00 00 00 00 
	//2���Ʊ�ʾ 00000000 00000000 00000000 00000000
	int tt[5] = {1,2,3,4,5};
	int *ptr1 = (int*)(&tt + 1);				//������������ָ��Ϊ��λ��������
	int *ptr2 = (int*)((int)tt + 1);			//��������intΪ��λ����ָ������
	cout<<"tt = "<<tt<<endl;					//�����׵�ַ
	char tt_1 = ((char*)&tt)[0];				//�����ǽ�һ��int 4���ֽ�ת��Ϊchar����
	char tt_2 = ((char*)&tt)[1];
	char tt_3 = ((char*)&tt)[2];
	char tt_4 = ((char*)&tt)[3];

	cout<<"tt_1 = "<<tt_1<<endl;
	cout<<"tt_2 = "<<tt_2<<endl;
	cout<<"tt_3 = "<<tt_3<<endl;
	cout<<"tt_4 = "<<tt_4<<endl;

	cout<<"&tt[0] = "<<&tt[0]<<endl;			//���������Ԫ�ؽ���ȡַȻ����+
	cout<<"&tt[0]+1 = "<<&tt[0]+1<<endl;
	cout<<"&tt[0]+2 = "<<&tt[0]+2<<endl;
	cout<<"&tt[0]+3 = "<<&tt[0]+3<<endl;

	cout<<"&tt[1] = "<<&tt[1]<<endl;			//�ĸ��ֽ�Ϊ��λ����ƫ��
	cout<<"&tt = "<<&tt<<endl;					//�����׵�ַ����ȡַ���������׵�ַ��ֻ������ָ������ָ��
	cout<<"&tt + 1 = "<<&tt + 1<<endl;
	cout<<"&tt + 2 = "<<&tt + 2<<endl;
	cout<<"&tt + 3 = "<<&tt + 3<<endl;
	cout<<"&tt + 4 = "<<&tt + 4<<endl;
	cout<<"&tt + 5 = "<<&tt + 5<<endl;
	cout<<"sizeof(&tt)="<<sizeof(&tt)<<endl;	//����ָ�����sizeof�����������size
	cout<<"&tt + 1 = "<<&tt+1<<endl;			//����ָ�����ƫ�� ƫ�Ƶ�λ������ָ���size
	cout<<"ptr1 = "<<ptr1<<endl;				//����ָ����и�ֵ������һ��ָ��
	cout<<"(int)tt = "<<hex<<(int)tt<<endl;
	cout<<"(int)tt+1 = "<<(int)tt+1<<endl;
	cout<<"ptr2 = "<<ptr2<<endl;
	cout<<"ptr2 + 1 = "<<ptr2 + 1<<endl;		//����+1������һ��int������Ϊ����
	//��Ϊ������С�� ���ֽڷ��ڵ͵�ַ
	cout<<"*ptr2 = "<<*ptr2<<endl;				//ȡ������һ����ַ Ȼ����ݵ�ַ�������м���
	
	cout<<"sizeof(ptr1) = "<<sizeof(ptr1)<<endl;	//һ������ĳ���
	cout<<"sizeof(ptr2) = "<<sizeof(ptr2)<<endl;	//�����ֽڵĳ���	

}

const char* enum2str(const WM4A_AXIS_ID_ENUM& t)
{
	const char* str = NULL;
	switch (t)
	{
	case WM4A_AXIS_Z:
		str = "WM4A_AXIS_Z";
		break;
	case WM4A_AXIS_R:
		str = "WM4A_AXIS_R";
		break;
	case WM4A_AXIS_C:
		str = "WM4A_AXIS_C";
		break;
	case WM4A_AXIS_V:
		str = "WM4A_AXIS_V";
		break;
	default:
		str = "INVALIE_AXIS_ID_ENUM";
		break;
	}

	return str;
}


ostream& operator<<(ostream& os, const WRHIOMC_AX_MCS_STRUCT& status)
{
	os<<"status.a = "<<status.a<<", status.b = "<<status.b;
	return os;
}

ostream& operator<<(ostream& os, const WM4A_AXIS_ID_ENUM& axis)
{
	os<<enum2str(axis);
	return os;
}
