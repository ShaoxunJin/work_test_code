#include "stdafx.h"
#include "CAST.h"

PARENTS::PARENTS(string n /* = */ )
:name(n)
{

}

PARENTS::~PARENTS()
{

}


void PARENTS::Speak()
{
	cout<<"I am "<<name<<", I love my children !"<<endl;
}

void PARENTS::Work()
{
	cout<<"I am "<<name<<", I need work for my family !"<<endl;
}

CHILDREN::CHILDREN(string n /* = */ )
:PARENTS(n)
{

}

CHILDREN::~CHILDREN()
{

}

void CHILDREN::Speak()
{
	cout<<"I am "<<name<<", I love my parents !"<<endl;
}

void CHILDREN::Study()
{
	cout<<"I am "<<name<<", I need to study for future !"<<endl;
}

STRANGER::STRANGER(string n /* = */ )
:name(n)
{
	
}

STRANGER::~STRANGER()
{

}

void STRANGER::SelfIntroduce()
{
	cout<<"I am a strange !"<<endl;
}

void STRANGER::Speak()
{
	cout<<"Do not talk to "<<name<<", who is a stranger !"<<endl;
}

void cast_test()
{
	cout<<"dynamic_cast from children to parent is safe "<<endl;
	CHILDREN *daughter_d = new CHILDREN("Daughter who pretend to be my mother !");
	PARENTS *mother_d = dynamic_cast<PARENTS*>(daughter_d);//right 从子类到父类
	mother_d->Speak();
	mother_d->Work();

	cout<<"static_cast from child class to base class :"<<endl;
	//从child to father 也是一种安全的
	CHILDREN *son_s = new CHILDREN("Son who pretend to be my father !");
	PARENTS *father_s = static_cast<PARENTS*>(son_s);//从派生类到子类肯定是很很安全的
	father_s->Speak();
	father_s->Work();

	//dynamic_cast from base class to child class
	cout<<"dynamic_cast from base class to base class !"<<endl;
	PARENTS *father_d = new PARENTS("Father who pretend to be my son !");
	CHILDREN *son_d = dynamic_cast<CHILDREN*>(father_d);//这里如果使用staic_cast 则肯定是不行的
	//这里是符合正常的逻辑的
	if (son_d)
	{
		son_d->Speak();
		son_d->Study();
	}
	else
	{
		cout<<"dynamic_cast from father to child failed !"<<endl;
	}

	cout<<"static_cast from base class to child class !"<<endl;
	PARENTS *mother_s = new PARENTS("Mother who pretend to be my daughter !");
	CHILDREN *daughter_s = static_cast<CHILDREN*>(mother_s);//子类指针指向父类对象，而父类中不一定有具体的实现方式
	//这里是不符合正常的逻辑的
	if (daughter_s)
	{
		daughter_s->Speak();
		daughter_s->Study();		
	}
	else
	{
		cout<<"static_cast from mother to daughter failed !"<<endl;
	}

	cout<<"dynamic_cast from non-related class :"<<endl;
	STRANGER *stranger_d = dynamic_cast<STRANGER*>(daughter_d);
	if (stranger_d)
	{
		//stranger_d->Speak();
		stranger_d->SelfIntroduce();
	}
	else
	{
		cout<<"dynamic_cast from non-related class failed !"<<endl;
	}

	cout<<"reinterpret_cast from non-related class :"<<endl;
	STRANGER *stranger_r = reinterpret_cast<STRANGER*>(daughter_d);
	if (stranger_r)
	{
		//stranger_d->Speak();
		stranger_r->SelfIntroduce();//虽然发生了转换，但是显然子类中没有stranger具体对象selfintroduce属性
		//reinterpret最好是对象都是一样的才可以进行
		//speak中调用了具体的对象成员 而对象成员两者之间是毫无关系的
	}
	else
	{
		cout<<"reinterpret_cast from non-related class failed !"<<endl;
	}

	//
	cout<<"use dynamic_cast to cast back from static_cast :"<<endl;
	CHILDREN *child_s = dynamic_cast<CHILDREN*>(father_s);
	if (child_s)
	{
		child_s->Speak();
		child_s->Study();
		child_s->Work();
	}
	cout<<"use dynamic_cast to cast back from reinterpret_cast:"<<endl;
	CHILDREN *child_r = dynamic_cast<CHILDREN*>(stranger_r);
	if (child_r)
	{
		child_r->Speak();
		child_r->Study();
		child_r->Work();
	}
	else
	{
		cout<<"use dynamic_cast to cast back from reinterpret_cast failed !"<<endl;
	}

	delete daughter_d;
	daughter_d = NULL;
	delete son_s;
	son_s = NULL;
	delete father_d;
	father_d = NULL;
	delete mother_s;
	mother_s = NULL;

}
