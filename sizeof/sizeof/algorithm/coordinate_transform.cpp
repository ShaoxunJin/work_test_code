#include "stdafx.h"
#include "coordinate_transform.h"

void coordinate_transform()
{
	//定义数组
	xy_vect *src = new xy_vect[10];
	xy_vect *dst = new xy_vect[10];

	FILE *read_file_ptr = NULL;
	read_file_ptr = fopen(coordinate_read_filename,"r");
	if(read_file_ptr == NULL)
	{
		printf("Open file %s failed !", coordinate_read_filename);
		//exit(-1);
	}
	else
	{
		while(!feof(read_file_ptr))
		{
			int i = 0;
			i = fscanf(read_file_ptr,"%lf %lf",&(src->x), &(src->y));
			if(i != EOF)
			{
				transform_calculate(30, *src, dst);
				cout<<src->x<<" "<<src->y<<" "<<dst->x<<" "<<dst->y<<endl; 
			}
		}
	}

	fclose(read_file_ptr);
	read_file_ptr = NULL;

	delete[] src;
}

void transform_calculate(double angle, xy_vect src, xy_vect* dst)
{
	double angle_rad = angle/180*3.1415926;
	
	dst->x = src.x * cos(angle_rad) + src.y * sin(angle_rad);
	dst->y = src.y * cos(angle_rad) - src.x * sin(angle_rad);
}

void PUAC_eccentricity_angle_calculation(xy_vect eccentricity_xy,
										 SMEE_DOUBLE *eccentricity_angle)
{
	double angle = 0.0;
	//
	angle = atan(eccentricity_xy.y / eccentricity_xy.x);
	//逆时针 R正
	if(angle > 0)
	{
		*eccentricity_angle = RL_PI/2.0 - angle;
	}
	else
	{
		*eccentricity_angle = -(RL_PI/2.0 + angle);
	}

}
