// calculate_2_power.cpp : Defines the entry point for the console application.
//�˺������ڲ��Լ�������һ�����Ƿ���2��N����

#include "stdafx.h"
#include <math.h>

double calculate_pow_2(double a)
{
	double result;
	double result_1 = log10(a);
	double result_2 = log10(2.0);
	result = log10(a)/log10(2.0);
	//result = int(pow(a,b));
	return result;
}

//�Ƚ�����������Ƿ�Ϊint�� ��������Y ����������N
//����ؼ����ǽ������ָ�����������ʹ���ַ�����
char compare_data(double i)
{
	char *y= "YES";
	char *n = "NO";
	if(abs(i-int(i))<4.45e-308)
	{
		//printf("%s\n",a);
		return *y;
	}
	else
	{
		//printf("%s\n",b);
		return *n;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	double a,result;
	printf("Please input the parameter of 2 pow:\n");
	scanf("%lf",&a);
	printf("%.2lf\n",a);
	result = calculate_pow_2(a);
	printf("result = %d\n",int(result));
	printf("The data input is power of 2 ? %C\n",compare_data(result));
	return 0;
}
//ע����д������������������ı���һ��Ҫ����һ�£