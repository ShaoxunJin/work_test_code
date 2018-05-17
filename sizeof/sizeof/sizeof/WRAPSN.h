#ifndef WRAPSN_H
#define WRAPSN_H


#include "WRMC_106.h"

#include "head_file.h"
#include "HARDWARE.h"

class WRAPSN
{
public:
	WRAPSN(){}
	~WRAPSN(){}

	virtual void set_exchange_method(WR_106_EXCHANGE_METHOD_ENUM method) = 0;

	virtual WR_106_EXCHANGE_METHOD_ENUM get_exchange_method() = 0;

	virtual int send_wafer() = 0;

	virtual int receive_wafer() = 0;

protected:

private:
	
};


class WRAPPU : public WRAPSN
{
public:
	WRAPPU(const char* class_name, WR_106_EXCHANGE_METHOD_ENUM method);
	~WRAPPU();

	void set_exchange_method(WR_106_EXCHANGE_METHOD_ENUM method);

	WR_106_EXCHANGE_METHOD_ENUM get_exchange_method();

	int send_wafer();

	int receive_wafer();

protected:
private:

	WR_106_EXCHANGE_METHOD_ENUM m_exchange_method;
	const char* m_name;

};



#endif