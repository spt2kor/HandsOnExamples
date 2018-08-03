#include <iostream>
#include <windows.h>
using namespace std;

int g_data = 0;
CRITICAL_SECTION g_prod_cs;

HANDLE  g_evBufferNotEmpty = NULL;
HANDLE  g_evBufferNotFull  = NULL;

HANDLE threads_cs[2] = {NULL, NULL};
#define PRODUCER_COUNT  30
#define EOP				999

int g_producerCount = 0;
int g_consumerCount = 0;
//=================================================================
ostream& operator<<(ostream& out, CRITICAL_SECTION& cs)
{
	cout<<"\n CRITICAL_SECTION details"<<endl;
	cout<<"\n cs.LockCount = "<<cs.LockCount<<endl;
	cout<<"\n cs.RecursionCount = "<<cs.RecursionCount<<endl;
	cout<<"\n cs.OwningThread = "<<cs.OwningThread<<endl;
	cout<<"\n cs.LockSemaphore = "<<cs.LockSemaphore<<endl;
	cout<<"\n cs.SpinCount = "<<cs.SpinCount<<endl;
	return out;
}

DWORD WINAPI ProducerFunc(LPVOID param)
{
	bool terminate = false;
	
	SetEvent(g_evBufferNotFull);

	cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] started"<<endl;

	for(int count =0; count < PRODUCER_COUNT ; ++count)
	{
		WaitForSingleObject(g_evBufferNotFull,INFINITE);
		{
			EnterCriticalSection(&g_prod_cs);			//making recursive aquisition
			if(count >= PRODUCER_COUNT-5 )
			{
				g_data = EOP;
				terminate = true;
			}
			else
				++g_data;
			++g_producerCount;
			cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

			LeaveCriticalSection(&g_prod_cs);
		}
		SetEvent(g_evBufferNotEmpty);
		if(terminate)
			break;

		Sleep(20);
	}
	cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}

DWORD WINAPI ConsumerFunc(LPVOID param)
{
	Sleep(100);
	bool terminate = false;
	cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] started"<<endl;

	for(; ; )
	{
		WaitForSingleObject(g_evBufferNotEmpty,INFINITE);
		{
			EnterCriticalSection(&g_prod_cs);
			if(g_data == EOP )
				terminate = true;
			--g_data;
			++g_consumerCount;
			cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

			LeaveCriticalSection(&g_prod_cs);
		}
		SetEvent(g_evBufferNotFull);
		if(terminate)
			break;
		Sleep(50);
	}
	cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}

/*
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateEventA(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
    _In_ BOOL bManualReset,
    _In_ BOOL bInitialState,
    _In_opt_ LPCSTR lpName
    );
*/
void main()
{
	cout<<"\n[Main :"<<GetCurrentThreadId() <<"] Program started : "<< __FILE__<<endl;
	
	BOOL result = InitializeCriticalSectionAndSpinCount(&g_prod_cs , 4000);
	if(result != 0)//success
		cout<<"\n[Main :"<<GetCurrentThreadId() <<"] created g_prod_cs="<<g_prod_cs<<endl;
	else
		cout<<"\nERROR [Main :"<<GetCurrentThreadId() <<"] failed to created g_prod_cs=GLE="<<GetLastError()<<endl;
	//=======================================================================================
	g_evBufferNotEmpty	= CreateEventA(NULL,FALSE,FALSE,NULL);
	g_evBufferNotFull	= CreateEventA(NULL,FALSE,FALSE,NULL);
	
	if(g_evBufferNotEmpty != NULL )//success
		cout<<"\n[Main :"<<GetCurrentThreadId() <<"] created g_evBufferNotEmpty="<<g_evBufferNotEmpty<<endl;
	else
		cout<<"\nERROR [Main :"<<GetCurrentThreadId() <<"] failed to created g_evBufferNotEmpty=GLE="<<GetLastError()<<endl;
	//=======================================================================================
	if(g_evBufferNotFull != NULL )//success
		cout<<"\n[Main :"<<GetCurrentThreadId() <<"] created g_evBufferNotFull="<<g_evBufferNotFull<<endl;
	else
		cout<<"\nERROR [Main :"<<GetCurrentThreadId() <<"] failed to created g_evBufferNotFull=GLE="<<GetLastError()<<endl;
	//=======================================================================================
	threads_cs[0] = CreateThread(NULL,0,ProducerFunc,NULL,0,NULL);
	threads_cs[1] = CreateThread(NULL,0,ConsumerFunc,NULL,0,NULL);

	WaitForMultipleObjects(2,threads_cs,TRUE,INFINITE);

	CloseHandle(g_evBufferNotEmpty);
	CloseHandle(g_evBufferNotFull);
	DeleteCriticalSection(&g_prod_cs);

	cout<<"\n#### [Main :"<<GetCurrentThreadId() <<"] g_producerCount ="<<g_producerCount<<endl;
	cout<<"\n#### [Main :"<<GetCurrentThreadId() <<"] g_consumerCount ="<<g_consumerCount<<endl;

	cout<<"\n[Main :"<<GetCurrentThreadId() <<"] Program Ended"<<endl;
}

/*
typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
*/