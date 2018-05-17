#include "stdafx.h"
#include "file_read_write.h"
extern vector<double> vec_data_read_write;


void default_parameter_function(int a , double b)
{
	function_in(__FUNCTION__);

	cout<<"int = "<<a<<endl;
	cout<<"double = "<<b<<endl;

	function_out(__FUNCTION__);
}

void prt_function(string *a)
{
	function_in(__FUNCTION__);
	cout<<"a = "<<*a<<endl;
	function_in(__FUNCTION__);

}

void read_file()
{
	FILE *ptr_read = NULL;
	ptr_read = fopen(READ_FILENAME_C,"r");
	if (NULL == ptr_read)
	{
		printf("Open file failed!\nPlease check the filename or file path\n");
		system("pause");
	}
	else
	{
		printf("Open read source file OK!\n");
	}
	//vector<double> data_read;
	double data_buffer = 0.0;
	while(!feof(ptr_read))
	{
		fscanf(ptr_read, "%lf", &data_buffer);
		vec_data_read_write.push_back(data_buffer);
	}
	if(NULL != ptr_read)
	{
		if(NULL == fclose(ptr_read))
		{
			printf("Read File Success !\n");
		}
		else
		{
			printf("Read File Failed !\n");
		}
	}

	const static int iStaticNbr = 99;
	
	return ;
}

void write_file()
{
	FILE *ptr_write = NULL;
	ptr_write = fopen(WRITE_FILENAME_C, "w");
	if (NULL == ptr_write)
	{
		printf("Create file failed!\nPlease check the filename or file path\n");
		exit(1);
	}
	else
	{
		printf("Create file OK !\n");
	}
	int data_size = vec_data_read_write.size();
	/*for (int i = 0; i < data_size; ++i)
	{
		fprintf(ptr_write, "%lf\n", vec_data_read_write[i]);
	}*/
	//下面采用迭代 iterator进行
	vector<double>::iterator iter;
	for(iter = vec_data_read_write.begin(); iter != vec_data_read_write.end(); ++iter)
	{
		fprintf(ptr_write, "%lf\n", *iter);
	}

	if(NULL != ptr_write)
	{
		if(NULL == fclose(ptr_write))
		{
			printf("Write File Success !\n");
		}
		else
		{
			printf("Write File Failed !\n");
		}
	}
	/********通常采用如下方式对文件指针进行扫尾工作*********/
	/*if(NULL != ptr_write)
	{
		fclose(ptr_write);
		ptr_write = NULL;
	}*/

	return;
}

void read_write_file()
{

}

void write_format_string_file()
{

	//创建一个file
	FILE *format_string_file = NULL;
	format_string_file = fopen(format_string_file_name,"a+");
	if(!format_string_file)
	{
		printf("File %s is not exist!\n",format_string_file_name);
	}
	else
	{	
		//ok -- fprintf(format_string_file,"%s %s\n",format_string("jin",2).c_str(),format_string("shao",2).c_str());
		//
		fprintf(format_string_file,"%s %s %s\n",
									format_string("jin",1).c_str(),
									format_string("shao",1).c_str(),
									format_string("xun",2).c_str());
		//string name = "jishaoxun";
		//fprintf(format_string_file, "%s\n",name.c_str());
	}

	if(format_string_file)
	{
		fclose(format_string_file);
		format_string_file = NULL;
	}

}

string format_string( char* character, int nbr )
{
	char rtn_char[100] = {};
	string rtn_string;
	for(int i = 0; i < nbr; ++i)
	{
		strcat(rtn_char,character);
	}
	rtn_string = rtn_char;
	return rtn_string;
}


