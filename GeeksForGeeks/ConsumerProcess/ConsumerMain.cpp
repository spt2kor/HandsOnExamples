#include <windows.h>
#include <iostream>
using namespace std;
//===========================================================================================
#define SharedMemoryName "ProducerConsumer-MessageQueue-AccrossTheProcess"
#define SharedMemoryName_Empty "ProducerConsumer-MessageQueue-AccrossTheProcess_Empty"
#define SharedMemoryName_Full "ProducerConsumer-MessageQueue-AccrossTheProcess_Full"
#define SharedMemoryName_Mutex "ProducerConsumer-MessageQueue-AccrossTheProcess_Mutex"

#define MessageQueue_Length 16
#define MQ_FULL			1
#define MQ_EMPTY		2
#define MQ_OP_SUCCESS	0
struct messageQueue
{
	//============================================================
	struct Data
	{
		int m_data;
		char m_dummy[24];
		Data(int no) : m_data(no){}
	};
	Data m_data[MessageQueue_Length];
	int m_front,m_rear;
	int m_size;
	//============================================================
	int GetSize(){return m_size;}
	void Init()
	{
		cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Init()"<<endl;
		m_front = m_rear = -1;
		m_size = 0;
	}

	int  Push(Data obj)
	{ 
		cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Push(), data = "<<obj.m_data<<endl;
		if(m_size == MessageQueue_Length)
			return MQ_FULL;
		else
		{
			++m_size;
			if(m_size == 1)
			{
				m_front = m_rear = 0;
			}
			else
			{
				m_rear = (++m_rear) % MessageQueue_Length;				
			}
			m_data[m_rear] = obj;
		}
		return MQ_OP_SUCCESS;
	}

	int  Pop(Data& obj)
	{
		if(m_size == 0)
			return MQ_EMPTY;
		else
		{
			obj = m_data[m_front];
			--m_size;
			if(m_size == 0)
				m_front = m_rear = -1;
			else
				m_front = (++m_front) % MessageQueue_Length;				
		}

		cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Pop(), data = "<<obj.m_data<<endl;
		return MQ_OP_SUCCESS;
	}


	void PrintMessageQueue()
	{
		cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue:m_front="<<m_front<<",m_rear="<<m_rear<<",m_size="<<m_size<<endl;
	}

};

HANDLE g_FileMappigObject = NULL;
messageQueue *g_pMessageQueueBufferhandle = NULL;

HANDLE g_IsItEmptySem = NULL; 
HANDLE g_IsItFullSem = NULL; 
HANDLE g_MessageQueueMutex = NULL; 

#define WRITER_THREADS 5
#define READER_THREADS 5
HANDLE threads[READER_THREADS] = {NULL, NULL, NULL, NULL, NULL};
int threadsData[READER_THREADS] = {1,2,3,4,5};
#define EOP 99999

#define ITEMS_TO_PRODUCE 20
//===========================================================================================
void CreateReaderThreads();
void CreateSharedMemoryResource();
DWORD WINAPI ConsumerFunc(LPVOID param);
void DeleteSharedMemoryResource();
//===================================================================================

void main()
{
	cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Program Started"<<endl;

	CreateSharedMemoryResource();

	CreateReaderThreads();

	DeleteSharedMemoryResource();
	cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Program Finished"<<endl;

}
//=====================================
DWORD WINAPI ConsumerFunc(LPVOID param)
{
	int threadNo = * ((int*)param);
	cout<<"\n[Consumer:"<<GetCurrentThreadId() <<"] Consumer Thread Started threadNo="<<threadNo<<endl;

	for (; ;)
	{
		//cout<<"\n[Consumer:"<<threadNo<<"]-"<<count<<endl;
		DWORD result = WaitForSingleObject(g_IsItFullSem , INFINITE);	//initial value is 1 => 0
		if(result == WAIT_OBJECT_0)
		{
			//cout<<"\n[Consumer:"<<threadNo<<"]-got g_IsItFullSem"<<endl;
			result = WaitForSingleObject( g_MessageQueueMutex, INFINITE);
			if(result == WAIT_OBJECT_0)
			{
				//cout<<"\n[Consumer:"<<threadNo<<"]-got g_MessageQueueMutex"<<endl;
				messageQueue::Data data(0);
				int result = g_pMessageQueueBufferhandle->Pop(data);
				ReleaseMutex(g_MessageQueueMutex);
				if(data.m_data == EOP)
					break;
				if( MQ_EMPTY == result )
				{
					cout<<"\nERROR: [Consumer:"<<GetCurrentThreadId() <<"] Consumer Thread -MessageQueueIsEMPTY"<<endl;
				}
				else
				{
					cout<<"\n[Consumer:"<<GetCurrentThreadId() <<"] Consumer Thread -"<<threadNo<<", pop(data)="<<data.m_data<<endl;
					ReleaseSemaphore(g_IsItEmptySem , 1 , NULL);	//initial value is 15 -> 16
				}				
			}			
		}		
	}
	cout<<"\n[Consumer:"<<GetCurrentThreadId() <<"] Consumer Thread Exiting"<<endl;
	return 0;
}
//===================================================================
/*
        hThreadArray[i] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pDataArray[i],          // argument to thread function 
            0,                      // use default creation flags 
            dwThreadIdArray[i]);   // returns the thread identifier 
*/
void CreateReaderThreads()
{
	for(int i=0 ; i <READER_THREADS  ; ++i)
	{
		threads[ i ] = CreateThread(NULL,0,ConsumerFunc,&threadsData[i],0,NULL);
	}
	WaitForMultipleObjects(READER_THREADS,threads,TRUE,INFINITE);

	for(int i=0 ; i <READER_THREADS  ; ++i)
	{
		CloseHandle(threads[ i ]);
	}	
}

