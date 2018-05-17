#include "stdafx.h"

#include "thread_mutex.h"

MUTEX g_lock;

int iTickets = 100;

HANDLE m_ticket_mutex;

IMYLOCK::~IMYLOCK()
{

}

MUTEX::MUTEX()
{
	cout<<__FUNCTION__<<endl;
	m_mutex = CreateMutex(NULL, SMEE_FALSE, NULL);
}

MUTEX::~MUTEX()
{
	cout<<__FUNCTION__<<endl;
	CloseHandle(m_mutex);//释放句柄
}

void MUTEX::lock() const
{
	cout<<__FUNCTION__<<endl;
	DWORD d = WaitForSingleObject(m_mutex, INFINITE);//一直在等待信号过来
}

void MUTEX::unlock() const
{
	cout<<__FUNCTION__<<endl;
	//
	ReleaseMutex(m_mutex);
}

CLOCK::CLOCK(const IMYLOCK &m)
:m_lock(m)
{
	cout<<__FUNCTION__<<endl;
	m_lock.lock();
}

CLOCK::~CLOCK()
{
	cout<<__FUNCTION__<<endl;
	m_lock.unlock();
}

unsigned int __stdcall startThread(void *pParam)
{
	char *pMsg = (char *)pParam;
	if (!pMsg)
	{
		return static_cast<unsigned int>(1);
	}
	CLOCK lock(g_lock);

	for (int i = 0;i < 5; ++i)
	{
		cout<<pMsg<<endl;
		Sleep(500);
	}

	return static_cast<unsigned int>(0);
}

void multi_thread()
{
	function_in(__FUNCTION__);

	HANDLE hHandle_1, hHandle_2;
	unsigned int uiThreadID_1, uiThreadID_2;
	char *pMsg_1 = "Fist thread !";
	char *pMsg_2 = "Second thread !";

	//开始创建线程
	hHandle_1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startThread, (void*)pMsg_1, 0, (LPDWORD)&uiThreadID_1);
	hHandle_2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startThread, (void*)pMsg_2, 0, (LPDWORD)&uiThreadID_2);

	//hHandle_1 = (HANDLE)_beginthreadex(NULL, 0, &startThread, (void *)pMsg_1, 0, &uiThreadID_1);
	//hHandle_2 = (HANDLE)_beginthreadex(NULL, 0, &startThread, (void *)pMsg_2, 0, &uiThreadID_2);

	DWORD deRet = WaitForSingleObject(hHandle_1, INFINITE);
	if (deRet == WAIT_TIMEOUT)
	{
		TerminateThread(hHandle_1, 0);
	}

	deRet = WaitForSingleObject(hHandle_2, INFINITE);
	if (deRet == WAIT_TIMEOUT)
	{
		TerminateThread(hHandle_2, 0);
	}

	CloseHandle(hHandle_1);
	CloseHandle(hHandle_2);

	function_out(__FUNCTION__);
}



DWORD WINAPI funcProcessOne(LPVOID lpParameter)
{
	function_in(__FUNCTION__);

	while (true)
	{
		//WaitForSingleObject(m_ticket_mutex, INFINITE);
		if (0 < iTickets)
		{
			Sleep(1000);
			cout<<endl<<__FUNCTION__<<" : "<<iTickets--<<endl;
		}
		else
		{
			break;
		}
		//ReleaseMutex(m_ticket_mutex);
	}
	
	function_out(__FUNCTION__);

	return 0;

}

DWORD WINAPI funcProcessTwo(LPVOID lpParameter)
{
	function_in(__FUNCTION__);

	while (true)
	{
		//WaitForSingleObject(m_ticket_mutex, INFINITE);

		if (0 < iTickets)
		{
			Sleep(2000);
			cout<<endl<<__FUNCTION__<<" : "<<iTickets--<<endl;
		}
		else
		{
			break;
		}
		//ReleaseMutex(m_ticket_mutex);
	}
	function_out(__FUNCTION__);
	return 0;

}

void sellTickets()
{
	function_in(__FUNCTION__);

	HANDLE hHandleOne;
	HANDLE hHandleTwo;
	hHandleOne = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)funcProcessOne, NULL, 0, NULL);
	hHandleTwo = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)funcProcessTwo, NULL, 0, NULL);

	CloseHandle(hHandleOne);
	CloseHandle(hHandleTwo);

	m_ticket_mutex = CreateMutex(NULL, false, NULL);

	function_out(__FUNCTION__);
}
