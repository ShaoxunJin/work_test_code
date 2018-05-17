#include "stdafx.h"
#include "head_file.h"
#include "char_test.h"

extern int i_static_nbr;
int iQuoteNbr = 0;

void char_test(char out_char[])
{
	cout<<"测试输出字符串"<<endl;
	//out_char  ="jinsahoxun";
	cout<<"测试结果。。。。"<<out_char<<endl;
	cout<<"sizeof() = "<<sizeof(out_char)<<endl;
	cout<<""<<endl;

	//定义字符串数组
	char char_array[10] = "0";
	cout<<"char_array:"<<char_array<<endl;
	strcpy(char_array,"shaoxun");
	cout<<"char_array:"<<char_array<<endl;
	
	return;
}  

//函数形参应用测试
int quote_test( int quote_input, int& quote_output )
{
	cout<<"\nBegin to quote_test ....."<<endl;
	quote_output = quote_input;
	return quote_output;
	cout<<"End of quoter_test .......\n"<<endl;
}

int& quote_test_return_function()
{
	iQuoteNbr++;
	int i = 10;
	return i;
}

void quote(int& input )
{
	//int &input_quote = input;
	//int const& input_quote_const = input;
	cout<<"input:"<<input<<endl;
	//cout<<"input_quote:"<<input_quote<<endl;
	//cout<<"input_quote_const:"<<input_quote_const<<endl;
	//input++;
	//cout<<"After ++ , input = "<<input<<endl;
	cout<<"After ++ , input = "<<input<<endl;
}

void transfer_char_to_const_char()
{
	char const_char[10];
	cout<<"cosnt_char_addr = "<<const_char<<endl;
	cout<<"sizeof(const_char) = "<<sizeof(char)*strlen(const_char)<<endl;
	char *transfer_test = "tr";
	cout<<"transfer_test = "<<sizeof(char)*strlen(transfer_test)<<endl;
	cout<<"sizeof(char) = "<<sizeof(char)<<endl;
	strcpy(const_char,transfer_test);
	//const_char = transfer_test;
	cout<<"const_char : "<<const_char<<endl;
}

void char_extern_static()
{
	cout<<"i_static_nbr:"<<i_static_nbr<<endl;
}
