/*
Slim reader/writer (SRW) locks enable the threads of a single process to 
access shared resources; 
they are optimized for speed and occupy very little memory.							IMP
Slim reader-writer locks cannot be shared across processes.

Reader threads read data from a shared resource whereas 
writer threads write data to a shared resource. 
When multiple threads are reading and writing using a shared resource, 
exclusive locks such as a critical section or mutex can 
become a bottleneck if the reader threads run continuously 
but write operations are rare.

SRW locks provide two modes in which threads can access a shared resource:				IMP

1> Shared mode, which grants shared read-only access to multiple reader threads,		IMP
which enables them to read data from the shared resource concurrently. 
If read operations exceed write operations, this concurrency increases performance	
and throughput compared to critical sections.											IMP

2> Exclusive mode, which grants read/write access to one writer thread at a time. 
When the lock has been acquired in exclusive mode, no other thread can 
access the shared resource until the writer releases the lock.

A single SRW lock can be acquired in either mode; 
reader threads can acquire it in shared mode 
whereas writer threads can acquire it in exclusive mode. 
There is no guarantee about the order in which threads that								IMP
request ownership will be granted ownership; 
SRW locks are neither fair nor FIFO.													IMP

An SRW lock is the size of a pointer.													IMP
The advantage is that it is fast to update the lock state.								IMP
The disadvantage is that very little state information can be stored,					IMP
so SRW locks cannot be acquired recursively.											IMP
In addition, a thread that owns an SRW lock in shared mode cannot upgrade				IMP
its ownership of the lock to exclusive mode.

The caller must allocate an SRWLOCK structure and initialize it by					
either calling InitializeSRWLock (to initialize the structure dynamically) 
or assign the constant SRWLOCK_INIT to the structure variable 
(to initialize the structure statically).

*/



#include <iostream>
#include <windows.h>
using namespace std;

int g_data = 0;

SRWLOCK g_SWR_Lock;
HANDLE threads_cs[4] = {NULL, NULL, NULL, NULL};
#define PRODUCER_COUNT  30
#define EOP				999

int g_WriterCount = 0;
int g_ReaderCount = 0;
//=================================================================

DWORD WINAPI WriterFunc(LPVOID param)
{
	bool terminate = false;
	cout<<"\n[WriterFunc :"<<GetCurrentThreadId() <<"] started"<<endl;
	for(int count =0; count < PRODUCER_COUNT ; ++count)
	{
		AcquireSRWLockExclusive(&g_SWR_Lock);
		if(count >= PRODUCER_COUNT-2 )
		{
			g_data = EOP;
			terminate = true;
		}
		else
			++g_data;
		++g_WriterCount;
		cout<<"\n#### [WriterFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

		ReleaseSRWLockExclusive(&g_SWR_Lock);
		if(terminate)
			break;
		Sleep(20);
	}
	cout<<"\n[WriterFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}

DWORD WINAPI ReaderFunc(LPVOID param)
{
	bool terminate = false;
	cout<<"\n[ReaderFunc :"<<GetCurrentThreadId() <<"] started"<<endl;
	for(; ; )
	{
		if( TryAcquireSRWLockShared(&g_SWR_Lock) != 0 ) 
		{
			if(g_data == EOP )
				terminate = true;
			++g_ReaderCount;
			cout<<"\n[ReaderFunc :"<<GetCurrentThreadId() <<"] g_data="<<g_data<<endl;

			ReleaseSRWLockShared(&g_SWR_Lock);
		}
		if(terminate)
			break;
		Sleep(10);
	}
	cout<<"\n[ReaderFunc :"<<GetCurrentThreadId() <<"] Ended"<<endl;
	return 0;
}

/*
typedef struct _RTL_SRWLOCK {                            
        PVOID Ptr;                                       
} RTL_SRWLOCK, *PRTL_SRWLOCK;   
typedef RTL_SRWLOCK SRWLOCK, *PSRWLOCK;
*/
void main()
{
	cout<<"\n[Main :"<<GetCurrentThreadId() <<"] Program started"<<endl;
	InitializeSRWLock(&g_SWR_Lock);

	threads_cs[0] = CreateThread(NULL,0,WriterFunc,NULL,0,NULL);
	threads_cs[1] = CreateThread(NULL,0,ReaderFunc,NULL,0,NULL);
	threads_cs[2] = CreateThread(NULL,0,ReaderFunc,NULL,0,NULL);
	threads_cs[3] = CreateThread(NULL,0,ReaderFunc,NULL,0,NULL);

	WaitForMultipleObjects(4,threads_cs,TRUE,INFINITE);

	//NOE: No delete function

	cout<<"\n#### [Main :"<<GetCurrentThreadId() <<"] g_producerCount ="<<g_WriterCount<<endl;
	cout<<"\n#### [Main :"<<GetCurrentThreadId() <<"] g_consumerCount ="<<g_ReaderCount<<endl;

	cout<<"\n[Main :"<<GetCurrentThreadId() <<"] Program Ended"<<endl;
}
