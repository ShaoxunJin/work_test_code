// algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "head_file.h"
#include "algorithm.h"
#include "sigma_calculation.h"
#include "coordinate_transform.h"
#include "model_search.h"

//#define _MODEL_SEARCH_
#define __LEAST_SQUARE_

int _tmain(int argc, _TCHAR* argv[])
{
	double matrix_src[9] = {1,2,3,4,5,6,1,90,1};
	
	double *matrix_des = NULL;
	float lowpass_freq = 100.0;
	float sample_period = 0.0004;
	float a_factor_ptr[2] = {0.0,0.0};
	float b_factor_ptr[2] = {0.0,0.0};
	
	RLMATH_1st_lowpass_Z_cov(lowpass_freq,sample_period,a_factor_ptr,b_factor_ptr);
	printf("a[0] = %f,a[1] = %f\n",a_factor_ptr[0],a_factor_ptr[1]);
	printf("b[0] = %.8f,b[1] = %.8f\n",b_factor_ptr[0],b_factor_ptr[1]);
	//Cross_Matrix(matrix_src,3,3,matrix_des);

	SMEE_FLOAT den[2] = {0.0,0.0};
	SMEE_FLOAT num[2] = {0.0,0.0};
	
	RLMATH_1st_notch_Z_cov(10,20,sample,den,num);
	cout<<"num[0] = "<<num[0]<<" num[1] = "<<num[1]<<endl;
	cout<<"den[0] = "<<den[0]<<" den[1] = "<<den[1]<<endl;

	char temp1[10] = "";
	char *temp2 = "ABC";
	//strcpy(temp1,temp2);
	//temp1[] = temp2;'
	cout<<strlen(temp2)+1<<endl;
	memcpy(temp1, temp2, sizeof(char)*strlen(temp2));
	cout<<temp1<<endl;


	double throughput = 0.0;
	std::vector<double> vector_test;
	for(int i = 1; i < 16; ++i)
	{
		cout<<"i = "<<i<<endl;
		vector_test.push_back(i);
	}
	cout<<"3*Sigma = "<<sigma_cal(vector_test)<<endl;
	
	std::vector<double> vector_throughput;
	FILE *FileThrougput = NULL;
	FileThrougput = fopen(".\\throughput.txt","r");
	if(FileThrougput == NULL)
	{
		printf("Open througphput file failed !\n");
	}
	else
	{
		double data_buffer = 0.0;
		while(!feof(FileThrougput))
		{
			fscanf(FileThrougput,"%lf",&data_buffer);
			if(!feof(FileThrougput))
			{
				cout<<data_buffer<<endl;
				vector_throughput.push_back(data_buffer);
			}
			//cout<<"vector_throughput.size() = "<<vector_throughput.size()<<endl;
		}
		throughput = calculate_throuhput(vector_throughput);
	}
	cout<<"throughput = "<<throughput<<endl;

	coordinate_transform();

	cout<<"atan(sqrt(3)) = "<<-atan(sqrt(3.0))/3.1415926*180<<endl;

	double eccentricity_angle = 0.0;
	xy_vect eccentricity_xy = {-1, 1.732};
	PUAC_eccentricity_angle_calculation(eccentricity_xy, &eccentricity_angle);
	cout<<"eccentricity_xy.x = "<<eccentricity_xy.x<<" eccentricity_xy.y = "<<eccentricity_xy.y<<endl;
	cout<<"eccentricity_angle = "<<eccentricity_angle/RL_PI*180<<endl;

#ifdef _MODEL_SEARCH_
	
	xx_vect value = {1.1,2.2};
	cout<<"MODEL_SEARCH_function_value = "<<MODEL_SEARCH_function_value(value)<<endl;

#endif

#ifdef __LEAST_SQUARE_
	
	vector<double> x;
	vector<double> y;

	FILE * pFileLeastSquare = fopen(".\\least_square_sec.dat", "r");

	if (NULL == pFileLeastSquare)
	{
		cout<<"Open file failed !"<<endl;
	}
	else
	{	
		char buf[100] = {};
		char *ptr = NULL;
		//这里是为了获取dat文件前面的字符串，99个加上\0文件的指针自动指向下一行
		//下面只会执行一次
		if(0 != (ptr = fgets(buf,100,pFileLeastSquare)))
		{
			cout<<"buf = "<<buf;
		}
#if 0
		while(0 != (ptr = fgets(buf, 100, pFileLeastSquare)))
		{
			cout<<"buf = "<<buf;
		}
#endif

#if 1
		int i = 0;
		double aa = 0.0, bb = 0.0;
		//while (!feof(pFileLeastSquare))
		//最好采用如下方式
		while(EOF != fscanf(pFileLeastSquare, "%lf\t\%lf\n", &aa,&bb))
		{
			x.push_back(aa);
			y.push_back(bb);
			//cout<<"x["<<i<<"] = "<<x[i]<<", y["<<i<<"] = "<<y[i]<<endl;
			cout<<"aa = "<<aa<<", bb = "<<bb<<endl;
			i++;
		}
#endif
	}

	least_squares_second_order(x, y);

	if (NULL != pFileLeastSquare)
	{
		fclose(pFileLeastSquare);
		pFileLeastSquare = NULL;
	}

#endif
	data_process();
	
	system("pause");
	return 0;
}

