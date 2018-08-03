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
	int m_count; 
	//============================================================
	int GetSize(){return m_size;}
	void Init()
	{
		cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Init()"<<endl;
		m_front = m_rear = -1;
		m_size = 0;
		m_count = 0;
	}

	int  Push(Data obj)
	{ 
		cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Push(), data = "<<obj.m_data<<endl;
		if(m_size == MessageQueue_Length)
		{
			//PrintMessageQueue();
			return MQ_FULL;
		}
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
		{
			PrintMessageQueue();
			return MQ_EMPTY;
		}
		else
		{
			obj = m_data[m_front];
			--m_size;
			if(m_size == 0)
				m_front = m_rear = -1;
			else
				m_front = (++m_front) % MessageQueue_Length;				
		}

		cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue Pop(), data = "<<obj.m_data<<endl;
		return MQ_OP_SUCCESS;
	}


	void PrintMessageQueue()
	{
		cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] MessageQueue:m_front="<<m_front<<",m_rear="<<m_rear<<",m_size="<<m_size<<endl;
	}

};

HANDLE g_FileMappigObject = NULL;
messageQueue *g_pMessageQueueBufferhandle = NULL;

HANDLE g_IsItEmptySem = NULL; 
HANDLE g_IsItFullSem = NULL; 
HANDLE g_MessageQueueMutex = NULL; 


#define WRITER_THREADS 5
HANDLE threads[WRITER_THREADS] = {NULL, NULL, NULL, NULL, NULL};
int threadsData[WRITER_THREADS] = {1,2,3,4,5};
#define EOP 99999

#define ITEMS_TO_PRODUCE 20
//===========================================================================================
void CreateWriterThreads();
void CreateSharedMemoryResource();
DWORD WINAPI ProducerFunc(LPVOID param);
void DeleteSharedMemoryResource();

//===================================================================================

