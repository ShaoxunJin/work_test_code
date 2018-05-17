#ifndef EXCHANGE_CLASS_H
#define EXCHANGE_CLASS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <utility>
#include "smee.h"
#include "smee_station.h"
#include "smee_type.h"
#include "smee_unit.h"

namespace _WU
{
	typedef enum
	{
		EXCHANGE_MODE_MIN,
		EXCHANGE_MODE_PICKUP,
		EXCHANGE_MODE_PUT_GET,
		EXCHANGE_MODE_SWAP,
		EXCHANGE_MODE_MAX
	}EXCHANGE_MODE_ENUM;

	class EXCHANGE_ABSTRACT_STEP
	{
	public:
		EXCHANGE_ABSTRACT_STEP(std::string name = "EXCHANGE_STEP")
		{
			m_name = name;
		}
		virtual ~EXCHANGE_ABSTRACT_STEP() ;
		virtual int step()=0;
		virtual SMEE_BOOL can_process()=0;
		virtual std::string & name() =0;
	private:
		std::string m_name;
	};
	EXCHANGE_ABSTRACT_STEP::~EXCHANGE_ABSTRACT_STEP()
	{

	}

	class EXCHANGE_STEP_ONE:virtual public EXCHANGE_ABSTRACT_STEP
	{
	public:
		EXCHANGE_STEP_ONE(std::string name);
		virtual ~EXCHANGE_STEP_ONE();
		virtual int step();
		virtual SMEE_BOOL can_process();
		virtual std::string & name()
		{
			return this->m_name;
		}
	private:
		std::string m_name;
	};
	SMEE_BOOL EXCHANGE_STEP_ONE::can_process()
	{
		return true;
	}
	int EXCHANGE_STEP_ONE::step()
	{
		std::cout<<"done\n"<<std::endl;
		return 0;
	}
	EXCHANGE_STEP_ONE::~EXCHANGE_STEP_ONE()
	{

	}
	EXCHANGE_STEP_ONE::EXCHANGE_STEP_ONE(std::string name):m_name(name)
	{

	}

	class EXCHANGE_STEP_TWO:virtual public EXCHANGE_ABSTRACT_STEP
	{
	public:
		EXCHANGE_STEP_TWO(std::string name);
		virtual ~EXCHANGE_STEP_TWO();
		virtual int step();
		virtual SMEE_BOOL can_process();
		virtual std::string & name()
		{
			return this->m_name;
		}
	private:
		std::string m_name;
	};
	SMEE_BOOL EXCHANGE_STEP_TWO::can_process()
	{
		return true;
	}
	int EXCHANGE_STEP_TWO::step()
	{
		std::cout<<"done\n"<<std::endl;
		return 0;
	}
	EXCHANGE_STEP_TWO::~EXCHANGE_STEP_TWO()
	{

	}
	EXCHANGE_STEP_TWO::EXCHANGE_STEP_TWO(std::string name):m_name(name)
	{

	}


	class EXCHANGE_CLASS
	{
	public:
		EXCHANGE_CLASS();
		virtual ~EXCHANGE_CLASS();
		int prepare_exchange(IN EXCHANGE_MODE_ENUM mode);
		SMEE_BOOL handle_exchange();
		int post_exchange();

		int get_current_step();
		int get_next_step();
		//int set_next_step(std::list<EXCHANGE_ABSTRACT_STEP> sequence);
		void set_exchange_sequence(std::list<EXCHANGE_ABSTRACT_STEP*> sequence);
		int get_sequence_size()
		{
			return m_sequence.size();
		}
		const char* WRenum2str(const EXCHANGE_MODE_ENUM &t);

