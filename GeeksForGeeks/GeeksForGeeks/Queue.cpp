#include <iostream>
using namespace std;
//=============================================================================================
//TO OD 

//=============================================================================================

//=======================================================
//=======================================================
void BasicQueueOp();


//=======================================================
void main()
{
	cout<<"\n Proram started"<<endl;
	BasicQueueOp();
	cout<<"\n Proram ended"<<endl;

}

//=======================================================

//=======================================================
//=======================================================
struct QueueArray
{
	int rear;	//	insert into back 
	int front;	//	remove from front
	int capacity;
	int* arr;
	enum QueueOPResult
	{
		QueueOPSuccess = 0 ,
		QueueEmpty = INT_MIN,
		QueueFull = INT_MAX
	};

	QueueArray(int size ): rear(-1), front(-1),capacity(size), arr(new int[size])
	{cout<<"\n QueueArray::QueueArray() created"<<endl;}

	~QueueArray()
	{cout<<"\n QueueArray::~QueueArray() destroyed"<<endl;delete arr; }


	int Enqueue(int val)
	{
		int result = val;
		if(  ( (front == 0)  && ( (rear+1) == capacity) )// queue is full
		  ||  (front == rear+1) )
		{
			cout<<"\n Queue is Full"<<endl;
			result = QueueFull;
		}
		else
		{
			if(front == -1)		//first element
				arr[++front] = val, rear = front;
			else    //  put in rear and increment the rear and make it circular
			{
				rear = (rear+1) %capacity;
				arr[rear] = val;
			}
		}	
		return result;
	}

	int Dequeue()
	{
		int val = QueueEmpty;
		if(front == -1)	//empty queue
		{
			cout<<"\n Queue is Empty"<<endl;
		}
		else
		{
			val = arr[front];
			//cout<<"\n Dequeue val = "<<val <<endl;
			if(front == rear)	//only one element
				front = rear = -1;
			else
				front = (front+1) % capacity;
		}
		return val;
	}
};

void BasicQueueOp()
{
	cout<<"\n BasicQueueOp() started"<<endl;

	QueueArray Qp(10);
	for (int i=0;i<11;++i)
		Qp.Enqueue(i+20);

	cout<<"\n Elements in Queue are: ";
	for (int i=0;i<11;++i)
		cout<<" -> "<<Qp.Dequeue();
	//========================================

	Qp.Enqueue(10);
	Qp.Enqueue(20);
	Qp.Enqueue(30);
	cout<<"\n\n -> "<<Qp.Dequeue();
	cout<<" -> "<<Qp.Dequeue();
	Qp.Enqueue(40);
	Qp.Enqueue(50);
	Qp.Enqueue(60);
	Qp.Enqueue(70);
	cout<<"\n\n -> "<<Qp.Dequeue();

	Qp.Enqueue(80);
	Qp.Enqueue(90);
	cout<<"\n Elements in Queue are: ";
	for (int i=0;i<11;++i)
		cout<<" -> "<<Qp.Dequeue();

	cout<<"\n BasicQueueOp() ended"<<endl;
}


//=======================================================


