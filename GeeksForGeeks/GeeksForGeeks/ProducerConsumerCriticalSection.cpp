/*
//https://docs.microsoft.com/en-us/windows/desktop/sync/critical-section-objects
threads waiting on a critical section do not acquire the critical section on a							IMP
first-come, first-serve basis. This change increases performance significantly for most code

Lock not guaranteed in FIFO ourder
 However, some applications depend on first-in, first-out (FIFO) ordering and may perform poorly 
 or not at all on current versions of Windows (for example, applications that have been using 
 critical sections as a rate-limiter). To ensure that your code continues to work correctly,
 you may need to add an additional level of synchronization. For example, suppose you have a 
 producer thread and a consumer thread that are using a critical section object to synchronize
 their work. Create two event objects, one for each thread to use to signal that it is ready 
 for the other thread to proceed. The consumer thread will wait for the producer to signal
 its event before entering the critical section, and the producer thread will wait for the 
 consumer thread to signal its event before entering the critical section. After each thread 
 leaves the critical section, it signals its event to release the other thread.

 Threads that are waiting on a critical section are added to a wait queue; they are woken and 
 generally acquire the critical section in the order in which they were added to the queue. 
 However, if threads are added to this queue at a fast enough rate, performance can be degraded 
 because of the time it takes to awaken each waiting thread.
 
 No TimeOut
 A thread uses the EnterCriticalSection or TryEnterCriticalSection function to request ownership of a critical section.			IMP
 It uses the LeaveCriticalSection function to release ownership of a critical section. 
 If the critical section object is currently owned by another thread, EnterCriticalSection waits indefinitely for ownership. 
 In contrast, when a mutex object is used for mutual exclusion, the wait functions accept a specified time-out interval. 
 The TryEnterCriticalSection function attempts to enter a critical section without blocking the calling thread.

 recursive allowed
 When a thread owns a critical section, it can make additional calls to EnterCriticalSection or 
 TryEnterCriticalSection without blocking its execution. This prevents a thread from deadlocking itself							IMP
 while waiting for a critical section that it already owns. To release its ownership, the thread 
 must call LeaveCriticalSection one time for each time that it entered the critical section. There 
 is no guarantee about the order in which waiting threads will acquire ownership of the critical section.

 spin and try multiple times then go for sleep
 A thread uses the InitializeCriticalSectionAndSpinCount or SetCriticalSectionSpinCount function to 
 specify a spin count for the critical section object. Spinning means that when a thread tries to acquire a						IMP
 critical section that is locked, the thread enters a loop, checks to see if the lock is released, 
 and if the lock is not released, the thread goes to sleep.
 On single-processor systems, the spin count is ignored and the critical section spin count is set to 0 (zero).					IMP
 On multiprocessor systems, if the critical section is unavailable, the calling thread spins dwSpinCount times					IMP
 before performing a wait operation on a semaphore that is associated with the critical section.
 If the critical section becomes free during the spin operation, the calling thread avoids the wait operation.
*/


#include <iostream>
#include <windows.h>
using namespace std;

int g_data = 0;

CRITICAL_SECTION g_crt_sec;
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
	cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] started"<<endl;
	for(int count =0; count < PRODUCER_COUNT ; ++count)
	{
		EnterCriticalSection(&g_crt_sec);
		if(count >= PRODUCER_COUNT-5 )
		{
			g_data = EOP;
			terminate = true;
		}
		else
			++g_data;
		++g_producerCount;
		cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

		LeaveCriticalSection(&g_crt_sec);
		if(terminate)
			break;
		Sleep(20);
	}
	cout<<"\n[ProducerFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}

DWORD WINAPI ConsumerFunc(LPVOID param)
{
	bool terminate = false;
	cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] started"<<endl;
	for(; ; )
	{
		EnterCriticalSection(&g_crt_sec);
		if(g_data == EOP )
			terminate = true;
		--g_data;
		++g_consumerCount;
		cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

		LeaveCriticalSection(&g_crt_sec);
		if(terminate)
			break;
		Sleep(50);
	}
	cout<<"\n[ConsumerFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}
//  consumer get less change compared to producer // not FIFO or ordered
void main()
{
	cout<<"\n[Main :"<<GetCurrentThreadId() <<"] Program started"<<endl;
	BOOL result = InitializeCriticalSectionAndSpinCount(&g_crt_sec , 4000);
	if(result != 0)//success
		cout<<"\n[Main :"<<GetCurrentThreadId() <<"] created g_crt_sec="<<g_crt_sec<<endl;
	else
		cout<<"\nERROR [Main :"<<GetCurrentThreadId() <<"] failed to created g_crt_sec=GLE="<<GetLastError()<<endl;

	threads_cs[0] = CreateThread(NULL,0,ProducerFunc,NULL,0,NULL);
	threads_cs[1] = CreateThread(NULL,0,ConsumerFunc,NULL,0,NULL);

	WaitForMultipleObjects(2,threads_cs,TRUE,INFINITE);

	DeleteCriticalSection(&g_crt_sec);

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