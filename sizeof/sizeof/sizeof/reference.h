#ifndef REFERENCE_H
#define REFERENE_H

#include "head_file.h"

//����һ��ģ���ࣻ
//ͨ��pair����ṹ��
//��������ĳ���ṹ��
template<typename T>
class TEMPLATE_CLASS_REFERENCE
{
	TEMPLATE_CLASS_REFERENCE();
	~TEMPLATE_CLASS_REFERENCE();
	
	T& return_status();
};


TEMPLATE_CLASS_REFERENCE::TEMPLATE_CLASS_REFERENCE()
{
	cout<<"Construct TEMPLATE_CLASS_REFERENCE"<<endl;
}

T& TEMPLATE_CLASS_REFERENCE::return_status()
{
	return T;
}



#endif