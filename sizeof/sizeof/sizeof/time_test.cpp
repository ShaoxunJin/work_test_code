#include "stdafx.h"
#include "time_test.h"
void time_test()
{

	printf("Time_Test Begin>>>>>>>");
	time_t current_time;
	time(&current_time);
	cout<<"Current_time = "<<current_time<<endl;

	cout<<__DATE__<<" "<<__TIME__<<endl;
	//cout<<"current_time"<<current_time<<endl;

	//
	tm *tm_current_time;
	tm_current_time = localtime(&current_time);
	cout<<"Current time :"<<asctime(tm_current_time)<<endl;
	cout<<"current_month : "<<tm_current_time->tm_mon<<endl;

	cout<<"Time_Test End<<<<<<<<"<<endl;

}

double time_calculation(int m)
{
	double total_time = 0.0;
	clock_t start_time = 0,stop_time = 0;
	start_time = clock();
	cout<<"start_time :"<<start_time<<endl;

	for(int i = 0; i < m ; ++i)
	{
		double circle = 3.14152546546 * i;
	}
	stop_time = clock();
	cout<<"stop_time :"<<stop_time<<endl;
	total_time = (double)(stop_time - start_time)/CLOCKS_PER_SEC;
	return total_time;
}