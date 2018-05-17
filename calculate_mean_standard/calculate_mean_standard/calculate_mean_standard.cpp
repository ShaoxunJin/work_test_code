// calculate the mean value and standard value
//

#include "stdafx.h"
#include <math.h>

double mean_calc(double *data)
{
	int i_number = sizeof(data);
	int i;
	double mean_value;
	double sum_number = 0.0;
	for(i = 0; i<i_number; i++)
	{
		sum_number += data[i];
	}
	mean_value = sum_number/i_number;
	return mean_value;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double input_data[2] = {};
	int j = sizeof(input_data)/sizeof(double);
	int i;
	printf("Please input the data array:\n");
	for(i = 0; i<j;i++)
	{
		scanf("%lf",&input_data[i]);
	}
	for(i = 0; i<j;i++)
	printf("data is %lf\n",input_data[i]);
	printf("mean_data is %lf\n",mean_calc(input_data));
	return 0;
}
