#include <iostream>
using namespace std;
//=============================================================================================
//TO OD 

//=============================================================================================
//stack using array
struct Stack
{
	int size;
	int top;
	int* arr;
	//struct StackFull {};
	//struct StackEmpty {};
	enum StackOPResult
	{
		StackOPSuccess = 0 ,
		StackEmpty = INT_MIN,
		StackFull = INT_MAX
	};
	//=======================
	Stack(int size) : size(size) , top(-1) , arr(new int[size])
	{cout<<"\n STACK::STACK() created"<<endl;}

	~Stack() 
	{cout<<"\n STACK::~STACK() destroyed"<<endl; delete[] arr;}

	bool IsEmpty()
	{
		return (top  == -1) ;
	}
	//void Push(int val) throw(StackFull)
	StackOPResult Push(int val) 
	{
		if(top+1 < size)
		{
			arr[++top] = val;
		}
		else //full
		{
			cout<<"\n ERROR :Full Stack unable to Push: "<< val<<endl;
			return StackFull;
		}
		return StackOPSuccess;
	}

	//int Top() throw(StackEmpty)
	int Top() 
	{
		if(top == -1) 
			return StackEmpty;
			//throw StackEmpty() ;  
		return arr[top];
	}

	//int Pop() throw(StackEmpty)
	int Pop() 
	{ 
		if(top == -1) 
		{
			cout<<"\n ERROR :Empty Stack unable to Pop: "<<endl;
			return StackEmpty;
		}
		else
		{
			int val = arr[top--];
			//cout<<"\n Poped element from Stack is : "<<val<<endl;
			return val;
		}
	}

	void Print()
	{
		cout<<"\n Stack Elements are : ";
		for(int i=0;i<=top;++i)
			cout<<" -> "<<arr[i];
		cout<<endl;
	}
};
//=======================================================
//=======================================================
void ImplementQueueUsingStack();
void BasicStackOp();
void BasicStackOpUsingLinkList();

//=======================================================
void main()
{
	cout<<"\n Proram started"<<endl;
	//BasicStackOp();
	//ImplementQueueUsingStack();
	BasicStackOpUsingLinkList();
	cout<<"\n Proram ended"<<endl;

}

//=======================================================
//stack using array
struct StackList
{
	struct Node	{
		int data;
		Node* next;
		Node(int val , Node* next):data(val), next(next){}
	};

	Node* head;

	enum StackOPResult
	{
		StackOPSuccess = 0 ,
		StackEmpty = INT_MIN,
		StackFull = INT_MAX
	};
	//=======================
	StackList() : head(NULL)
	{cout<<"\n StackList::StackList() created"<<endl;}

	~StackList() 
	{
		cout<<"\n StackList::~StackList() destroyed"<<endl; 
		Node* temp = head;
		while (head)
		{	temp = head; head = head->next; delete temp;	}
	}

	bool IsEmpty()
	{
		return (! head) ;
	}
	StackOPResult Push(int val) 
	{
		head = new Node(val , head); //add at front
		return StackOPSuccess;
	}

	int Top() 	{
		if(! head) 
			return StackEmpty;
		return head->data;
	}

	int Pop() 	{ 
		if(! head) 	{
			cout<<"\n ERROR :Empty Stack unable to Pop: "<<endl;
			return StackEmpty;
		}
		else {
			Node* temp = head;
			head = head->next;
			int val = temp->data;
			cout<<"\n Poped element from Stack is : "<<temp->data<<endl;
			delete temp;
			return val;
		}
	}

	void Print() {
		if(! head)
			cout<<"\n Error : Stack is empty"<<endl;
		Node* temp = head;
		cout<<"\n Stack Elements are : ";
		while (temp)	{
			cout<<" -> "<<temp->data; temp = temp->next;
		}
		cout<<endl;
	}
};

//=======================================================
void BasicStackOpUsingLinkList()
{
	cout<<"\n BasicStackOpUsingLinkList() started"<<endl;
	StackList s;
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Push(40);

	s.Print();

	int d = s.Pop();
	d = s.Pop();
	d = s.Pop();
	s.Print();
	d = s.Pop();
	d = s.Pop();
	d = s.Pop();
	for(int j=0;j<30;++j)
		s.Push(j);
	s.Print();
	cout<<"\n BasicStackOpUsingLinkList() started"<<endl;
}

//=======================================================
//=======================================================
struct Queue
{
	Stack *rear;	//	insert into back 
	Stack *front;	//	remove from front
	Queue(int size ): rear(new Stack(size)), front(new Stack(size))
	{cout<<"\n Queue::Queue() created"<<endl;}

	~Queue()
	{cout<<"\n Queue::~Queue() destroyed"<<endl;delete rear; delete front;}

	int Enqueue(int val)
	{
		return rear->Push(val);
	}

	int Dequeue()
	{
		if(front->IsEmpty())
		{
			while (! rear->IsEmpty())
				front->Push(rear->Pop());
		}
		return front->Pop();
	}
};

void ImplementQueueUsingStack()
{
	cout<<"\n ImplementQueueUsingStack() started"<<endl;

	Queue Qp(10);
	for (int i=0;i<11;++i)
		Qp.Enqueue(i+20);

	cout<<"\n Elements in Queue are: ";
	for (int i=0;i<11;++i)
		cout<<" -> "<<Qp.Dequeue();
	//========================================

	Qp.Enqueue(10);
	Qp.Enqueue(20);
	Qp.Enqueue(30);
	cout<<" -> "<<Qp.Dequeue();
	cout<<" -> "<<Qp.Dequeue();
	Qp.Enqueue(40);
	Qp.Enqueue(50);
	Qp.Enqueue(60);
	Qp.Enqueue(70);
	cout<<" -> "<<Qp.Dequeue();

	Qp.Enqueue(80);
	Qp.Enqueue(90);
	cout<<"\n Elements in Queue are: ";
	for (int i=0;i<11;++i)
		cout<<" -> "<<Qp.Dequeue();

	cout<<"\n ImplementQueueUsingStack() ended"<<endl;
}


//=======================================================



void BasicStackOp()
{
	cout<<"\n BasicStackOp() started"<<endl;

	Stack s(20);
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Push(40);

	s.Print();

	int d = s.Pop();
	d = s.Pop();
	d = s.Pop();
	s.Print();
	d = s.Pop();
	d = s.Pop();
	d = s.Pop();
	for(int j=0;j<30;++j)
		s.Push(j);
	
	cout<<"\n BasicStackOp() ended"<<endl;
}
