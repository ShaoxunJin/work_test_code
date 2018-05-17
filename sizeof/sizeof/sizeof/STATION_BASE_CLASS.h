#ifndef STATION_BASE_CLASS_H
#define STATION_BASE_CLASS_H

//测校上暂时不使用boost
#include "head_file.h"
#include "STATION_HEADER.h"

class STATION_BASE_CLASS
{
public:
	explicit STATION_BASE_CLASS()
	{

	};
	~STATION_BASE_CLASS(){};

	virtual void check_from_station_material(int* present) = 0;
	virtual void check_to_station_material(int* present) = 0;
};

class LOAD_ROBOT : public STATION_BASE_CLASS
{
public:
	LOAD_ROBOT();
	virtual ~LOAD_ROBOT();
	void check_from_station_material(int* present);
	void check_to_station_material(int* present);

protected:
private:
};






#endif