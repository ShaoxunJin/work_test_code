#ifndef ENUM_REGISTER_H
#define ENUM_REGISTER_H

#include <map>
#include <string.h>

namespace WRH
{
#define REGISTER_ENUM_BEGIN(name) class t_##name##_str : public ENUM_CONVERT_BASE_CLASS<name>\
	{\
	public:\
	~t_##name##_str(){}\
	t_##name##_str()

//实现的时候是在构造函数中进行赋值操作
#define REGISTER_ENUM(item)                 this->operator[](#item) = item

#define REGISTER_ENUM_END }

//模板类
	template<typename T>
	class ENUM_CONVERT_BASE_CLASS : public map<const char*, T>
	{
	public:
		bool to_enum(const char* str, T& value)
		{
			for (typename std::map<const char*, T>::iterator iter = this->begin();
				iter != this->end();
				iter++)
			{
				if (strcmp(iter->first, str) == 0)
				{
					value = iter->second;
					return true;
				}
			}
			return false;
		}

		const char* to_string(T value)
		{
			const char* str = NULL;
			typename map<const char*, T>::iterator iter = this->begin();
			while (iter != this->end())
			{
				if (iter->second == value)
				{
					str = iter->first;
					break;
				}
				iter++;
			}
			if(iter == this->end())
			{
				cout<<"enum not exist in the data base, you may not register the enum value ! "<<endl;
			}
			return str;
		}
	};

}



#endif