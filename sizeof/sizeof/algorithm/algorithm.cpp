#include "stdafx.h"
#include "algorithm.h"
#include "sigma_calculation.h"


void Cross_Matrix(double* Matrix_Src, int src_width, int src_height, double* Matrix_Dst)
{
	int rtn = OK;
	int i, j, k, m, n;
	double temp, scale;
	double data_up = 0.0;
	double data_down = 0.0;

	if(src_width != src_height)
	{
		printf("this matrix isn't a square matrix! \n");
		//rtn = PUAPCA_PARAMETER_ERROR;
	}
	else
	{
		for(i=0; i<src_height; i++)
		{
			k = i;
			data_up = Matrix_Src[i * src_width + i];
			data_down = Matrix_Src[i * src_width + i];
			while((data_down) == 0 && (k + 1) < src_height)
			{
				k++;
				data_down = Matrix_Src[k * src_width + i];
			}
			if(k == i)
			{
				for(m=i+1; m<src_height; m++)
				{
					scale = Matrix_Src[m * src_width + i] / Matrix_Src[i * src_width + i];
					for(n=i; n<src_width; n++)
					{
						Matrix_Src[m * src_width + n] = Matrix_Src[m * src_width + n] - (scale * Matrix_Src[i * src_width + n]);
					}
				}
			}
			else
			{
				for(j=i; j<src_width; j++)
				{
					temp = Matrix_Src[i * src_width + j];
					Matrix_Src[i * src_width + j] = Matrix_Src[k * src_width + j];
					Matrix_Src[k * src_width + j] = temp;
				}
				for(m=i+1; m<src_height; m++)
				{
					scale = Matrix_Src[m * src_width + i] / Matrix_Src[i * src_width + i];
					for(n=i; n<src_width; n++)
					{
						Matrix_Src[m * src_width + n] = Matrix_Src[m * src_width + n] - (scale * Matrix_Src[i * src_width + n]);
					}
				}
			}
		}

		for(i=src_height-1; i>=0; i--)//~{8_K9O{T*:s;X4z5D9}3L~}
		{
			k = i;
			data_up = Matrix_Src[i * src_width + i];
			data_down = Matrix_Src[i * src_width + i];
			while((data_down) == 0 && (k - 1) >= 0)
			{
				k--;
				data_down = Matrix_Src[k * src_width + i];
			}
			if(k == i)
			{
				for(m=i-1; m>=0; m--)
				{
					scale = Matrix_Src[m * src_width + i] / Matrix_Src[i * src_width + i];
					for(n=i; n<src_width; n++)
					{
						Matrix_Src[m * src_width + n] = Matrix_Src[m * src_width + n] - (scale * Matrix_Src[i * src_width + n]);
					}
				}
			}
			else
			{
				for(j=i; j>=0; j--)
				{
					temp = Matrix_Src[i * src_width + j];
					Matrix_Src[i * src_width + j] = Matrix_Src[k * src_width + j];
					Matrix_Src[k * src_width + j] = temp;
				}
				for(m=i-1; m>=0; m--)
				{
					scale = Matrix_Src[m * src_width + i] / Matrix_Src[i * src_width + i];
					for(n=i; n<src_width; n++)
					{
						Matrix_Src[m * src_width + n] = Matrix_Src[m * src_width + n] - (scale * Matrix_Src[i * src_width + n]);
					}
				}
			}
		}

		printf("The result of Cross_Matrix! \n");
		for(i=0; i<src_height; i++)
		{
			for(j=0; j<src_width; j++)
			{
				if(i == j)
				{
					printf("   %f     ", Matrix_Dst[i * src_width + j]);
				}
				else
				{
					printf("   %f     ", 0);
				}
				if(j == src_width - 1)
				{
					printf("\n  \n  \n");
				}
			}
		}
	}

	//return rtn;
}



