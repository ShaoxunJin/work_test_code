// malloc_free.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

struct student
{
	int num;
	char *name;
	char sex;
	float score;
};

int _tmain(int argc, _TCHAR* argv[])
{
	//student *ps
	//ps = (struct student*)malloc(sizeof(strct student))
	student *jin;
	cout<<sizeof(student)<<endl;

	jin = (student *)malloc(sizeof(*jin));
	jin->name = "jinshaoxun";
	jin->num = 1;
	jin->score = 99;
	jin->sex = 'M';
	cout<<"name = "<<jin->name<<endl;
	cout<<"sex = "<<jin->sex<<endl;
	free(jin);
	// free 之后就已经归为原始状态
	cout<<"num = "<<jin->num<<endl;
	cout<<"score= "<<jin->score<<endl;
	return 0;
}