void read_matrix_file()
{
	const char *cFileMatrix = ".\\matrix.dat";
	FILE *pFileMatrix = NULL;

	double dMatrix[2][2] = {{0.0, 0.0},{0.0, 0.0}};
	int rtn = OK;

	pFileMatrix = fopen(cFileMatrix, "r");
	if (pFileMatrix == NULL)
	{
		cout<<"Open File :"<<cFileMatrix<<" Failed !"<<endl;
		rtn = 1;
	}

	for (int i = 0; i < 2; ++i)
	{
		rtn = fscanf(pFileMatrix, "%lf\t%lf\n", &dMatrix[i][0], &dMatrix[i][1]);
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0 ;j < 2; ++j)
		{
			cout<<"dMatrix["<<i<<"]["<<j<<"] = "<<dMatrix[i][j]<<endl;
		}
	}
}

//读取仿真文件，将文件中的信息以字符串的形式读上来之后
void read_motion_time()
{
	const char *func = "WRSPDM::get_motion_time";
	int rtn = OK;

	int iSim_motion_time = 0;
	int j = 0;
	char temp_mapping_info[36] = {0};
	char temp_sim_motion_time[36] = {0};
	char sim_motion_time_char[36] = {0};
	FILE *fd = fopen(".\\WR_test_data.dat", "r");

	if (fd != 0)
	{
		for(int i = 0; i < 4; ++i)
		{
			if(i != 3)
			{
				fscanf(fd,"%s\n", temp_mapping_info);
			}
			else
			{
				fscanf(fd,"%s\n", temp_sim_motion_time);
			}
		}
		//m_spet.trace(func, "temp_sim_motion_time = %s", temp_sim_motion_time);
		printf("temp_sim_motion_time = %s\n", temp_sim_motion_time);
		printf("strlen(temp_sim_motion_time) = %d\n", strlen(temp_sim_motion_time));
		for(unsigned int i = 0; i < strlen(temp_sim_motion_time); ++i)
		{
			//0~10的数据取出
			if(temp_sim_motion_time[i] >= 48 && temp_sim_motion_time[i] <= 57)
			{
				//sim_motion_time_char[j] = temp_sim_motion_time[i];
				//++j;
				strcpy(sim_motion_time_char, &temp_sim_motion_time[i]);
				break;
			}	
		}
		printf("sim_motion_time_char = %s\n", sim_motion_time_char);
		//字符串转int
		iSim_motion_time = atoi(sim_motion_time_char);
		printf("iSim_motion_time = %d\n", iSim_motion_time);

		fclose(fd);
	}
	else
	{
		rtn = 1;
	}
}

void write_sim_file(int wafer_present)
{
	FILE *wu_sim_file_read = fopen(WU_SIM_FILE, "r+");
	//先读上来
	char buffer[9][100];
	for (int i = 0; i < 9; ++i)
	{
		if (i != 8)
		{
			fscanf(wu_sim_file_read,"%s\n",buffer[i]);
			printf("i= %d,%s\n",i,buffer[i]);
		}
	}

	if (NULL != wu_sim_file_read)
	{	
		fclose(wu_sim_file_read);
		wu_sim_file_read = NULL;
	}
	//再写下去 可以同时读写 但是不能先删除后增加 how?
	FILE *wu_sim_file_write = fopen(WU_SIM_FILE, "w+");
	for (int i = 0; i < 9; ++i)
	{
		if (i != 8)
		{
			fprintf(wu_sim_file_write, "%s\n",buffer[i]);
		}
		else
		{
			fprintf(wu_sim_file_write, "p_chuck_present=%d\n",wafer_present);
		}
	}
	if (NULL != wu_sim_file_write)
	{
		fclose(wu_sim_file_write);
		wu_sim_file_write = NULL;
	}
}

