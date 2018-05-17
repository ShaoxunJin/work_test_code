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
	//数组偏移测试
	//一个int占空间4 byte， 4*8 = 32 bit
	//16进制表示 0x00 00 00 00 
	//2进制表示 00000000 00000000 00000000 00000000
	int tt[5] = {1,2,3,4,5};
	int *ptr1 = (int*)(&tt + 1);				//这里是以数组指针为单位进行增加
	int *ptr2 = (int*)((int)tt + 1);			//这里是以int为单位进行指针增加
	cout<<"tt = "<<tt<<endl;					//数组首地址
	char tt_1 = ((char*)&tt)[0];				//这里是将一个int 4个字节转换为char类型
	char tt_2 = ((char*)&tt)[1];
	char tt_3 = ((char*)&tt)[2];
	char tt_4 = ((char*)&tt)[3];

	cout<<"tt_1 = "<<tt_1<<endl;
	cout<<"tt_2 = "<<tt_2<<endl;
	cout<<"tt_3 = "<<tt_3<<endl;
	cout<<"tt_4 = "<<tt_4<<endl;

	cout<<"&tt[0] = "<<&tt[0]<<endl;			//这里是针对元素进行取址然后是+
	cout<<"&tt[0]+1 = "<<&tt[0]+1<<endl;
	cout<<"&tt[0]+2 = "<<&tt[0]+2<<endl;
	cout<<"&tt[0]+3 = "<<&tt[0]+3<<endl;

	cout<<"&tt[1] = "<<&tt[1]<<endl;			//四个字节为单位进行偏移
	cout<<"&tt = "<<&tt<<endl;					//数组首地址进行取址还是数组首地址，只不过是指向数组指针
	cout<<"&tt + 1 = "<<&tt + 1<<endl;
	cout<<"&tt + 2 = "<<&tt + 2<<endl;
	cout<<"&tt + 3 = "<<&tt + 3<<endl;
	cout<<"&tt + 4 = "<<&tt + 4<<endl;
	cout<<"&tt + 5 = "<<&tt + 5<<endl;
	cout<<"sizeof(&tt)="<<sizeof(&tt)<<endl;	//数组指针进行sizeof是整个数组的size
	cout<<"&tt + 1 = "<<&tt+1<<endl;			//数组指针进行偏移 偏移单位是数组指针的size
	cout<<"ptr1 = "<<ptr1<<endl;				//数组指针进行赋值给另外一个指针
	cout<<"(int)tt = "<<hex<<(int)tt<<endl;
	cout<<"(int)tt+1 = "<<(int)tt+1<<endl;
	cout<<"ptr2 = "<<ptr2<<endl;
	cout<<"ptr2 + 1 = "<<ptr2 + 1<<endl;		//这里+1是增加一个int？？？为甚？
	//因为这里是小端 低字节放在低地址
	cout<<"*ptr2 = "<<*ptr2<<endl;				//取出其中一个地址 然后根据地址后续进行计算
	
	cout<<"sizeof(ptr1) = "<<sizeof(ptr1)<<endl;	//一个数组的长度
	cout<<"sizeof(ptr2) = "<<sizeof(ptr2)<<endl;	//单个字节的长度	

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
