#include "stdafx.h"
#include "memory_operation.h"

void memcpy_test()
{	
	//整形数组操作
	int iArraySrc[5] = {0,1,2,3,4};
	int iArrayDest[5] = {};
	for (int i = 0; i < 5; ++i)
	{
		cout<<"iArraySrc["<<i<<"] = "<<iArraySrc[i]<<endl;
	}
	for (int i = 0; i < 5; ++i)
	{
		cout<<"iArrayDest["<<i<<"] = "<<iArrayDest[i]<<endl;
	}
	//cout<<"sizeof = "<<sizeof(iArrayDest)<<endl;
	cout<<"After memcpy operation:"<<endl;
	memcpy((void *)iArrayDest, (void *)iArraySrc, sizeof(iArrayDest));
	for (int i = 0; i < 5; ++i)
	{
		cout<<"iArraySrc["<<i<<"] = "<<iArraySrc[i]<<endl;
	} 
	for (int i = 0; i < 5; ++i)
	{
		cout<<"iArrayDest["<<i<<"] = "<<iArrayDest[i]<<endl;
	}	
	//字符数组操作

	return;
}

void memset_test()
{
	
	int iArrayDest[5] = {0,1,2,3,4};
	for (int i = 0; i < 5; ++i)
	{
		cout<<"iArrayDest["<<i<<"] = "<<iArrayDest[i]<<endl;
	}
	cout<<"After memset operation:"<<endl;
	memset(iArrayDest, 0, sizeof(iArrayDest));

	for (int i = 0; i < 5; ++i)
	{
 		cout<<"iArrayDest["<<i<<"] = "<<iArrayDest[i]<<endl;
		//cout<<(iArrayDest[i]&0x000000ff)<<endl;
	}
	//这里针对单个字节，单个字节的最高位是符号位，实际的计算机存储根据取反加1原则进行
	//但是最终输出的时候还是按照int类型四个字节输出 因此单个字节输出不带符号；
	int a = 0xffffffff;
	cout<<"Ox02020202 = "<<a<<endl;
	int b = 0xfefefefe;
	cout<<"0xfefefefe = "<<b<<endl;
	return;
}

void memset_struct_test(MEMSET_STRUCT *memset_struct)
{
	*memset_struct = MEMSET_STRUCT();
	cout<<"Struct before memset : iStruct ="<<memset_struct->iStruct<<endl;
	cout<<"Struct before memset : dStruct ="<<memset_struct->dStruct<<endl;

	memset((void *)(memset_struct), 0, sizeof(MEMSET_STRUCT));
	cout<<"Struct after memset : iStruct ="<<memset_struct->iStruct<<endl;
	cout<<"Struct after memset : dStruct ="<<memset_struct->dStruct<<endl;
}

void memcpy_for_struct()
{
	WR4T_HOME_LIMIT_STRUCT sWR4T_home_limit_status = WR4T_HOME_LIMIT_STRUCT();
	HW4T_WR_HOME_LIMIT_STRUCT sHW4T_home_limit_status = HW4T_WR_HOME_LIMIT_STRUCT();
	sWR4T_home_limit_status.home_actived = true;
	sWR4T_home_limit_status.forward_actived = false;
	sWR4T_home_limit_status.reserve_actived = true;
	cout<<"sWR4T_home_limit_status.home_actived = "<<sWR4T_home_limit_status.home_actived<<endl;
	cout<<"sWR4T_home_limit_status.forward_actived = "<<sWR4T_home_limit_status.forward_actived<<endl;
	cout<<"sWR4T_home_limit_status.reserve_actived = "<<sWR4T_home_limit_status.reserve_actived<<endl;
	cout<<"sHW4T_home_limit_status.home_actived = "<<sHW4T_home_limit_status.home_actived<<endl;
	cout<<"sHW4T_home_limit_status.forward_actived = "<<sHW4T_home_limit_status.forward_actived<<endl;
	cout<<"sHW4T_home_limit_status.reserve_actived = "<<sHW4T_home_limit_status.reserve_actived<<endl;


	cout<<"After memcpy..."<<endl;
	memcpy((void*)&sHW4T_home_limit_status,(void*)&sWR4T_home_limit_status,sizeof(WR4T_HOME_LIMIT_STRUCT));
	cout<<"sHW4T_home_limit_status.home_actived = "<<sHW4T_home_limit_status.home_actived<<endl;
	cout<<"sHW4T_home_limit_status.forward_actived = "<<sHW4T_home_limit_status.forward_actived<<endl;
	cout<<"sHW4T_home_limit_status.reserve_actived = "<<sHW4T_home_limit_status.reserve_actived<<endl;

}