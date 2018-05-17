#include "stdafx.h"
#include "head_file.h"

//gloable
char response_string[64];

void string_test()
{
	string name = "jinshaoxun";
	const char *c_name = NULL;
	c_name = name.c_str();
	cout<<"c_name = "<<c_name<<endl;
	char copy_name[100];
	strcpy(copy_name, c_name);
	cout<<"copy_name = "<<copy_name<<endl;
	string family_name = name.substr(0,3);
	cout<<"family_name = "<<family_name<<endl;
	string::size_type index_m = name.find("s");
	cout<<"index_m = "<<index_m<<endl;

 	return;

}

void istringstream_test()
{
	//ostringstream是向一个string中写入相应的内容 然后调用cout或者是return进行返回
	//istringstream是从一个string中读相应的内容
	string full_name = "jinshaoxun____11111";
	string second_name = "";
	istringstream is(full_name);
	is>>second_name;
	cout<<"second_name = "<<second_name<<endl;
	
	return;
}

void char_2_string()
{
	//定义一个char[]
	char char_change[] = "char_2_string";
	//
	string string_change = char_change;
	string string_out = "This is string out!";
	cout<<"string_change = "<<string_change<<endl;
	printf("string_out = %s\n",string_out.c_str());

	string string_source = "jinshaoxun";
	string string_destinate = "";
	cout<<"string_source = "<<string_source<<endl;
	cout<<"string_destinate = "<<string_destinate<<endl;

	string_destinate = string_source;
	cout<<"string_destinate = "<<string_destinate<<endl;

	//字符串拷贝情况下最好使用字符数组形式
	//后续在coding过程中最好采用字符数组形式
	strcpy(response_string, string_destinate.c_str());
	
	cout<<"response_string = "<<response_string<<endl;

	printf("string_change = %s\n", string_change.c_str());


	char t_char[64] = "this is test!";
	cout<<"t_char = "<<t_char<<endl;
	memset(t_char,0,64*sizeof(char));
	cout<<"t_char = "<<t_char<<endl;
	string t_string = "this is test!";
	//t_char[64] = t_string.c_str();
	memcpy(t_char, t_string.c_str(),64*sizeof(char));
	cout<<"t_char = "<<t_char<<endl;
	
	return;
}

void string_2_char()
{
	string string_change = "string_2_char";
	const char *char_change = NULL;
	char_change = string_change.c_str();
	printf("char_change = %s\n", char_change);
	
	return;
}

void string_vector()
{
	vector<string> vector_string;
	vector_string.push_back("jin");
	vector_string.push_back("shao");
	vector_string.push_back("xun");
	cout<<"vector_string.size() = "<<vector_string.size()<<endl;
	vector<string>::iterator index_iter = vector_string.begin();
	for(int i = 0; i < vector_string.size(); ++i )
	{
		cout<<"vector_string["<<i<<"] = "<<vector_string[i]<<endl;
	}
	vector_string.clear();
	cout<<"vector_string.size() = "<<vector_string.size()<<endl;

	//string tt_tet = "123456";
	//cout<<tt_tet.erase(3)<<endl;

	//cout<<"  "<<endl;

	return;


}

void* return_globle_string()
{	
	return response_string;
}

//采用双重指针方式进行
void get_memory(char** p)
{
	*p = (char*)malloc(100);
}

//采用引用方式进行 实际这里的P就是传进来的指针参数
void get_memory_reference(char* &p)
{
	p = (char*)malloc(100);
}

//这是一个涉及到内存分配的问题
//可以编译  也可以运行 但是实际上的这个a的值？？
void string_strcpy_test()
{
	function_in;
	char a;
	char *ptr_a = &a;
	strcpy(&a, "abcd");
	//printf(ptr_a);
	//printf("a = %c\n",a);

	function_out;
}

void string_strncpy_test()
{
	function_in;

	char to[10];
	memset(to, 0x0, sizeof(to));
	for (int i = 0 ;i < sizeof(to); ++i)
	{
		if ('\0' == to[i])
		{
			cout<<"i = "<<i<<": "<<to[i]<<endl;
		}
	}

	char from[9] = "12345678";
	strncpy(to, from, sizeof(from));
	if ('\0' == to[9])
	{
		cout<<"The last oen character is "<<to[9]<<endl;
	}

	function_out;
}
