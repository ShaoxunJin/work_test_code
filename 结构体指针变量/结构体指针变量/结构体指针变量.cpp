// �ṹ��ָ�����.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct stu
	{
		int num;
		char *name;									//name��ָ������׵�ַ��name��ַ�д�ŵ���jinshaoxun�ַ���
		char sex;
		float score;
	} boy1 = {102,"Jin Shaoxun",'M',1000000},*pstu;


struct nature_alignment
	{
		char a;
		char b;
		short c;
		long d;
		int e;
	}ss;
struct structA
	{
		int iMember;
		char *cMember;
	};

int _tmain(int argc, _TCHAR* argv[])
{
	//pstu = &boy1;
	//printf("Number=%d\nName=%s\n",boy1.num,++boy1.name);	//���Ӧ����name�׸���ַ����ƫ����һλ��ʼ���
	//printf("Sex=%c\nScore=%f\n",boy1.sex,boy1.score);

	//printf("Number=%d\nName=%s\n",(*pstu).num,(*pstu).name+2);//���Ӧ����name�д�ŵ������׸�����ƫ������λ
	//printf("Sex=%c\nScore=%f\n",(*pstu).sex,(*pstu).score);

	//printf("Number=%d\nName=%s\n",pstu->num,pstu->name);
	//printf("Sex=%c\nScore=%f\n",pstu->sex,pstu->score);
	//printf("int_length=%d\n",sizeof(int));
	//printf("float_length=%.20f\n",boy1.score);
	//printf("char_length=%d\n",sizeof(char));
	//printf("double_length=%d\n",sizeof(double));
	structA instant1, instant2;
	char c = 'a';
	char t[] = "jinsahoxun";
	instant1.iMember = 1;
	instant1.cMember = &c;
	printf("result = %c\n",*(instant1.cMember));
	instant2 = instant1;
	*(instant2.cMember) = 'b';
	printf("result = %c\n",*(instant1.cMember));
	printf("sizeof=%d\n",sizeof(ss));
	printf("sizeof=%d\n",sizeof(int));
	printf("name=%s\n",t);
	return 0;
}

