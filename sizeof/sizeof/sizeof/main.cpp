// sizeof.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "head_test_file.h"

//#include "ENUM_TO_STRING.h"
/********宏定义************/
//#显示字符串
//#define _INTERPRET_
//#define _STATIC_FCN_
//#define  _PTR_
//#define _TEMPLATE_RETURN_REFERENCE_
#define error_code(error) #error
#define con(x,y) x##y
#define toStr(err) #err
#define str_out(err) toStr(err)
#define single_quotation(x) #@x
#define second_pre_year 365*24*60*60
#define PFU_CAM_CC1_MODE_SHIFT 31
#define PFU_CAM_CC1_MODE (1u << PFU_CAM_CC1_MODE_SHIFT)
#define PFU_CAM_CC1_MODE_1 (1 << PFU_CAM_CC1_MODE_SHIFT)
#define sss     1000000

#define max_jin(a,b) ((a) > (b) ? (a) : (b))

//#define _VALUE_FINDER_
#define _BOOST_
//#define _MAP_PAIR_
//#define _FILE_OPERATION_
//#define _TRY_CATCH_
//#define _MOVE_WAFER_
#define _WH_TEST_
#define _LIST_TEST_
#define _CLASS_SIZE_TEST_

#define _CAST_
#define _CUSTOM_MAP_
#define _THREAD_MUTEX_
#define _TEMPLATE_

//#define _HONEYWELL_

void funcc(int* tt);

//class
class jinshaoxun
{
public:
	jinshaoxun();
	~jinshaoxun();
	int call_private();
	int public_num;

private:
	int private_num;
	int m_call_private();
};

jinshaoxun::jinshaoxun()
{
	private_num = 222;
}
jinshaoxun::~jinshaoxun()
{

}
int jinshaoxun::call_private()
{
	return private_num;
}

int jinshaoxun::m_call_private()
{
	cout<<"m_call_private = "<<private_num<<endl;
	return 1;
}

