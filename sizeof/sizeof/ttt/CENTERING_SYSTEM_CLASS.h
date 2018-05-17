#ifndef CENTERING_SYSTEM_CLASS_H_
#define CENTERING_SYSTEM_CLASS_H_
#include <iostream>
#include <string>
#include <map>
#include <list>

#include "SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS.h"
namespace _WU
{

	template<typename M_TYPE,typename A_ENUM>
	class CENTERING_SYSTEM_CLASS:virtual public SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS<M_TYPE,A_ENUM>
	{
	public:

		CENTERING_SYSTEM_CLASS(std::string subset_name);
		virtual ~CENTERING_SYSTEM_CLASS();
		virtual void set_material_size(M_TYPE* size);
		virtual M_TYPE* get_material_size() const;
		virtual SMEE_BOOL* is_interfered();
		virtual int interference_handle();
		virtual SMEE_BOOL* is_initialized();
		virtual int initialize();
		virtual SMEE_BOOL* is_do_switch();
		virtual int switch_station();
		virtual SMEE_BOOL* is_material_present();
		virtual void set_station_list(std::map<A_ENUM,std::list<void*> >* station);
		virtual std::map<A_ENUM,std::list<void*> >* get_station_list();
		std::string get_name() const;

	private:
		std::string m_subset_name;
		M_TYPE* m_size;
		std::map<A_ENUM,std::list<void*> >* m_station;
		SMEE_BOOL m_material_present;
		SMEE_BOOL m_do_switch;
		SMEE_BOOL m_initialized;
		SMEE_BOOL m_is_interfered;

	};



	//template<typename M_TYPE,typename A_ENUM>
	//CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::CENTERING_SYSTEM_CLASS( std::string subset_name )
	//{
	//	this->m_size = new M_TYPE;
	//	this->m_station = new std::map<A_ENUM,std::list<void*> >;
	//	this->m_subset_name = subset_name;
	//	this->m_material_present = false;
	//	this->m_do_switch = false;
	//	this->m_initialized = false;
	//	this->m_is_interfered = false;

	//}

	//template<typename M_TYPE,typename A_ENUM>
	//CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::~CENTERING_SYSTEM_CLASS()
	//{

	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//std::map<A_ENUM,std::list<void*>>* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_station_list()
	//{
	//	return this->m_station;

	//}

	//template<typename M_TYPE,typename A_ENUM>
	//void CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::set_station_list( std::map<A_ENUM,std::list<void*>>* station )
	//{
	//	this->m_station = station;
	//}

	//template<typename M_TYPE,typename A_ENUM>
	//SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_material_present()
	//{
	//	return &this->m_material_present;
	//}

	//template<typename M_TYPE,typename A_ENUM>
	//int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::switch_station()
	//{
	//	int error_code = 0;
	//	return error_code;

	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_do_switch()
	//{
	//	return &this->m_do_switch;
	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::initialize()
	//{
	//	int error_code = 0;
	//	return error_code;
	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_initialized()
	//{
	//	return &this->m_initialized;
	//}

	//template<typename M_TYPE,typename A_ENUM>
	//int CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::interference_handle()
	//{
	//	int error_code = 0;
	//	return error_code;	
	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//SMEE_BOOL* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::is_interfered()
	//{
	//	return &this->m_is_interfered;
	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//M_TYPE* CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_material_size() const
	//{
	//	return this->m_size;
	//}
	//
	//template<typename M_TYPE,typename A_ENUM>
	//void CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::set_material_size( M_TYPE* size )
	//{
	//	this->m_size = size;
	//}

	//template<typename M_TYPE,typename A_ENUM>
	//std::string CENTERING_SYSTEM_CLASS<M_TYPE, A_ENUM>::get_name() const
	//{
	//	return this->m_subset_name;
	//}

}

#endif // CENTERING_SYSTEM_CLASS_H_