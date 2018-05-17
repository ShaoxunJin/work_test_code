#include "stdafx.h"
#include "WORKFLOW_EXE.h"

/******************************************************************
1、设备都有自己的hardware类，执行具体的设备动作；
2、每个设备都有自己的interface接口，每个model都会继承这个interface；
3、都会有controller类来封装所有设备的底层接口，类似4T接口，通过这些接口执行单独的功能；
4、最终都会通过model来下发 到interface 到具体的设备执行功能；
******************************************************************/


void WORKFLOW_EXE()
{
#ifdef _WORKFLOW_WR_
	STATION_INTERFACE tt_station_interface;
	tt_station_interface.set_current_slot(10);
	cout<<tt_station_interface.get_current_slot()<<endl;
	tt_station_interface.register_exchange_type(WR4T_EXCHANGE_TYPE_PUT);
	tt_station_interface.register_exchange_type(WR4T_EXCHANGE_TYPE_SWAP_PUT_GET);
	tt_station_interface.register_exchange_type(WR4T_EXCHANGE_TYPE_SWAP_PICKUP);
	tt_station_interface.tt_show_m_exchange_vector();
	tt_station_interface.tt_show_exchange_nbr();
	tt_station_interface.register_station_name(WZ4A_2_INCH, WR4T_ARM_STATION_A);
	tt_station_interface.register_station_name(WZ4A_3_INCH, WR4T_ARM_STATION_B);
	tt_station_interface.register_station_name(WZ4A_4_INCH, WR4T_ARM_STATION_C);

	t_WR4T_ARM_STATION_ENUM_str str_WR4T_ARM_STATION_ENUM;
	cout<<str_WR4T_ARM_STATION_ENUM.to_string(tt_station_interface.get_station_name(WZ4A_2_INCH))<<endl;
	cout<<str_WR4T_ARM_STATION_ENUM.to_string(tt_station_interface.get_station_name(WZ4A_4_INCH))<<endl;

	//station_model_abstract
	t_WRMC_SPEED_LEVEL_ENUM_str str_WRMC_SPEED_LEVEL_ENUM;
	WRMC_STATION_PARAMTER_STRUCT stn_param = WRMC_STATION_PARAMTER_STRUCT();
	stn_param.max_slot = 12;
	stn_param.speed = WRMC_SPEED_LEVEL_9;
	STATION_MODEL_ABSTRACT_INTERFACE *tt_station_model_abstract = new STATION_MODEL_ABSTRACT_INTERFACE();
	tt_station_model_abstract->reset_configuration(stn_param);
	cout<<"tt_station_model_abstract.m_slot = "<<tt_station_model_abstract->get_config_slot()<<endl;
	cout<<"tt_station_model_abstract.get_work_speed = "<<str_WRMC_SPEED_LEVEL_ENUM.to_string(tt_station_model_abstract->get_work_speed())<<endl;
	delete tt_station_model_abstract;
	//tt_station_model_abstract->reset_configuration(stn_param);

	WRMC_ROBOT_STRUCT mc = WRMC_ROBOT_STRUCT();
	mc.info_mode = WRMC_INFO_MODE_1;
	mc.on_line = 1;
	boost::shared_ptr<MACHINE_CONSTANT_CLASS> tt_machine_constance_class(new MACHINE_CONSTANT_CLASS());
	tt_machine_constance_class->print_mc();
	tt_machine_constance_class->set_mc(mc);
	tt_machine_constance_class->print_mc();

	//STATION_CONTROLLER_CLASS
	try
	{
		boost::shared_ptr<STATION_CONTROLLER_CLASS> tt_station_controller_class(new STATION_CONTROLLER_CLASS());
		cout<<"'A' : "<<str_WR4T_ARM_STATION_ENUM.to_string(tt_station_controller_class->convert('A'))<<endl;
		cout<<"'D' : "<<str_WR4T_ARM_STATION_ENUM.to_string(tt_station_controller_class->convert('D'))<<endl;
	}
	catch (WR_PARAMETER_EXCEPTION_CLASS& e)
	{
		cout<<"Catch sucess : "<<e.error_msg()<<endl;
		cout<<"Catch sucess : "<<e.error_code()<<endl;
	}
	
	//WG_STATION
	boost::shared_ptr<WG_STATION_MODEL_CALSS> tt_WG_STATION_MODEL_CALSS_1(new WG_STATION_MODEL_CALSS("WG_1"));
	boost::shared_ptr<WG_STATION_MODEL_CALSS> tt_WG_STATION_MODEL_CALSS_2(new WG_STATION_MODEL_CALSS("WG_2"));
	cout<<tt_WG_STATION_MODEL_CALSS_1->get_wg_station_name()<<endl;
	cout<<tt_WG_STATION_MODEL_CALSS_2->get_wg_station_name()<<endl;
	
	//WR_EXCEPTION_CLASS
	std::exception* std_msg = NULL;
	boost::shared_ptr<WR_EXCEPTION_CLASS> tt_WR_EXCEPTION_CLASS(new WR_EXCEPTION_CLASS(1,2,"error_message", std_msg));
	boost::shared_ptr<WR_SYSTEM_EXCEPTION_CLASS> tt_WR_SYSTEM_EXCEPTION_CLASS(new WR_SYSTEM_EXCEPTION_CLASS("WR_SYSTEM_EXCEPTION_CLASS", std_msg));
	cout<<tt_WR_SYSTEM_EXCEPTION_CLASS->error_code()<<endl;
	cout<<tt_WR_SYSTEM_EXCEPTION_CLASS->link_code()<<endl;
	cout<<tt_WR_SYSTEM_EXCEPTION_CLASS->error_msg()<<endl;

	//下面是采用重载operator<<添加了构造函数中的内容
	//WR_EXCEPTION_CLASS tt(WR_EXCEPTION_CLASS(0,3,"WR_EXCEPTION_CLASS error !", std_msg)<<"__FUNCTION__ : "<<__FUNCTION__<<"xxxxxxxxxxxxxxxxxxxxxxxxxxx");
	//WR_PARAMETER_EXCEPTION_CLASS ttt(WR_PARAMETER_EXCEPTION_CLASS("WR_PARAMETER_EXCEPTION_CLASS", std_msg)<<"__FUNCTION__ : "<<__FUNCTION__<<"xxxxxxxxxxxxxxxxxxxxxxxxxxx");
	//cout<<tt.error_code()<<endl;
	//cout<<tt.link_code()<<endl;
	//cout<<tt.error_msg()<<endl;
	WR_EXCEPTION_CLASS* t = new WR_EXCEPTION_CLASS(0,3,"WR_EXCEPTION_CLASS", std_msg);


	try
	{
		//当自身的类中存在了operator<<则在调用的时候会失败
		//throw boost::enable_error_info(WR_EXCEPTION_CLASS(0,0,"WR_EXCEPTION_CLASS....",NULL)<<__FUNCTION__);
		throw boost::enable_error_info(WR_PARAMETER_EXCEPTION_CLASS("WR_PARAMETER_EXCEPTION_CLASS...",NULL))<<boost::errinfo_errno(123)<<boost::errinfo_api_function("ews");
	}
	catch(WR_PARAMETER_EXCEPTION_CLASS& e)
	{
		cout<<e.error_msg()<<endl;
		cout<<dec<<*boost::get_error_info<boost::errinfo_errno>(e)<<endl;
		cout<<*boost::get_error_info<boost::errinfo_api_function>(e)<<endl;

	}


#endif // _WORKFLOW_WR_

}