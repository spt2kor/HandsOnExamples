#include <iostream>
#include <list>
#include <windows.h>
using namespace std;

#define Producer_Count 4
#define Consumer_Count 4
#define BoundedBufferLength 16

#define PRODUCER_MAX_COUNT 10
#define EOP   INT_MAX

HANDLE MyThreads[Producer_Count+Consumer_Count]= {NULL, NULL, NULL , NULL , NULL,NULL,NULL,NULL};


list<int>  m_resource;
int ProducerCounter=0;
HANDLE mutex = NULL;
//====================================================
//typedef void far            *LPVOID;
//#define WINAPI      __stdcall
//typedef unsigned long       DWORD;
//#define INFINITE            0xFFFFFFFF  // Infinite timeout

DWORD WINAPI ExecuteProducerFunc(LPVOID pthreadID)
{
	int TotalProduce = 0;
	int threadID = *( (int *)pthreadID);
	cout<<"\n ****  ["<<GetCurrentThreadId()<<"] Produer "<<threadID<<endl;
	while(TotalProduce < PRODUCER_MAX_COUNT)
	{
		DWORD dwWaitResult = WaitForSingleObject(mutex , INFINITE);
		if( dwWaitResult == WAIT_OBJECT_0 )
		{
			if(m_resource.size() != BoundedBufferLength)
			{
				++TotalProduce;
				cout<<"\n ****  ["<<GetCurrentThreadId()<<"] Produer "<<threadID<<", value = "<<++ProducerCounter<<endl;
				if(TotalProduce ==  PRODUCER_MAX_COUNT-1)
					m_resource.push_back(EOP);
				else
					m_resource.push_back(ProducerCounter);
			}
			else
				cout<<"\n ****  ["<<GetCurrentThreadId()<<"] Produer "<<threadID<<", BUFFER FULL "<<endl;
			ReleaseMutex(mutex);
			Sleep(10);
		}
	}

	cout<<"\n ****  ["<<GetCurrentThreadId()<<"] Produer Finished threadNo = "<<threadID<<endl;
	return threadID;
}

DWORD WINAPI ExecuteCunsumerFunc(LPVOID pthreadID)
{
	int TotalProduce = 0;
	int threadID = *( (int *)pthreadID);
	cout<<"\n  ["<<GetCurrentThreadId()<<"] #### Cunsumer "<<threadID<<endl;
	while(true)
	{
		DWORD dwWaitResult = WaitForSingleObject(mutex , 100);
		if( dwWaitResult == WAIT_OBJECT_0 )
		{
			if(! m_resource.empty())
			{
				int data = m_resource.front();
				m_resource.pop_front();
				if(data ==  EOP)
					break;
				else
					cout<<"\n ####  ["<<GetCurrentThreadId()<<"] Cunsumer "<<threadID<<", value = "<<data<<endl;
			}
			else
				cout<<"\n ####  ["<<GetCurrentThreadId()<<"] Cunsumer "<<threadID<<", BUFER EMPTY "<<endl;
			ReleaseMutex(mutex);
			Sleep(100);
		}
	}

	cout<<"\n ####  ["<<GetCurrentThreadId()<<"] Cunsumer Finished : threadNo = "<<threadID<<endl;
	return threadID;
}
//====================================================
void ExecuteProducerFunc(int ThreadID)
{
	cout<<"\n  ["<<GetCurrentThreadId()<<"] ExecuteProducerFunc() Produer to be created threadNo = "<<ThreadID<<endl;
	MyThreads[ThreadID-1] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            ExecuteProducerFunc,       // thread function name
            (void*)&ThreadID,          // argument to thread function 
            0,                      // use default creation flags 
            NULL);   // returns the thread identifier 
	cout<<"\n  ["<<GetCurrentThreadId()<<"] ExecuteProducerFunc() Produer Created threadID = "<<MyThreads[ThreadID-1]<<endl;
}

void CreateCunsumerFunc(int ThreadID)
{
	cout<<"\n  ["<<GetCurrentThreadId()<<"] CreateCunsumerFunc() Produer to be created threadNo= "<<ThreadID<<endl;
	MyThreads[ThreadID-1] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            ExecuteCunsumerFunc,       // thread function name
            (void*)&ThreadID,          // argument to thread function 
            0,                      // use default creation flags 
            NULL);   // returns the thread identifier 
	cout<<"\n  ["<<GetCurrentThreadId()<<"] ExecuteProducerFunc() Produer Created : threadID = "<<MyThreads[ThreadID-1]<<endl;

}

//====================================================
void main()
{
	cout<<"\n ["<<GetCurrentThreadId()<<"] Program started "<<endl;

	
	mutex = CreateMutex(	NULL,              // default security attributes
							FALSE,             // initially not owned
							NULL);             // unnamed mutex

	cout<<"\n ["<<GetCurrentThreadId()<<"] Mutex object created mutex= "<<mutex<<endl;
	int i = 0;
	for(; i< 4 ; ++i)
		CreateCunsumerFunc(i+1);

	cout<<"\n  ["<<GetCurrentThreadId()<<"] Consumer threads are created "<<endl;
	for(; i< Producer_Count+Consumer_Count  ; ++i)
		ExecuteProducerFunc(i+1);

	cout<<"\n  ["<<GetCurrentThreadId()<<"] Producer threads are created , going for wait state"<<endl;
	

	WaitForMultipleObjects( Producer_Count+Consumer_Count , MyThreads,TRUE , INFINITE); 

	cout<<"\n  ["<<GetCurrentThreadId()<<"] all threads are finished "<<endl;

	for(i = 0; i< Producer_Count+Consumer_Count  ; ++i)
		CloseHandle(MyThreads[i]);


	CloseHandle(mutex);

	cout<<"\n Program Ended"<<endl;
};