void FILE_OPERATION_read_write_file_c(const char* file_name)
{
	function_in(__FUNCTION__);
	//创建文件指针
	FILE *pFILE_READ_C = fopen(READ_FILENAME_C, "r");
	FILE *pFILE_WRITE_C = fopen(WRITE_FILENAME_C, "w");
	char temp_char[100] = {};
	std::vector<string> v_read_write;
	std::string temp_string;
	if (NULL == pFILE_READ_C)
	{
		printf("Open file failed !\n");
	}
	else
	{
		while (!feof(pFILE_READ_C))
		{
			fscanf(pFILE_READ_C,"%s\n",temp_char);
			temp_string = temp_char;
			v_read_write.push_back(temp_string);
			printf("%s\n",temp_char);
		}
	}
	if(NULL == pFILE_WRITE_C)
	{
		printf("Open file failed !\n");
	}
	else
	{
		for (int i = 0; i < v_read_write.size(); ++i)
		{
			printf("i = %d, %s\n",i,v_read_write[i].c_str());
			fprintf(pFILE_WRITE_C, "%s\n", v_read_write[i].c_str());
		}
	}

	if (NULL != pFILE_READ_C)
	{
		fclose(pFILE_READ_C);
		pFILE_READ_C = NULL;
	}
	if (NULL != pFILE_WRITE_C)
	{
		fclose(pFILE_WRITE_C);
		pFILE_WRITE_C = NULL;
	}
	function_out(__FUNCTION__);
}

void FILE_OPERATION_read_write_file_c_plus()
{
	function_in(__FUNCTION__);

	std::string temp_string;
	std::vector<string> vec_string;

	ifstream file_read(READ_FILE_C_PLUS, ios_base::in);
	ofstream file_write(WRITE_FILE_C_PLUS, ios_base::out);
	if (!file_read.is_open())
	{
		cout<<"Open file: "<<READ_FILENAME_C<<endl;
	}
	else
	{
		//while (!file_read.eof())
		////while(file_read>>temp_string)
		//{
		//	file_read.getline(temp_char,100000,'\n');
		//	//file_read>>temp_string;
		//	cout<<temp_char<<endl;
		//}
		//通过string中的函数来获取整行内容；
		//while会将文件内所有的都字符都打印取出
		while(getline(file_read, temp_string))
		{
			cout<<temp_string<<endl;
			vec_string.push_back(temp_string);
		}
		//采用if形式
		/*getline(file_read, temp_string);
		cout<<temp_string<<endl;
		getline(file_read, temp_string);
		cout<<temp_string<<endl;
		getline(file_read, temp_string);
		cout<<temp_string<<endl;		
		getline(file_read, temp_string);
		cout<<temp_string<<endl;*/
	}

	if (!file_write.is_open())
	{
		cout<<"Open file : "<<WRITE_FILE_C_PLUS<<endl;
	}
	else
	{
		for (int i = 0; i < sizeof(vec_string.size()); ++i)
		{
			//写文件
			cout<<"Line["<<i<<"]:"<<vec_string[i]<<endl;
			file_write<<vec_string[i]<<endl;
		}
	}
	
	function_out(__FUNCTION__);
}


void FILE_OPERATION_find_ch()
{
	function_in(__FUNCTION__);

	char* first = "jin=shaoxun";
	char *p = strchr(first, '=');
	if (p != NULL)
	{
		cout<<"p-first = "<<p-first<<endl;
	}
	cout<<"string(first,p-first) = "<<string(first,p-first)<<endl;
	cout<<"string(first,p+1) = "<<string(p+1)<<endl;

	function_out(__FUNCTION__);
}

//下面函数的目的是删除字符串首末两端的空格字符
string& FILE_OPERATION_trim_string_space(string& str)
{
	function_in(__FUNCTION__);

	string name = string(str);
	cout<<"name = "<<name<<endl;
	size_t first = 0;
	size_t last = name.length();

	while(first < last)
	{
		if (str[first] != ' ')
		{
			break;
		}
		else
		{
			++first;
		}
		cout<<"first = "<<first<<endl;
	}
	while (last > first)
	{
		if (str[last - 1] != ' ')
		{
			break;
		}
		else
		{
			--last;
		}
		cout<<"last = "<<last<<endl;

	}
	str = string(&name[first], &name[last]);

	function_out(__FUNCTION__);
	return name;
}

