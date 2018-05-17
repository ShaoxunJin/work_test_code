#ifndef CAST_H
#define CAST_H

#include "head_file.h"

class PARENTS
{
public:
	PARENTS(string n = "parent");
	virtual ~PARENTS();

	virtual void Speak();
	void Work();

protected:
	string name;

private:
};

class CHILDREN : public PARENTS
{
public:
	CHILDREN(string n = "children");
	virtual ~CHILDREN();
	
	virtual void Speak();
	void Study();

protected:
private:
};

class STRANGER
{
public:
	STRANGER(string n = "stranger");
	virtual ~STRANGER();
	void SelfIntroduce();
	void Speak();

protected:
private:
	string name;
};

void cast_test();


#endif