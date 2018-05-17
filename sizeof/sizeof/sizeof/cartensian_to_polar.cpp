#include "stdafx.h"
#include "cartensian_to_polar.h"

polar_cs_struct cartensian_to_polar(cartensian_cs_struct xy_cartensian_cs)
{
	ostringstream os("");
	os<<"Cartensian_to_polar calculation start...."<<endl<<endl;
	cout<<os.str();
	polar_cs_struct r_theta_cs = polar_cs_struct();

	r_theta_cs.r = 0;
	r_theta_cs.theta = 0;
	
	os.str("");
	os<<"Cartensian_to_polar calculation end ...."<<endl<<endl;
	cout<<os.str();
	return r_theta_cs;
}