void RLMATH_1st_lowpass_Z_cov(float lowpass_freq,
                                    float sample_period,
                                    float* a_factor_ptr,
                                    float* b_factor_ptr )
{
    double EA1 = 0.;
    float wlwp = 0.;

    /////1st_order low pass filter disperse factors
	wlwp = 2*RL_PI*lowpass_freq;
	EA1 = exp(-wlwp*sample_period);

	/*pole*/
	*(a_factor_ptr + 0) = 1.;
	*(a_factor_ptr + 1) = (float)(-EA1);

	/*zero*/
	*(b_factor_ptr + 0) = (float)(1-EA1)/2.;
	*(b_factor_ptr + 1) = (float)(1-EA1)/2.;

	return ;
}


void RLMATH_1st_notch_Z_cov(SMEE_FLOAT zero_freq,
							SMEE_FLOAT pole_freq,
							SMEE_FLOAT sample_period,
							SMEE_FLOAT* a_factor_ptr,
							SMEE_FLOAT* b_factor_ptr)
{
	SMEE_DOUBLE EA1 = 0.;
	SMEE_DOUBLE EB1 = 0.;
	SMEE_FLOAT wzero = 0.;
	SMEE_FLOAT wpole = 0.;
	SMEE_DOUBLE Kpole = 0.;
	SMEE_DOUBLE Kzero = 0.;

	/////1st_order notch filter disperse factors
	wzero = 2*RL_PI*zero_freq;
	EB1 = exp(-wzero*sample_period);
	wpole = 2*RL_PI*pole_freq;
	EA1 = exp(-wpole*sample_period);

	/*pole*/
	*(a_factor_ptr + 0) = 1.;
	*(a_factor_ptr + 1) = (SMEE_FLOAT)(-EA1);

	/*zero*/
	*(b_factor_ptr + 0) = 1.;
	*(b_factor_ptr + 1) = (SMEE_FLOAT)(-EB1);

	Kpole = *(a_factor_ptr + 0) + (*(a_factor_ptr + 1)) ;
	Kzero = *(b_factor_ptr + 0) + (*(b_factor_ptr + 1)) ;

	if(fabs(Kzero)<zero_line)
	{
		*(b_factor_ptr + 0) = 1.;
		*(b_factor_ptr + 1) = 0;
	}
	else
	{
		*(b_factor_ptr + 0) = Kpole/Kzero * (*(b_factor_ptr + 0));
		*(b_factor_ptr + 1) = Kpole/Kzero * (*(b_factor_ptr + 1));
	}

	return ;
}


void least_squares(int nbr)
{
	double *x = new double[21];
	double *y = new double[21];
	//double *new_double = new double[100];
	//cout<<"new_double = "<<*new_double<<endl;

	FILE * pFileLeastSquare = fopen(".\\least_square.dat", "r");
	
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
		double a = 0.0, b = 0.0;
		//while (!feof(pFileLeastSquare))
		//最好采用如下方式
		while(EOF != fscanf(pFileLeastSquare, "%lf\t\%lf\n", &x[i],&y[i]))
		{

			//fscanf(pFileLeastSquare, "%lf\t\%lf", x,y);
			//cout<<"x[i] : "<<x[i]<<endl;
			cout<<"x["<<i<<"] = "<<x[i]<<", y["<<i<<"] = "<<y[i]<<endl;
			//x++;
			//y++;
			i++;
		}
#endif

	}
	
	double sxy = 0.0, sx = 0.0, sy = 0.0, sxx = 0.0;
	double a = 0.0, b = 0.0;//a是斜率，b是截距

	for (int j = 0; j < nbr; ++j)
	{
		sx += x[j];
		sy += y[j];
		sxx += x[j] * x[j];
		sxy += x[j] * y[j];
	}

	a = (nbr * sxy - sx * sy)/(nbr * sxx - sx * sx);
	b = sy/nbr - a * sx/nbr;
	cout<<"a = "<<a<<endl;
	cout<<"b = "<<b<<endl;

	if (NULL != x)
	{
		delete []x;
		x = NULL;
	}

	if (NULL != y)
	{
		delete []y;
		y = NULL;
	}

	if (NULL != pFileLeastSquare)
	{
		fclose(pFileLeastSquare);
		pFileLeastSquare = NULL;
	}
}


