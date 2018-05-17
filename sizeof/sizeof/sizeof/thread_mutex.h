#ifndef _THREAD_MUTEX_H_
#define _THREAD_MUTEX_H_

#include "head_file.h"
#include <Windows.h>
#include <process.h>

class IMYLOCK
{
public:
	virtual ~IMYLOCK();
	virtual void lock() const = 0;
	virtual void unlock() const = 0;
protected:
private:
};

//互斥锁
class MUTEX : public IMYLOCK
{
public:
	MUTEX();
	~MUTEX();
	virtual void lock() const;
	virtual void unlock() const;

private:
	HANDLE m_mutex;
};

class CLOCK
{
public:
	CLOCK(const IMYLOCK&);
	~CLOCK();

protected:
private:
	const IMYLOCK& m_lock;
};

//unsigned int startThread(void *pParam);
unsigned int __stdcall startThread(void *pParam);

void multi_thread();

//下面这个是卖车票的例子
//线程的入口函数

DWORD WINAPI funcProcessOne(LPVOID lpParameter);

DWORD WINAPI funcProcessTwo(LPVOID lpParameter);

void sellTickets();

#endif