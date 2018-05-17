#ifndef SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS_H_
#define SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS_H_

//#include "WU4A_tc.h"
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "smee.h"
#include "smee_station.h"
#include "smee_type.h"
#include "smee_unit.h"

namespace _WU
{	/**
	* @stereotype interface 
	* @priority medium
	* @difficulty medium
	* @description
	* @number,expansion 
	* @type Product Requirement
	* @document F:\workflow\prj\205C-WU.tpr
	* @author sunww*/
	template<typename T1,typename T2>
	class SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS
	{
	public:
		//************************************
		// Method:    SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS
		// FullName:  _WU::class<MATERIAL_TYPE>::SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS(/*std::string subset_name*/);

		virtual ~SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS();
		virtual void set_material_size(T1* size) = 0;	
		virtual T1* get_material_size() const = 0;
		virtual SMEE_BOOL* is_interfered() = 0;
		virtual int interference_handle() = 0;
		virtual SMEE_BOOL* is_initialized() = 0;
		virtual int initialize() = 0;
		virtual SMEE_BOOL* is_do_switch() = 0;
		virtual int switch_station() = 0;
		virtual SMEE_BOOL* is_material_present() = 0;
		virtual void set_station_list(std::map<T2,std::list<void*> >* station) = 0;
		virtual std::map<T2,std::list<void*> >* get_station_list() =0;
	private:
			////std::string m_subset_name;
			//MATERIAL_TYPE m_size;
			//std::map<AXIS_ENUM,std::list<int*>> m_station;
			//SMEE_BOOL m_material_present;
			//SMEE_BOOL m_do_switch;
			//SMEE_BOOL m_initialized;
	};

	template<typename T1,typename T2>
	SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS<T1, T2>::~SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS()
	{

	}

	template<typename T1,typename T2>
	SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS<T1, T2>::SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS( /*std::string subset_name*/ )
	{

	}
}
#endif // SUBSYSTEM_INITIALIZE_ABSTRACT_CLASS_H_