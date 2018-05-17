#include "stdafx.h"
#include "read_file.h"

void read_from_file()
{
	cout<<"Please input your FileName:"<<endl;
	char cFileName[100];
	cin>>cFileName;
	ifstream ReadFile(cFileName,ios_base::in);
	if(!ReadFile)
	{
		cout<<"File not exist!"<<endl;
		exit(-1);
	}
	int i = 0;
	while(!ReadFile.eof())
	{
		ReadFile>>i;
		cout<<i<<endl;
	}
}