//===================================================================
/*
HANDLE CreateFileMappingA(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCSTR                lpName
);

LPVOID WINAPI MapViewOfFile(
  _In_ HANDLE hFileMappingObject,
  _In_ DWORD  dwDesiredAccess,
  _In_ DWORD  dwFileOffsetHigh,
  _In_ DWORD  dwFileOffsetLow,
  _In_ SIZE_T dwNumberOfBytesToMap
);
*/
void CreateSharedMemoryResource()
{
	bool isExistingMQ = false;
	g_FileMappigObject = CreateFileMappingA(	NULL
											 ,	NULL
											 , PAGE_READWRITE
											 , 0
											 , sizeof(messageQueue)
											 , SharedMemoryName );
	if(g_FileMappigObject == NULL)
	{
		cout<<"\nERROR : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create CreateFileMapping()= "<<SharedMemoryName <<endl;
		return;
	}
	else if(ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout<<"\nWARNING: [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Attaching to existing CreateFileMapping()= "<<SharedMemoryName <<", g_FileMappigObject= "<<g_FileMappigObject <<endl;
		isExistingMQ = true;
	}
	else
	{
		cout<<"\nWARNING: [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Successfully CreateFileMapping()= "<<SharedMemoryName<<", g_FileMappigObject= "<<g_FileMappigObject <<endl;
	}
	//================================================================
	
	LPVOID pbuffer				= MapViewOfFile(	g_FileMappigObject
												, FILE_MAP_ALL_ACCESS 
												, 0
												, 0
												, 0);

	g_pMessageQueueBufferhandle = (messageQueue*)	pbuffer;

	if(pbuffer == NULL)
	{
		cout<<"\nERROR : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create MapViewOfFile()= "<<SharedMemoryName <<endl;
		CloseHandle(g_FileMappigObject);
		return;
	}
	else
	{
		cout<<"\n: [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Successfully MapViewOfFile()= "<<SharedMemoryName <<",g_pMessageQueueBufferhandle="<<g_pMessageQueueBufferhandle<<", pbuffer="<<pbuffer<<endl;
		if(isExistingMQ)
		{
			g_pMessageQueueBufferhandle->PrintMessageQueue();
		}
		else
		{
			g_pMessageQueueBufferhandle->Init();
		}
	}
	/* testing
	*g_pMessageQueueBufferhandle = 192;
	cout<<std::dec<<"\n *g_pMessageQueueBufferhandle = "<<(int )( *g_pMessageQueueBufferhandle) <<endl;
	*/
	//================================================================
	//#define SharedMemoryName_Empty "ConsumerConsumer-MessageQueue-AccrossTheProcess_Empty"
	g_IsItEmptySem = CreateSemaphoreA(NULL,MessageQueue_Length,MessageQueue_Length,SharedMemoryName_Empty); 
	if(g_IsItEmptySem == NULL)
	{
		cout<<"\nERROR : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_EmptySem= "<<SharedMemoryName_Empty <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_EmptySem= "<<SharedMemoryName_Empty <<", = "<<g_IsItEmptySem<<endl;
	}
	else
	{
		cout<<"\n : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_EmptySem= "<<SharedMemoryName_Empty <<", = "<<g_IsItEmptySem<<endl;
	}
	//================================================================
	//#define SharedMemoryName_Full "ConsumerConsumer-MessageQueue-AccrossTheProcess_Full"
	g_IsItFullSem = CreateSemaphoreA( NULL, 0, MessageQueue_Length, SharedMemoryName_Full); 
	if(g_IsItFullSem == NULL)
	{
		cout<<"\nERROR : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_FullSem= "<<SharedMemoryName_Full <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_FullSem= "<<SharedMemoryName_Full <<", = "<<g_IsItFullSem<<endl;
	}
	else
	{
		cout<<"\n : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_FullSem= "<<SharedMemoryName_Full <<", = "<<g_IsItFullSem<<endl;
	}
	//================================================================
	//#define SharedMemoryName_Mutex "ConsumerConsumer-MessageQueue-AccrossTheProcess_Mutex"
	g_MessageQueueMutex = CreateMutexA(NULL, false, SharedMemoryName_Mutex); 
	if(g_MessageQueueMutex == NULL)
	{
		cout<<"\nERROR : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<", = "<<g_MessageQueueMutex<<endl;
	}
	else
	{
		cout<<"\n : [Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<", = "<<g_MessageQueueMutex<<endl;
	}

	cout<<"\n[Consumer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] SharedMemory resource created successfully"<<endl;
}
void DeleteSharedMemoryResource()
{
	CloseHandle(g_IsItEmptySem); 
	CloseHandle(g_IsItFullSem); 
	CloseHandle(g_MessageQueueMutex); 

	UnmapViewOfFile(g_pMessageQueueBufferhandle);
	CloseHandle(g_FileMappigObject); 
}