/******* main function********/
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{	
	cout<<"Test Begin ......"<<endl;
	std::string df("sdasd");
	std::cout<<df<<endl;
	//enum_sizeof_value_test test;
	//double test;
	struct_sizeof_value struct_sizeof;

	//test the limit value of different data type
	limit_value_test();

	//int result;
//	result  = sizeof_calc(struct_sizeof);
//	cout<<"Result = "<<result<<endl;

	//开始测试是否有溢出
	volatile unsigned int overflow_flag = 0;
	cout<<"sizeof(int) = "<<sizeof(int)<<endl;
	cout<<"sizeof(short) = "<<sizeof(short)<<endl;

	long distance = 2147483648;
	//int compare = 0x80000000;
	int compare = (distance & 0xff80000000);
		compare = compare>> 31;
	unsigned int i;
	i = (unsigned int)compare;
	cout<<"compare = "<<compare<<endl;
	overflow_flag = (unsigned int)((distance & 0xff80000000) >> 31);
	cout<<"overflow_flag = "<<overflow_flag<<endl;

	cout<<"2014-11-28"<<endl;
	short int A = 15;
	short int B = 20;
	int C;
	C = (A<<16);
	cout<<"C = "<<C<<endl;
	int D = ((A & 0xFFFFFFFF)<<16) | 20 ;
	cout <<"D = "<<D<<endl;

	cout<<"false = "<<true<<endl;

	cout<<"Test 2014-12-07"<<endl;
	//cout<<"十六进制A = "<<"0x%x"<<A<<endl;
	printf("0x%x\n",A);

	cout<<"JINTIAN"<<endl;
	int num_1210 = 0xffff0000;
	cout<<num_1210<<endl;
	
	cout<<endl;
	cout<<"Test for 20141211"<<endl;
	double num_double = 15.467;
	cout<<"double = "<<num_double<<endl;

	/*double *ptr_double = &num_double;
	int num_int = reinterpret_cast<double&>(num_double);*/
	/*cout<<ptr_int<<endl;
	cout<<num_double<<endl;*/
	//int *ptr_int = &num_int;
	//cout<<"ptr_double = "<<ptr_double<<endl;
	//cout<<"ptr_int = "<<ptr_int<<endl;

	TH_STRUCT jkj;
	TH_STRUCT_INT KKK;
	jkj.t = B_ENUM;
	cout<<"A_ENUM"<<A_ENUM<<endl;

	KKK = reinterpret_cast<TH_STRUCT_INT&>(jkj);
	//cout<<"KKK = "<<KKK.A_int<<endl;
	
	int test_num = 0xffff0000;
	cout<<"2014-12-18:"<<test_num<<endl;
	test_num = 100;
	double test_num_output = test_num%9;
	cout<<"test_num_output = "<<test_num_output<<endl;
	cout<<error_code(00000)<<endl;
	cout<<con(1,2)<<endl;
	
	cout<<str_out(con(jin,shaoxun))<<endl;

	int link_error[2] = {555,2};
	cout<<*link_error<<endl;

	int int_numerator = 5;
	int int_denominator = 3;
	double double_data = 1.3;
	int int_data = 1;
	double result_1= 0.0;
	double result_2 = 0.0;
	result_1 = int_numerator/int_denominator;
	result_2 = int_data + double_data;
	cout<<"result_2 = "<<result_2<<endl;
	char c = 'b';
	if(c == 98)
	{
		cout<<"YES"<<endl;
	}
	else
	{
		cout<<"No"<<endl;
	}

	cout<<"siezeof(bool) = "<<sizeof(bool)<<endl;
	cout<<"rand_max = 0x"<<hex<<RAND_MAX<<endl;
	printf("rand_max = 0x%x\n",RAND_MAX);
	//switch case test
	case_test(0);

	//sizeof
	size_of_test(1);

	struct jin
	{

	};
	cout<<"sizeof struct = "<<sizeof(jin)<<endl;

	//cartensian_to_polar test
	cartensian_cs_struct aaaa = {1,2};
	cartensian_to_polar(aaaa);
	//
	sprintf_test();
	//cout<<"seconds_per_year = "<<second_pre_year<<endl;

	//bool bDirection = true;
	//cout<<"bDirection = "<<bDirection<<endl;
	//bDirection = !bDirection;
	//cout<<"bDirection = "<<bDirection<<endl;
	cout<<"atan(1) = "<<atan(1.0)<<endl;
	//time_test
	time_test();

	//test bigendian or little endian
	endian_test_1();
	extern int g_int;
	cout<<"global_int = "<<g_int<<endl;

	/*volatile int volatile_num = 10;
	cout<<"volatile_num = "<<volatile_num<<endl;
	volatile_num = 11;
	int m = volatile_num;
	int n = m;
	cout<<"m = "<<m<<endl;
	cout<<"n = "<<n<<endl;*/

	template_function();
	//memcpy_test();
	memset_test();
	//count_if
	count_if_test();

	int iZero = 0;
	char iChar = (char)iZero;
	//char cZero = (char)((char *)&iZero)[0];
	cout<<"iZero = "<<hex<<iZero<<endl;
	cout<<error_code(iChar)<<endl;
	//cout<<"cZero = "<<cZero<<endl;
	cout<<"PFU_CAM_CC1_MODE_SHIFT = "<<dec<<PFU_CAM_CC1_MODE_SHIFT<<endl;
	cout<<"PFU_CAM_CC1_MODE = "<<PFU_CAM_CC1_MODE<<endl;
	cout<<"PFU_CAM_CC1_MODE_1 = "<<PFU_CAM_CC1_MODE_1<<endl; 
	
	MEMSET_STRUCT test_struct;
	memset_struct_test(&test_struct);

	Difference_r_n();
	macro_test_if_function();
	string_test();
	istringstream_test();
	int array[] = {0,1,2,3};
	int *a = &array[0];
	int print_out;

	enum_char_test();
	//char char_0518 = NULL;
	//char char_j[100];
	char char_j[] = "jinshaoxun";
	cout<<"sizeof(char_j) = "<<sizeof(char_j)<<endl;
	char_test(char_j);
	char *ttt = "";

	char_2_string();
	string_2_char();
	string_vector();

	ttt = (char*)(return_globle_string());
	cout<<"ttt = "<<ttt<<endl;

	int source_data = 0x80000002;
	cout<<"result = "<<hex<<(source_data>>1)<<endl;
	
 	SMEE_INT point = NULL;
	int ddd = 111;
	point = &ddd;
	cout<<"point = "<<dec<<*point<<endl;

	//char family_name[10]= "jin";
	//char given_name[20]= "shaoxun";
	//strcat(family_name, given_name);
	//cout<<"full_name = "<<family_name<<endl;
	//cout<<"given_name"<<given_name<<endl;
	tttt what_is_this;

	SMEE_BOOL bAxis[WM4A_AXIS_MAX-1] = {SMEE_FALSE,SMEE_TRUE,SMEE_FALSE,SMEE_TRUE};
	for(int i = 0; i< WM4A_AXIS_MAX-1; ++i)
	{
		cout<<"bAxis = "<<bAxis[i]<<endl;
	}
	size_of_array();
	char *name = "sddddds";
	cout<<"     "<<name<<endl;
	overload_function_test();

	int mcd_id = 0x1f0a0000;
	cout<<"mcd_id = "<<mcd_id<<endl;

	cout<<"随机数:"<<(1.0 * rand())/RAND_MAX<<endl;

	int ms = 562;
	double ms_double = (double)(ms/1000);
	cout<<"ms_double"<<ms_double<<endl;

	int iyy = 10;
	iyy = -iyy;
	cout<<"i = "<<0%2<<endl;

	cout<<"result = "<<(rand()*1.0/RAND_MAX)<<endl;
	cout<<"result = "<<(rand()*1.0/RAND_MAX)<<endl;

	//string name_1 = "jin";
	//string name_2 = "shao";
	//name_1 += name_2;
	//cout<<"final_name = "<<name_1.c_str()<<endl;

	char *name_1 = "jin";
	char *name_2;
	name_2 = name_1;
	cout<<"name_2 = "<<name_2<<endl;

	memcpy_for_struct();
	
	map_pair_pair_test();

	SMEE_BOOL bDirection = SMEE_FALSE;
	cout<<"bDirection = "<<bDirection<<endl;
	bDirection = (SMEE_BOOL)!bDirection;
	cout<<"!bDirection = "<<bDirection<<endl;

	int i_dec = 10;
	char i_hex[50];
	sprintf(i_hex,"%X",i_dec);
	cout<<"i_hex = "<<i_hex<<endl;

	//string jin_name = "";
	//cout<<"jin_name = "<<sizeof(jin_name)<<endl;
	////cout<<"string.size() = "<<string.size()<<endl;
	//vector<int> ivector(10);
	//for (int i = 0; i < 10; ++i)
	//{
	//	ivector.push_back(i);
	//	cout<<i<<endl;
	//}

	/************************************************************************/
	/* boost_test                                                           */
	/************************************************************************/
	//boost_test();

	cout<<"Time : "<<time_calculation(10)<<endl;
	cout<<"Time : "<<time_calculation(429496729)<<endl;
	cout<<"Time : "<<time_calculation(268435455)<<endl;

	int *iiiiii = 0;
	//int aaaaaa = 10;
	//iiiiii = &aaaaaa;
	//cout<<"*i = "<<*iiiiii<<endl;
	cout<<"&i = "<<iiiiii<<endl;

	//int quote_num = 10;
	//quote(10);
	
	cout<<++quote_test_return_function()<<endl;

	using std::string;
	cout<<" "<<name_1<<endl;
	cout<<"string : "<<string(name_1)<<endl;

	write_format_string_file();

	//cout<<format_string("sd",2)<<endl;
	//char *t_1 = "j";
	////cout<<format_string(tttt,5);
	//char *t_2 = "s";
	//strcat(t_1,t_2);
	//cout<<t_1<<endl;

	const char *tra_char = "";
	transfer_char_to_const_char();

	char *char_length = "PU_docking_repeatibility_x[um]";
	
	cout<<strlen(char_length)<<endl;
	arrar_sizeof_test();
	
#ifdef _CLASS_SIZE_TEST_
	//类大小测试
	cout<<"sizeof(SIZEOFCLASS_BASE) = "<<dec<<sizeof(SIZEOFCLASS_BASE)<<endl;
	SIZEOFCLASS_BASE tt_size_of_class_base;
	SIZEOFCLASS_DERIVE tt_size_of_class_derive;
	cout<<"sizeof base = "<<sizeof(SIZEOFCLASS_BASE)<<endl;
	cout<<"sizeof base_1 = "<<sizeof(SIZEOFCLASS_BASE_1)<<endl;
	cout<<"sizeof base instance = "<<sizeof(tt_size_of_class_base)<<endl;
	cout<<"sizeof derive = "<<sizeof(SIZEOFCLASS_DERIVE)<<endl;
	cout<<"sizeof derive instance = "<<sizeof(tt_size_of_class_derive)<<endl;
#endif
	//实例化 模板类
	//template_TYPE<int, int> template_int(10,11);
	//template_int.class_name();

	//
	HWPP_AP_nbr_test();
	//
	vector<int> iWaferNbr;
	iWaferNbr.push_back(1);
	iWaferNbr.push_back(3);
	iWaferNbr.push_back(5);
	cout<<iWaferNbr.size()<<endl;//3
	cout<<iWaferNbr.back()<<endl;//5
	iWaferNbr.pop_back();
	cout<<iWaferNbr.size()<<endl;//2
	cout<<iWaferNbr.back()<<endl;//3

	WRMC_PORT_PARAMETER_STRUCT port_parameter = WRMC_PORT_PARAMETER_STRUCT();
	cout<<"WRMC_PORT_PARAMETER_STRUCT = "<<sizeof(WRMC_PORT_PARAMETER_STRUCT)<<endl;
	
	//地址偏移测试
	int offset = 10;
	cout<<"WRHIOMC_AX_MCS_STRUCT : "<<sizeof(WRHIOMC_AX_MCS_STRUCT)<<endl;
	cout<<"LP_Z address : "<<(size_t)(&(((WIMC_FILE_STRUCT *)offset)->LP_Z))<<endl;
	cout<<"LP_SWING address : "<<(size_t)(&(((WIMC_FILE_STRUCT *)offset)->LP_SWING))<<endl;

	char cmd[256] = "jinfasdkfjhdskf";
	char cmd_rpl[256] = "";
	char cmd_end[] = "\r";
	for (int i = 0 ; i < sizeof(cmd); ++i)
	{
		//cout<<"cmd["<<i<<"] = "<<cmd[i]<<endl;
		//cout<<"cmd["<<i<<"] = "<<cmd_rpl[i]<<endl;
	}
	
	strcat(cmd,"HOM -1");
	cout<<"cmd = "<<cmd<<endl;
	read_matrix_file();

#ifdef _TEMPLATE_RETURN_REFERENCE_
	template_TYPE<int, int> int_class(10,11);
	cout<<"TYPE = "<<int_class.class_name()<<endl;
	cout<<"int_class.return_type() = "<<int_class.return_type()<<endl;

	//采用返回函数值引用的方式 可以对返回值进行更改
	//如果返回值不是引用方式，下面=操作符会出现报错现象
	int_class.return_type() = 100;
	cout<<"int_class.return_type() = "<<int_class.return_type()<<endl;
	//针对map创建 value_type（pair类型）
	typedef map<int, int>::value_type int_class_m_map_pair;
	int_class.m_map.insert(int_class_m_map_pair(1,1));
	int_class.m_map.insert(int_class_m_map_pair(2,2));
	int_class.m_map.insert(int_class_m_map_pair(3,3));
	int_class.m_map.insert(int_class_m_map_pair(4,4));
	//int_class.m_map.insert(make_pair(1,1));
	int iii = 0;
	cout<<"Please input map key !"<<endl;
	cin>>iii;
	map<int,int>::iterator int_class_m_map_iter = int_class.m_map.find(iii);
	if (int_class_m_map_iter != int_class.m_map.end())
	{
		cout<<"int_class_m_map_iter->second = "<<int_class_m_map_iter->second<<endl;
	}
	else
	{
		cout<<"Invalid mapping key !"<<endl;
	}
	cout<<"int_class.m_map.find("<<iii<<") = "<<int_class_m_map_iter->second<<endl;
		
	//如下采用返回引用值可以对status内的member进行赋值操作
	WRHIOMC_AX_MCS_STRUCT sStatus = WRHIOMC_AX_MCS_STRUCT();
	template_TYPE<int, WRHIOMC_AX_MCS_STRUCT> status_class(10,sStatus);
	cout<<"TYPE = "<<status_class.class_name()<<endl;
	status_class.return_type().a = 1;
	status_class.return_type().b = 2;
	WRHIOMC_AX_MCS_STRUCT ax_a = {1,2};
	cout<<ax_a<<endl;
	WRHIOMC_AX_MCS_STRUCT ax_b = {2,4};
	cout<<ax_b<<endl;
	WRHIOMC_AX_MCS_STRUCT ax_c = {3,6};
	cout<<ax_c<<endl;

	typedef map<int, WRHIOMC_AX_MCS_STRUCT>::value_type status_class_m_map_pair;
	//status_class.m_map<int, WRHIOMC_AX_MCS_STRUCT>::value_type status_value_type(1,ax_a);			//创建键值对pair类型
	status_class.m_map.insert(status_class_m_map_pair(1, ax_a));
	status_class.m_map.insert(status_class_m_map_pair(2, ax_b));
	status_class.m_map.insert(status_class_m_map_pair(3, ax_c));
	
	map<int, WRHIOMC_AX_MCS_STRUCT>::iterator status_class_m_map_iter = status_class.m_map.find(iii);
	if(status_class_m_map_iter != status_class.m_map.end())
	{
		cout<<"status_class.find("<<iii<<"); a = "<<status_class_m_map_iter->second.a<<", b = "<<status_class_m_map_iter->second.b<<endl;
	}
	else
	{
		cout<<"No key find. Pleaese check it!"<<endl;
	}

	//下面传递进来的sStatus自然是空的，因为更改的是status_class类中的值而不是原始是sStatus
	template_TYPE<WM4A_AXIS_ID_ENUM, WRHIOMC_AX_MCS_STRUCT> enum_struct_template_class(WM4A_AXIS_MIN, sStatus);
	//cout<<"sStatus.a = "<<sStatus.a<<endl;
	//cout<<"sStatus.b = "<<sStatus.b<<endl;
	//cout<<"status_class.m_type_2.a = "<<status_class.m_type_2.a<<endl;
	//cout<<"status_class.m_type_2.b = "<<status_class.m_type_2.b<<endl;
	//cout<<"enum_struct_template_class.return_type().a = "<<enum_struct_template_class.return_type().a<<endl;
	//cout<<"enum_struct_template_class.return_type().b = "<<enum_struct_template_class.return_type().b<<endl;
	//必须对结构体进行初始化操作
	WRHIOMC_AX_MCS_STRUCT ax_z = WRHIOMC_AX_MCS_STRUCT();
	WRHIOMC_AX_MCS_STRUCT ax_r = WRHIOMC_AX_MCS_STRUCT();
	WRHIOMC_AX_MCS_STRUCT ax_C = WRHIOMC_AX_MCS_STRUCT();
	WRHIOMC_AX_MCS_STRUCT ax_v = WRHIOMC_AX_MCS_STRUCT();	
	enum_struct_template_class.m_map.insert(make_pair(WM4A_AXIS_Z, ax_z));
	enum_struct_template_class.m_map.insert(make_pair(WM4A_AXIS_R, ax_r));
	typedef map<WM4A_AXIS_ID_ENUM, WRHIOMC_AX_MCS_STRUCT>::value_type enum_struct_m_map_pair;
	enum_struct_template_class.m_map.insert(enum_struct_m_map_pair(WM4A_AXIS_C, ax_C));
	enum_struct_template_class.m_map.insert(enum_struct_m_map_pair(WM4A_AXIS_V, ax_v));
	map<WM4A_AXIS_ID_ENUM, WRHIOMC_AX_MCS_STRUCT>::iterator enum_struct_m_map_iter = enum_struct_template_class.m_map.find(WM4A_AXIS_ID_ENUM(iii));
	if (enum_struct_m_map_iter != enum_struct_template_class.m_map.end())
	{
	}
	else
	{
		cout<<"Find index : "<<iii<<" in class : "<<typeid(enum_struct_template_class).name()<<" Map : "<<typeid(enum_struct_template_class.m_map).name()<<"Failed !"<<endl;
	}

#endif // _TEMPLATE_RETURN_REFERENCE


#ifdef _PTR_
	char *str = NULL;
	get_memory_reference(str);
	strcpy(str, "hello, world\n");
	printf(str);

#endif // _PTR_

#ifdef _STATIC_FCN_
	/*
	静态成员测试：
	1、类中声明静态成员函数和静态成员变量；
	2、在类体外必须添加类域进行定义，使用该静态变量的时候必须跟上类名；
	*/
	CLASS_JINSHAOXUN_DERIVE class_test;
	class_test.cout_base_class_member_fcn();
	//cout<<xxxxx<<endl;
	class_jinshaoxun xd;
	cout<<xd.call_private_number()<<endl;
#endif

#ifdef _VALUE_FINDER_
	
	map_int_int value_find_map;
	for (int i = 0; i < 10; ++i)
	{
		value_find_map.insert(make_pair(i, 10*i));
	}
	value_finder<int,int> value_find(1,90);
	//value_find中的pair是通过value_find_map中的pair来获取的；
	//也就是value_find中的形参对象就是find_if中前面迭代的对象进行传递进来
	map<int,int>::iterator iter = find_if(value_find_map.begin(), value_find_map.end(), value_find);
	if (iter != value_find_map.end())
	{
		cout<<"Find result : iter->first = "<<iter->first<<", iter->second = "<<iter->second<<endl;
	}
	else
	{
		cout<<"Cann't find the result !"<<endl;
	}
	//value_finder value_find(10);
	
#endif // _VALUE_FINDER_
	
	//
	WR4A_STATUS_STRUCT m_wr_status = WR4A_STATUS_STRUCT();
	cout<<m_wr_status.area.carrier_area<<endl;
	cout<<m_wr_status.dock_state.displacement.x<<endl;

#ifdef _INTERPRET_
	WRMC_COMMUNICATION_CONFIG_STRUCT wrmc_config = WRMC_COMMUNICATION_CONFIG_STRUCT();
	WM4A_RO_COMMUNICATION_CONFIG_STRUCT wmmc_config = WM4A_RO_COMMUNICATION_CONFIG_STRUCT();
	wrmc_config.config = WRMC_COM_DEVICE_SERIAL;
	wrmc_config.serial_config.port.baudrate = 9600;
	wrmc_config.serial_config.port.data_bit = 1;
	wrmc_config.serial_config.port.even_odd_bit = 2;
	//wrmc_config.serial_config.port.port_name = ;
	wrmc_config.serial_config.port.stop_bit = 3;
	//char *port_name = "jinshax";
	strcpy(wrmc_config.serial_config.port.port_name, "jinshax");
	//wrmc_config.socket_config.ip_address = "WRMC_IP_ADDRESS";
	wrmc_config.socket_config.port_id = 4;

	wmmc_config = reinterpret_cast<WM4A_RO_COMMUNICATION_CONFIG_STRUCT&>(wrmc_config);

	cout<<wmmc_config.config<<endl;
	cout<<wmmc_config.serial_config.port.baudrate<<endl;
	cout<<wmmc_config.serial_config.port.data_bit<<endl;
	cout<<wmmc_config.serial_config.port.even_odd_bit<<endl;
	cout<<wmmc_config.serial_config.port.port_name<<endl;
	cout<<wmmc_config.serial_config.port.stop_bit<<endl;
	//cout<<wmmc_config.socket_config.ip_address;
	cout<<wmmc_config.socket_config.port_id<<endl;
#endif // _INTERPRET_

#ifdef _BOOST_
	boost_tuple();
	boost_for_each();
	xuda_share_ptr_test();
	test_weak_ptr();
	boost_any_test();
#endif

#ifdef _MAP_PAIR_
	//string loc = string();
	char loc[100] = {};
	cout<<"Please input location :"<<endl;
	cin>>loc;
	cout<<"loc = "<<loc<<endl;
	//map_pair_station_string_2_enum("PORT");
	//char loc[100] = {};
	//cin>>loc;
	//cout<<"loc = "<<loc<<endl;
	map_pair_station_string_2_enum(loc);
#endif

#ifdef _FILE_OPERATION_
	//write_sim_file(999);
	//FILE_OPERATION_read_write_file_c(READ_FILENAME_C);
	//FILE_OPERATION_read_write_file_c_plus();
	
	//FILE_OPERATION_find_ch();	
	//string sdf = string("jin shaoxun name");
	//cout<<FILE_OPERATION_trim_string_space(sdf)<<endl;
	//read_motion_time();
	//read_file();
	//write_file();
	string tet = string("jinshsdf");
	FILE_DATA_BASE *file_parse = new FILE_DATA_BASE(PARSE_FILE, '=', 3, &tet);
	file_parse->set_and_write_data("NAME", "SJHAOXUN");
	file_parse->set_and_write_data("DATA", "2016-06-06");
	string data;
	file_parse->read_and_get_data("DATA", &data);
	int carrier_present;
	file_parse->get_data("CARRIER_PRESENT", &carrier_present);
	cout<<"carrier_present = "<<carrier_present<<endl;
	cout<<"csf"<<endl;
	
	string slot_info;
	file_parse->get_data("PORT", &slot_info);
	for (int i = 0; i < 29; i++)
	{
		switch (slot_info[i])
		{
		case '0':
			cout<<"No Wafer !"<<endl;
			break;
		case '1':
			cout<<"Normal Insert !"<<endl;
			break;
		case '2':
			cout<<"Cross Insert !"<<endl;
			break;
		default:
			cout<<"------"<<endl;
			break;
		}
	}
#endif // _FILE_

#if defined(_TRY_CATCH_)
	/*try
	{
		throw_int(100);
	}
	catch(char* i_throw)
	{
		cout<<"Catch success : "<<i_throw<<endl;
	}*/
	try_catch();

	try
	{
		throw boost::enable_error_info(BOOST_EXCEPTION_CLASS("jinshaoxun....."))
			<<boost::errinfo_errno(100)
			<<boost::errinfo_api_function("sdf");
	}
	catch(BOOST_EXCEPTION_CLASS& e)
	{
		cout<<e.error_msg()<<endl;
		cout<<*boost::get_error_info<boost::errinfo_errno>(e)<<endl;
		cout<<*boost::get_error_info<boost::errinfo_api_function>(e)<<endl;
	}
#endif
	
	WORKFLOW_EXE();

#ifdef _MOVE_WAFER_
	move_wafer();
#endif

#ifdef _WH_TEST_
	WH wh(110, WH4A_LOC_TRACK, WH4A_LOC_PREALIGNER);
	cout<<any_test(10, 11.11)<<endl;
	cout<<any_test(11.22, 10)<<endl;
	cout<<"wh operator = "<<wh+1<<endl;
	cout<<"wh operator = "<<wh*1<<endl;
	cout<<"sizeof(wh.array) = "<<sizeof(wh.array)<<endl;

	factor_function_test();

	cout<<">>compare_operate_less"<<endl;
	compare_operate_less tt_compare_operator;
	cout<<"compare_operate_less = "<<tt_compare_operator.operator()(12,11)<<endl;
	//cout<<"tt_compare_plus = "<<tt_compare_operator.operator ++(111)<<endl;
	compare_operate_plus tt_compare_plus;
	//cout<<"tt_compare_plus = "<<tt_compare_plus.operator ++(111)<<endl;
	cout<<"<<compare_operate_less"<<endl;
	
	struct_contain_struct sstt;
	cout<<"sstt.a = "<<sstt.a<<endl;
	cout<<"sizeof(struct_contain_struct) = "<<sizeof(sstt)<<endl;
	cout<<"dssdfsdfsd"<<(0x3 & 0x1)<<endl;

	/*deque<WH4A_LOC_ENUM> loc_deque;
	loc_deque.push_back(WH4A_LOC_TRACK);
	loc_deque.push_back(WH4A_LOC_PREALIGNER);
	cout<<""<<loc_deque.size()<<endl;*/
	/*int s;
	memset(&s, 1, sizeof(s));
	cout<<s<<endl;*/

	wh.optimise_route(wh.from(), wh.to());

	//test_callback();
	//wh.digui_function(5);
	#if 0
		//boost::shared_ptr<WH> p(new WH(1));
		////cout<<"p->use_count() = "<<p->use_count()<<endl;
		//boost::shared_ptr<WH> q = p->function_return_wh();	
		////cout<<"p->use_count() = "<<p->use_count()<<endl;
		//assert(p = q);

		boost::shared_ptr<Y> p(new Y());
		cout<<p.use_count()<<endl;
		boost::shared_ptr<Y> q = p->f();
		cout<<p.use_count()<<endl;
		p->fcn_out(string("jin"));
		multi_map_compare();
		
	#endif

	boost::shared_ptr<WH> tt_wh_is_null;
	//如果这里没有对对象进行new 则默认是null
	if (NULL == tt_wh_is_null)
	{
		time_t tt_current_time;
		time(&tt_current_time);
		tm *tm_current_time = localtime(&tt_current_time);
		cout<<"****"<<asctime(tm_current_time)<<endl;
		cout<<"tt_wh_is_null is NULL !"<<endl<<endl;
	}

	WH::tt_template_two_parameters<double,int>(5.5,5.6);

	char dest[2] = "1";
	cout<<"sizeof(dest) = "<<sizeof(dest)<<endl;
	char* src = "jinshaoxun";
	cout<<"src = "<<src<<endl;
	cout<<"dest = "<<dest<<endl;
	//cout<<"Result = "<<wh.tt_strcpy(dest, src)<<endl;
	cout<<"Result = "<<strncpy(dest, src,9)<<endl;

	char to;
	char from[10] = "jinsha";
	//memcpy(&to, from, sizeof(from));
	//cout<<"to = "<<to<<endl;

	strncpy(&to, from,4);
	cout<<"to = "<<to<<endl;
	cout<<"to + 1 = "<<*(&to+1)<<endl;

	//string_strcpy_test();
	string_strncpy_test();
	tt_digui_result();
	tt_digui_for();

	//验证赋值构造函数在私有变量是不允许的场景
	WH tt_equal_src;
	tt_equal_src.pBuffer = "jinshaoxun";
	cout<<"buffer = "<<tt_equal_src.pBuffer<<endl;
	if (NULL != &tt_equal_src)
	{
		cout<<"not null "<<endl;
	}

	//WH tt_equal_dest;
	//tt_equal_dest.pBuffer = "nuxoahsnij123456";
	//tt_equal_dest = tt_equal_src;
	//cout<<"equal success "<<endl;
	//cout<<"buffer = "<<tt_equal_dest.pBuffer<<endl;

	//
	OPERATOR_EQUAL_CLASS tt_operator_src(10);
	OPERATOR_EQUAL_CLASS tt_operator_dest(11);
	tt_operator_src.pBUFFER = "123456789";
	cout<<"tt_operator_src.pBUFFER = "<<tt_operator_src.pBUFFER<<endl;
	
	tt_operator_dest = tt_operator_src;
	cout<<"tt_operator_dest.pBUFFER = "<<tt_operator_dest.pBUFFER<<endl;

	boost::shared_ptr<WH> tt_count_WH;
	cout<<"tt_count_WH.use_count() = "<<tt_count_WH.use_count()<<endl;

	WH::ROUTE_LOC tt_route_loc_1;
	WH::ROUTE_LOC tt_route_loc_2;

	test_subject_observe();

	int *result_nbr = new int(10);
	cout<<"*result_nbr = "<<*result_nbr<<endl;
	
	wh.getNbr(result_nbr);
	
	cout<<"*result_nbr = "<<*result_nbr<<endl;

	cout<<endl;
	
	

#endif

#ifdef _LIST_TEST_

	//list_main();
	NODE *tt_1 = new NODE();
	delete tt_1;
	if (NULL == tt_1)
	{
		cout<<"NULL == tt_1"<<endl;
	}

#endif
	
	char xdf[100];
	if (strcmp(xdf, "") == 0)
	{
		cout<<"NULL !"<<endl;
	}
	else
	{
		cout<<"Not Null !"<<endl;
	}

	char *sdf = "sdf dsf";
	string ddsf = sdf;
	cout<<"char = "<<sdf<<endl;
	cout<<"string = "<<ddsf<<endl;
	cout<<"ddsf.substr(0,5) : "<<ddsf.substr(0,5)<<endl;
	if (0 ==ddsf.substr(0,5).compare("sdf d"))
	{
		cout<<"SAME !"<<endl;
	}
	else
	{
		cout<<"NOT SAME !"<<endl;
	}

	char c_char[] = {"abc"};
	char *c_char_ = "123456";
	cout<<"strlen(c_char) = "<<dec<<strlen(c_char)<<endl;
	cout<<"sizeof(c_char) = "<<sizeof(c_char)<<endl;
	cout<<"(int)(&c_char[1]) = "<<hex<<(&c_char[1])<<endl;
	cout<<"(int)(&c_char[2]) = "<<(int)(&c_char[2])<<endl;
	cout<<"(int)(&c_char[3]) = "<<(int)(&c_char[3])<<endl;

	cout<<"c_char = "<<c_char<<endl;
	cout<<"sizeof(c_char_) = "<<sizeof(c_char_)<<endl;
	cout<<"strlen(c_char_) = "<<strlen(c_char_)<<endl;

	FORWARD_QUOTE_A* instance_AA = new FORWARD_QUOTE_A();
	instance_AA->tt_bb->do_something();

	int tt = 2;
	cout<<-tt<<endl;

	string t1 = "1819";
	cout<<t1<<", size:"<<t1.size()<<endl;
	string t2 = "1819 ";
	cout<<t2<<", size:"<<t2.size()<<endl;
	string t3 = t2 + t1;
	cout<<t3<<", size:"<<t3.size()<<endl;

	short int tt_endian = 0x1234;
	char *little = (char*)&tt_endian;

	if ( 0x34 == *little && 0x12 == *(little + 1))
	{
		cout<<"Little"<<endl;
	}
	if(0x12 == *little && 0x34 == *(little + 1))
	{
		cout<<"Big"<<endl;
	}

	ascci_operation_main();

#ifdef _CAST_
	//cast_test();

#endif


#ifdef _HONEYWELL_
	//char honey_str[100];
	//void *p1 = malloc(100);
	//char *p2 = honey_str;
	//int n = 10;
	//cout<<"sizeof(honey_str) = "<<dec<<sizeof(honey_str)<<endl;
	//cout<<"sizeof(p1) = "<<sizeof(p1)<<endl;
	//cout<<"sizeof(p2) = "<<sizeof(p2)<<endl;
	//cout<<"sizeof(n) = "<<sizeof(n)<<endl;

	int *p[10];
	cout<<dec<<"sizeof(p) = "<<sizeof(p)<<endl;
	cout<<"sizeof(p[0]) = "<<sizeof(p[0])<<endl;
	int (*p1)[10];
	cout<<"sizeof(p1) = "<<sizeof(p1)<<endl;
	cout<<"sizeof(p1[0]) = "<<sizeof(p1[0])<<endl;

	struct token_t 
	{
		char digit:4;
		char index:4;
		unsigned short data:8;
		unsigned long tick;
	};
	cout<<"sizeof(token_t) = "<<sizeof(token_t)<<endl;
		
#endif

#ifdef _CUSTOM_MAP_
	
	custom_map();
	vector_delete();

#endif

#ifdef _THREAD_MUTEX_
	//multi_thread();
	//sellTickets();

#endif // _THREAD_MUTEX_

#ifdef _TEMPLATE_

	test_template_mc_changed();

#endif // __TEMPLATE__
	
	const int i_t = 0;
	cout<<sizeof(i_t)<<endl;

	TT_STATIC tt_src;
	TT_STATIC tt_dest(tt_src);

	int src_tt = 0;
	funcc(&src_tt);
	cout<<src_tt<<endl;

	int ee[4] = {1,2,3,4};
	int *p = (int*)(&ee + 1);
	printf("%x\n", &ee[4]);
	printf("%x\n",&p[-1]);

	system("pause");

	return 0;
}


void funcc(int* tt)
{
	cout<<"tt = "<<&tt<<endl;
	*tt = 100;
	cout<<"tt = "<<&tt<<endl;
}