	private:
		std::list<EXCHANGE_ABSTRACT_STEP*> m_sequence;
		//std::list<EXCHANGE_ABSTRACT_STEP*> m_sequence_pick;
		//std::list<EXCHANGE_ABSTRACT_STEP*> m_sequence_put;
		//std::list<EXCHANGE_ABSTRACT_STEP*> m_sequence_swap;
		EXCHANGE_STEP_ONE *m_step_one;
		EXCHANGE_STEP_TWO *m_step_two;
		EXCHANGE_MODE_ENUM m_mode;
		std::map<EXCHANGE_MODE_ENUM,std::list<EXCHANGE_ABSTRACT_STEP*>> m_mode_sequence;

	};
	
	const char* EXCHANGE_CLASS::WRenum2str(const EXCHANGE_MODE_ENUM &t)
	{
		char *str = NULL;
		switch(t)
		{
		case EXCHANGE_MODE_PICKUP:
			str = "Pickup";
			break;

		case EXCHANGE_MODE_SWAP:
			str = "Swap";
			break;

		case EXCHANGE_MODE_PUT_GET:
			str = "PUT_GET";
			break;

		default:
			str = "INVALID_MODE_ENUM";
			break;

		}

		return str;
	}

	EXCHANGE_CLASS::EXCHANGE_CLASS()
	{

	}
	void EXCHANGE_CLASS::set_exchange_sequence(std::list<EXCHANGE_ABSTRACT_STEP*> sequence)
	{
		this->m_sequence = sequence;

	}
	int EXCHANGE_CLASS::prepare_exchange(IN EXCHANGE_MODE_ENUM mode)
	{
		m_mode = mode;
		std::cout<<"prepare_exchange:\nm_mode :"<<WRenum2str(m_mode)<<std::endl;
		try
		{
			if (m_mode <= EXCHANGE_MODE_MIN || m_mode >= EXCHANGE_MODE_MAX)
			{
				throw "illegal EXCHANGE_MODE_ENUM";
			}
		}
		catch (const char* e)
		{
			std::cout<< e <<std::endl;
		}

		m_step_one = new EXCHANGE_STEP_ONE("move to top");
		m_step_two = new EXCHANGE_STEP_TWO("clamp wafer");

		m_sequence.push_back(m_step_one);
		m_sequence.push_back(m_step_two);

		//	copy(m_sequence.begin(),m_sequence.end(),m_sequence_pick.begin());
		//	copy(m_sequence.begin(),m_sequence.end(),m_sequence_put.begin());
		//	copy(m_sequence.begin(),m_sequence.end(),m_sequence_swap.begin());


		m_mode_sequence.insert(make_pair(EXCHANGE_MODE_PICKUP,m_sequence));
		//	m_mode_sequence.insert(make_pair(EXCHANGE_MODE_PUT_GET,m_sequence_put));
		//	m_mode_sequence.insert(make_pair(EXCHANGE_MODE_SWAP,m_sequence_swap));

		return 0;

	}
	SMEE_BOOL EXCHANGE_CLASS::handle_exchange()
	{
		std::cout<<"handle_exchange:\nfind_mode :"<<WRenum2str(m_mode)<<std::endl;
		std::map<EXCHANGE_MODE_ENUM,std::list<EXCHANGE_ABSTRACT_STEP*>>::iterator ite = m_mode_sequence.find(m_mode);
		if (ite != m_mode_sequence.end())//map´æÔÚm_modeÔªËØ
		{
			std::cout<<"find_mode:"<<WRenum2str(m_mode)<<" Success!"<<std::endl;
			std::list<EXCHANGE_ABSTRACT_STEP*>::iterator step = (ite->second).begin();
			if (step != (ite->second).end())
			{
				std::cout <<"Current_operation: "<<(*step)->name().c_str()<<std::endl;
				(*step)->step();
				(ite->second).erase(step);
				return false;
			}
			else
			{
				std::cout<<"find_mode :"<<WRenum2str(m_mode)<<" Failed!"<<std::endl;
				return true;
			}
		}
		else
		{
			throw "illegal swap mode";
		}
	}
	EXCHANGE_CLASS:: ~EXCHANGE_CLASS()
	{

	}

}


#endif