FILE_DATA_BASE::FILE_DATA_BASE(const std::string &file_name,
							   char delim /* =  */,
							   int instruction_num /* = 0 */,
							   std::string *instruction /* = NULL */)
							   :m_file_name(file_name)
							   ,m_delim(delim)
{
	cout<<"This is class :"<<typeid(FILE_DATA_BASE).name()<<" Construction !"<<endl;
	//如果这里instruction_num不是零的话 编译过程不会报错但是运行过程报了 null point
	//如果下面使用动态内存的话就是失败的 一定要使用&取值符进行计算
	m_instruction.assign(instruction, instruction + instruction_num);
	cout<<"m_instruction = "<<*instruction<<endl;
	cout<<"m_instruction.size() = "<<m_instruction.size()<<endl;
	read_data();
	////write_data();
}

FILE_DATA_BASE::~FILE_DATA_BASE()
{
	cout<<"This is class :"<<typeid(FILE_DATA_BASE).name()<<" Deconstruction !"<<endl;

}

void FILE_DATA_BASE::read_data()
{
	cout<<"Begin to read data from File :"<<m_file_name<<endl;
	std::ifstream fin(m_file_name.c_str());
	char temp_char[256];
	if (fin)
	{
		m_data.clear();
		m_data_order.clear();
		while (fin.getline(temp_char, 256))
		{
			m_parse(temp_char);
		}
	}
	else
	{
		cout<<"Open file failed !"<<endl;
	}
	cout<<"Finish to read data from File :"<<m_file_name<<endl;

}

void FILE_DATA_BASE::write_data()
{
	cout<<"Begin to write_data ..."<<endl;
	
	std::ofstream fout(m_file_name.c_str());
	if(fout)
	{
		std::map<std::string, std::string>::iterator data_it;
		for (std::list<std::string>::iterator it = m_data_order.begin();
			it != m_data_order.end();
			++it)
		{
			data_it = m_data.find(*it);
			cout<<"write_data :"<<*it<<endl;
			if (data_it != m_data.end())
			{
				fout<<*it<<m_delim<<" "<<m_data[*it]<<endl;
				cout<<*it<<m_delim<<" "<<m_data[*it]<<endl;
			}
		}
	}
	else
	{
		cout<<"Open file failed "<<endl;
	}
	cout<<"Finish to write_data ..."<<endl;
}

void FILE_DATA_BASE::m_parse(char *str)
{
	cout<<"Begin to parse char :"<<str<<endl;
	if (str[0] != '#')
	{
		char *p = NULL;
		p = strchr(str, m_delim);
		if (p != NULL)
		{
			string first(str, p - str);//m_delim前面的字符串
			string second(p + 1); //m_delim后面的字符串
			m_trim_space(first);
			m_trim_space(second);
			cout<<"First:"<<first<<endl;
			cout<<"Second:"<<second<<endl;
			if(m_data.empty())
			{
				cout<<"m_data is empty"<<endl;
			}
			std::map<std::string, std::string>::iterator it = m_data.find(first);//实际上一开始m_data是empty
			if (it == m_data.end())
			{
				m_data_order.push_back(first);//将m_delim左右的两个数值插入到m_data_order中
				m_data.insert(make_pair(first, second));
			}			
		}
	}

	cout<<"End to parse char :"<<str<<endl;

}


std::string& FILE_DATA_BASE::m_trim_space(std::string& str)
{
	string name = string(str);
	cout<<"name = "<<name<<endl;
	size_t first = 0;
	size_t last = name.length();

	while(first < last)
	{
		if (str[first] != ' ')
		{
			break;
		}
		else
		{
			++first;
		}
		cout<<"first = "<<first<<endl;
	}
	while (last > first)
	{
		if (str[last - 1] != ' ')
		{
			break;
		}
		else
		{
			--last;
		}
		cout<<"last = "<<last<<endl;

	}
	str = string(&name[first], &name[last]);
	return name;

}