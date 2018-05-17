#include "stdafx.h"
#include "sigma_calculation.h"

double sigma_cal(vector<double> &dVector)
{
	if(dVector.empty())
	{
		printf("This vector is null\n");
		exit(-1);
	}
	double value_mean = 0.0;
	double value_sum = 0.0;
	double value_sum_sqrt = 0.0;
	double sigma_3 = 0.0;
	int nbr = dVector.size();

	std::vector<double>::iterator iter;
	for(iter = dVector.begin(); iter != dVector.end(); ++iter)
	{
		value_sum += *iter;
	}
	value_mean = value_sum/nbr;
	
	for(iter = dVector.begin(); iter != dVector.end(); ++iter)
	{
		value_sum_sqrt += (*iter - value_mean) * (*iter - value_mean);
	}

	sigma_3 =  3 * sqrt(value_sum_sqrt/(nbr - 1));
	
	return sigma_3;
}

double calculate_throuhput(std::vector<double> &dVector)
{
	double value_sum = 0.0;
	double value_mean = 0.0;
	double value_throughput = 0.0;
	int nbr = dVector.size();
	
	std::cout<<"nbr = "<<nbr<<endl;
	std::vector<double>::iterator iter;
	int i = 1;
	for(iter = dVector.begin(); iter != dVector.end(); ++iter)
	{
		if(i <= 3 || (nbr - i) < 3)
		{

		}
		else
		{
			value_sum += *iter;
		}
		++i;
		cout<<" value_sum =   "<<value_sum<<endl;
	}
	value_mean = value_sum/(nbr - 6);
	value_throughput = 3600/value_mean;

	return value_throughput;
}