void least_squares_second_order(vector<double> x, vector<double> y)
{
	//double *x = new double[nbr];
	//double *y = new double[nbr];
	//double *new_double = new double[100];
	//cout<<"new_double = "<<*new_double<<endl;

//	vector<double> x;
//	vector<double> y;
//
//	FILE * pFileLeastSquare = fopen(".\\least_square_sec.dat", "r");
//
//	if (NULL == pFileLeastSquare)
//	{
//		cout<<"Open file failed !"<<endl;
//	}
//	else
//	{	
//		char buf[100] = {};
//		char *ptr = NULL;
//		//这里是为了获取dat文件前面的字符串，99个加上\0文件的指针自动指向下一行
//		//下面只会执行一次
//		if(0 != (ptr = fgets(buf,100,pFileLeastSquare)))
//		{
//			cout<<"buf = "<<buf;
//		}
//#if 0
//		while(0 != (ptr = fgets(buf, 100, pFileLeastSquare)))
//		{
//			cout<<"buf = "<<buf;
//		}
//#endif
//
//#if 1
//		int i = 0;
//		double aa = 0.0, bb = 0.0;
//		//while (!feof(pFileLeastSquare))
//		//最好采用如下方式
//		while(EOF != fscanf(pFileLeastSquare, "%lf\t\%lf\n", &aa,&bb))
//		{
//			x.push_back(aa);
//			y.push_back(bb);
//			//cout<<"x["<<i<<"] = "<<x[i]<<", y["<<i<<"] = "<<y[i]<<endl;
//			cout<<"aa = "<<aa<<", bb = "<<bb<<endl;
//			i++;
//		}
//#endif
//	}

	double sx = 0.0,sxx = 0.0,sxxx = 0.0,sxxxx = 0.0;
	double sy = 0.0,syx = 0.0,syxx = 0.0;
	int nbr = x.size();
	for (int j = 0; j < x.size(); ++j)
	{
		sx += x[j];
		sxx += x[j] * x[j]; 
		sxxx += x[j] * x[j] * x[j];
		sxxxx += x[j] * x[j] * x[j] * x[j];
		sy += y[j];
		syx += y[j] * x[j];
		syxx += y[j] * x[j] * x[j];
	}

	/*
	原始计算方式
	double A1 = sxxxx,A2 = sxxx,A3 = sxx;
	double B1 = sxxx, B2 = sxx, B3 = sx;
	double C1 = sxx, C2 = sx, C3 = nbr;
	double a = syxx, b = syx, c = sy;
	para[0] = ((B2*C1-B1*C2)*(c*C1-a*C3)-(B3*C1-B1*C3)*(b*C1-a*C2))/((A3*C1-A1*C3)*(B2*C1-B1*C2) - (B3*C1-B1*C3)*(A2*C1-A1*C2));
	para[1] = ((A3*C1-A1*C3)*(b*C1-a*C2)-(A2*C1-A1*C2)*(c*C1-a*C3))/((A3*C1-A1*C3)*(B2*C1-B1*C2) - (B3*C1-B1*C3)*(A2*C1-A1*C2));
	para[2] = (a-A1*para[0]-B1*para[1])/C1;
	*/
	double A = sxx * sxx - sxxxx * nbr;
	double B = sxx * sxx - sxxx * sx;
	double C = sx * sxx - sxxx * nbr;
	double D = sxxx * sxx - sxxxx * sx;
	double E = sy * sxx - syxx * nbr;
	double F = syx * sxx - syxx * sx;
	double para[3] = {0.0};
	para[0] = (B*E-C*F)/(A*B-C*D);
	para[1] = (A*F-D*E)/(A*B-C*D);
	para[2] = (syxx - sxxxx*para[0] - sxxx * para[1])/sxx;

	cout<<"para[0] = "<<para[0]<<endl;
	cout<<"para[1] = "<<para[1]<<endl;
	cout<<"para[2] = "<<para[2]<<endl;

	/*A1 = nbr * sxxxx- sxx * sxx;
	A2 = nbr * sxxx - sx * sxx;
	B1 = nbr * sxxx - sxx * sxx;
	B2 = nbr * sxx - sx * sx;
	C1 = nbr * syxx - sxx * sy;
	C2 = nbr * syx - sx * sy;
	a = (B1*C2 - B2*C1)/(A2*B1 - A1*B2);
	b = (A2*C1 - A1*C2)/(A2*B1 - A1*B2);
	c = (sy - a * sxx - b * sx)/nbr;*/

	//printf("a = %f\n", a);
	//printf("b = %f\n", b);
	//printf("c = %f\n", c);

	//if (NULL != x)
	//{
	//	delete []x;
	//	x = NULL;
	//}

	//if (NULL != y)
	//{
	//	delete []y;
	//	y = NULL;
	//}

	//if (NULL != pFileLeastSquare)
	//{
	//	fclose(pFileLeastSquare);
	//	pFileLeastSquare = NULL;
	//}
}


