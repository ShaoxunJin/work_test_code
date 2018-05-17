#ifndef FILE_READ_WRITE_H
#define FILE_READ_WRITE_H

#include "head_file.h"

#define OK 0

#define READ_FILENAME_C ".\\read_c.txt"
#define WRITE_FILENAME_C ".\\write_c.txt"
#define READ_FILE_C_PLUS ".\\read_c++.txt"
#define WRITE_FILE_C_PLUS ".\\write_c++.txt"
#define PARSE_FILE ".\\parse_file.txt"

#define format_string_file_name ".\\format_string.txt"

#define WU_SIM_FILE ".\\WU_sim2_info.txt"

void default_parameter_function(int a = 1, double b = 1.1);

void prt_function(string *a = NULL);

void read_file();
void write_file();
void read_write_file();
void write_format_string_file();
string format_string(char* character, int nbr);
void read_matrix_file();
void read_motion_time();
void write_sim_file(int wafer_present);
void FILE_OPERATION_read_write_file_c(const char* file_name);
void FILE_OPERATION_read_write_file_c_plus();
void FILE_OPERATION_find_ch();
string& FILE_OPERATION_trim_string_space(string& str);

/*
1�����Ƚ�txt�����ݰ��ջ����ĸ�ʽ��ȡ������
2���ֱ����ÿ�ж�ȡ�����Ľ��н���������=�����ҵķ��Ž��н������洢��
3������д���� ����write_data��ʱ���ǽ�֮ǰ�洢������ȫ�����½���дһ�飨�������������ĳһ���������ݣ���
**�����ϻ����Խ������� �о������е㸴��
*/
class FILE_DATA_BASE
{
public:
	FILE_DATA_BASE(const std::string &file_name,
					char delim = '=',
					int instruction_num = 0,
					std::string *instruction = NULL);
	~FILE_DATA_BASE();
	
	void read_data();
	void write_data();

	template<typename T>
	void set_data(std::string name, T value);

	template<typename T>
	void get_data(std::string name, T *value);

	template<typename T>
	void set_and_write_data(std::string name, T value);

	template<typename T>
	void read_and_get_data(std::string name, T *value);

protected:
private:
	void m_parse(char *str);
	std::string& m_trim_space(std::string& str);
	std::vector<std::string> m_instruction;
	std::map<std::string, std::string> m_data;	//���ڴ洢����ǰ��������ֵ��
	std::list<std::string> m_data_order;		//���ڲ������ǰ��������ַ�
	std::string m_file_name;
	char m_delim;
};

//���в������õ�m_data�� ����дͨ��write_data��ʵ��
template<typename T>
void FILE_DATA_BASE::set_data(std::string name, T value)
{
	std::map<std::string, std::string>::iterator iter = m_data.find(name);
	std::ostringstream os;
	//����ΪʲôҪ��os�أ���
	os<<value;
	//����ҵ�����valueֵ��ֵ��name
	if (iter != m_data.end())
	{
		iter->second = os.str();
		cout<<"Find name : "<<name<<" Success !"<<endl;
	}
	//���û���ҵ� ������һ��name Ȼ�����valueֵ����name
	else
	{
		m_data[name] = os.str();
		m_data_order.push_back(name);
		cout<<"Find name : "<<name<<"Failed !"<<endl;
	}
}

template<typename T>
void FILE_DATA_BASE::get_data(std::string name, T *value)
{
	std::map<std::string, std::string>::iterator iter = m_data.find(name);
	if (iter != m_data.end())
	{
		istringstream is(iter->second);
		is>>*value;
		//*value = iter->second;
		//����ΪʲôҪ������  ����Ϊ���Խ������string���ݲ��뵽T������
	}
	else
	{
		cout<<"get_data name : "<<name<<"Failed !"<<endl;
	}
}

template<typename T>
void FILE_DATA_BASE::set_and_write_data(std::string name, T value)
{
	set_data(name, value);
	write_data();
}

template<typename T>
void FILE_DATA_BASE::read_and_get_data(std::string name, T *value)
{
	read_data();
	get_data(name, value);

}

#endif