void main()
{
	cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Program Started"<<endl;

	CreateSharedMemoryResource();

	CreateWriterThreads();

	DeleteSharedMemoryResource();
	cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Program Finished"<<endl;

}
//=====================================
DWORD WINAPI ProducerFunc(LPVOID param)
{
	int threadNo = * ((int*)param);
	cout<<"\n[Producer:"<<GetCurrentThreadId() <<"] Producer Thread Started threadNo="<<threadNo<<endl;
	int count = 0;
	for (; count < ITEMS_TO_PRODUCE ; ++count)
	{
		//cout<<"\n[Producer:"<<threadNo<<"]-count="<<count<<endl;
		DWORD result = WaitForSingleObject(g_IsItEmptySem , INFINITE);	//initial value is 16 => 15
		if(result == WAIT_OBJECT_0)
		{
			//cout<<"\n[Producer:"<<threadNo<<"]-got g_IsItEmptySem"<<endl;
			result = WaitForSingleObject( g_MessageQueueMutex, INFINITE);
			if(result == WAIT_OBJECT_0)
			{
				//cout<<"\n[Producer:"<<threadNo<<"]-got g_MessageQueueMutex"<<endl;
				int data = ++g_pMessageQueueBufferhandle->m_count;
				if(count >= ITEMS_TO_PRODUCE-2)
					data = EOP;
				int result = g_pMessageQueueBufferhandle->Push(messageQueue::Data(data));
				ReleaseMutex(g_MessageQueueMutex);

				if( MQ_FULL == result )
				{
					cout<<"\nERROR: [Producer:"<<GetCurrentThreadId() <<"] Producer Thread -MessageQueueIsFull"<<endl;
					g_pMessageQueueBufferhandle->PrintMessageQueue();
					
				}
				else
				{
					cout<<"\n: [Producer:"<<GetCurrentThreadId() <<"] Producer Thread -signal-g_IsItFullSem"<<endl;
					ReleaseSemaphore(g_IsItFullSem , 1 , NULL);	//initial value is 0  -> 1, 
				}	
				if(data == EOP)
					break;
			}			
		}		
	}
	cout<<"\n[Producer:"<<GetCurrentThreadId() <<"] Producer Thread Exiting"<<endl;
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
void CreateWriterThreads()
{
	for(int i=0 ; i <WRITER_THREADS  ; ++i)
	{
		threads[ i ] = CreateThread(NULL,0,ProducerFunc,&threadsData[i],0,NULL);
	}
	WaitForMultipleObjects(WRITER_THREADS,threads,TRUE,INFINITE);

	for(int i=0 ; i <WRITER_THREADS  ; ++i)
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
		cout<<"\nERROR : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create CreateFileMapping()= "<<SharedMemoryName <<endl;
		return;
	}
	else if(ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout<<"\nWARNING: [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Attaching to existing CreateFileMapping()= "<<SharedMemoryName <<", g_FileMappigObject= "<<g_FileMappigObject <<endl;
		isExistingMQ = true;
	}
	else
	{
		cout<<"\nWARNING: [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Successfully CreateFileMapping()= "<<SharedMemoryName<<", g_FileMappigObject= "<<g_FileMappigObject <<endl;
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
		cout<<"\nERROR : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create MapViewOfFile()= "<<SharedMemoryName <<endl;
		CloseHandle(g_FileMappigObject);
		return;
	}
	else
	{
		cout<<"\n: [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Successfully MapViewOfFile()= "<<SharedMemoryName <<",g_pMessageQueueBufferhandle="<<g_pMessageQueueBufferhandle<<", pbuffer="<<pbuffer<<endl;
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
	//#define SharedMemoryName_Empty "ProducerConsumer-MessageQueue-AccrossTheProcess_Empty"
	g_IsItEmptySem = CreateSemaphoreA(NULL,MessageQueue_Length,MessageQueue_Length,SharedMemoryName_Empty); 
	if(g_IsItEmptySem == NULL)
	{
		cout<<"\nERROR : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_EmptySem= "<<SharedMemoryName_Empty <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_EmptySem= "<<SharedMemoryName_Empty <<", = "<<g_IsItEmptySem<<endl;
	}
	else
	{
		cout<<"\n : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_EmptySem= "<<SharedMemoryName_Empty <<", = "<<g_IsItEmptySem<<endl;
	}
	//================================================================
	//#define SharedMemoryName_Full "ProducerConsumer-MessageQueue-AccrossTheProcess_Full"
	g_IsItFullSem = CreateSemaphoreA( NULL, 0, MessageQueue_Length, SharedMemoryName_Full); 
	if(g_IsItFullSem == NULL)
	{
		cout<<"\nERROR : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_FullSem= "<<SharedMemoryName_Full <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_FullSem= "<<SharedMemoryName_Full <<", = "<<g_IsItFullSem<<endl;
	}
	else
	{
		cout<<"\n : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_FullSem= "<<SharedMemoryName_Full <<", = "<<g_IsItFullSem<<endl;
	}
	//================================================================
	//#define SharedMemoryName_Mutex "ProducerConsumer-MessageQueue-AccrossTheProcess_Mutex"
	g_MessageQueueMutex = CreateMutexA(NULL,false,SharedMemoryName_Mutex); 
	if(g_MessageQueueMutex == NULL)
	{
		cout<<"\nERROR : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] Unable to create g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<endl;
	}
	else if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout<<"\nWARNING : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] attach to exsiting g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<", = "<<g_MessageQueueMutex<<endl;
	}
	else
	{
		cout<<"\n : [Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] created new g_MessageQueueMutex= "<<SharedMemoryName_Mutex <<", = "<<g_MessageQueueMutex<<endl;
	}

	cout<<"\n[Producer:"<<GetCurrentProcessId()<<":"<<GetCurrentThreadId() <<"] SharedMemory resource created successfully"<<endl;
}
void DeleteSharedMemoryResource()
{
	CloseHandle(g_IsItEmptySem); 
	CloseHandle(g_IsItFullSem); 
	CloseHandle(g_MessageQueueMutex); 

	UnmapViewOfFile(g_pMessageQueueBufferhandle);
	CloseHandle(g_FileMappigObject); 
}