double max_data(double buffer[],int nbr,int *max_index)
{
	double max = buffer[0];
	for(int i = 0;i <= nbr;i++)
	{
		if(max <= buffer[i])
		{
			max = buffer[i];
			*max_index = i;
		}
	}
	return max;
}

double min_data(double buffer[],int nbr,int *min_index)
{
	double min = buffer[0];
	for(int i = 0;i <= nbr;i++)
	{
		if(min >= buffer[i])
		{
			min = buffer[i];
			*min_index = i;
		}
	}
	return min;
}
double avr_data(double buffer[],int nbr)
{
	double sum = 0.0;
	for(int i = 0;i <= nbr;i++)
	{
		sum += buffer[i];
	}
	if(0 == nbr)
	{
		sum = buffer[0];
	}
	else
	{
		sum = sum/(nbr + 1);
	}

	return sum;
}
double cur_data(double buffer[],int nbr)
{
	double threshold_coefficient = 2;
	double max = 0.0;
	double min = 0.0;
	double average = 0.0;

	int max_index = 0;
	int min_index = 0;
	double current = 0.0;
	max = max_data(buffer,nbr,&max_index);
	min = min_data(buffer,nbr,&min_index);
	if(0 != nbr)
	{
		average = avr_data(buffer,nbr-1);
		if(nbr == max_index)
		{
			if(fabs(max - average) > threshold_coefficient)// * 1.0e-6)
			{
				buffer[nbr] = average + 1.5;// * 1.0e-6;
				//buffer[nbr] = average;
			}
		}
		if(nbr == min_index)
		{
			if(fabs(min - average) > threshold_coefficient)// * 1.0e-6)
			{
				buffer[nbr] = average - 1.5;// * 1.0e-6;
				//buffer[nbr] = average;
			}
		}
	}
	current = buffer[nbr];
	return current;
}


void data_process()
{
	FILE *file_data_process = NULL;
	FILE *file_data_result = NULL;
	std::vector<double> vecInput;
	std::vector<double> vecProcess;
	double sigma_input = 0.0;
	double sigma_process = 0.0;
	double process_data = 0.0;

	file_data_process = fopen(".\\load_repeat.txt","r");
	file_data_result = fopen(".\\result.txt","w+");
	if(NULL == file_data_process || NULL == file_data_result)
	{
		printf("Open file failed !\n");
	}
	else
	{
		double data_buffer[20] = {0.0};
		int i = 0;
		while(!feof(file_data_process))
		{
			fscanf(file_data_process,"%lf",&data_buffer[i]);
			cout<<"i = "<<i + 1<<", "<<data_buffer[i]<<endl;
			vecInput.push_back(data_buffer[i]);
			if (i >= 1)
			{
				sigma_input = sigma_cal(vecInput);
			}
			cout<<"Input number : "<<i + 1<<", original_data = "<<data_buffer[i]<<", sigma_input = "<<sigma_input<<endl;

			process_data = cur_data(data_buffer, i);
			fprintf(file_data_result, "%lf\n", process_data);
			vecProcess.push_back(process_data);
			if (i >= 1)
			{
				sigma_process = sigma_cal(vecProcess);
			}
			cout<<"Process number : "<<i + 1<<", process_data = "<<process_data<<", sigma_process = "<<sigma_process<<endl;

			if(!feof(file_data_process))
			{
				//cout<<"i = "<<i++<<", "<<data_buffer<<endl;
				//vector_throughput.push_back(data_buffer);
			}
			++i;			
			//cout<<"vector_throughput.size() = "<<vector_throughput.size()<<endl;
		}
		//throughput = calculate_throuhput(vector_throughput);
	}
}