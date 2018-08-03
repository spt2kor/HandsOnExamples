#include <iostream>
using namespace std;
//=============================================================================================
//TO OD - https://www.geeksforgeeks.org/data-structures/linked-list/
	//11.Print the middle of a given linked list
	//13.Detect loop in a linked list
	//18. Swap nodes in a linked list without swapping data
	//19. Pairwise swap elements of a given linked list
	//21. Intersection of two Sorted Linked Lists
	//22. Intersection point of two Linked Lists.
	//23. QuickSort on Singly Linked List
	//	QuickSort on Doubly Linked List
//Find a triplet from three linked lists with sum equal to a given number
//Clone a linked list with next and random pointer | Set 1

//http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
//https://www.geeksforgeeks.org/?p=7740		-	Merge Sort for Linked Lists
//=============================================================================================
struct Node
{
	int data;
	Node* next;
	
	Node(int d =-1, Node* n=NULL): data(d),next(n){cout<<"\n NODE::NODE() created: data = "<<data<<endl;}
	~Node()		{cout<<"\n NODE::~NODE() Deleted: data = "<<data<<endl;}
};
//================
struct List
{
	Node* Head;
	List():Head(NULL){}
	~List();

	void AddAtStart(int val);
	void AddAtEnd(int val);
	void AddAfter(int key, int val);

	void Print();

	bool DeleteAtStart();
	bool DeleteAtEnd();
	bool DeleteAfter(int key);

	Node* FindData(int key);
	//Nth node from the end of a Linked List//https://www.geeksforgeeks.org/nth-node-from-the-end-of-a-linked-list/
	bool FindNthNodeFromEnd(int nth);

};

//=======================================================
void main()
{
	List aList;

	cout<<"\n Proram started"<<endl;
	aList.AddAtStart(100);
	aList.AddAtStart(200);
	aList.AddAtStart(300);

	cout<<"\n **** AddAtStart"<< endl; 
	aList.Print();


	aList.AddAtEnd(400);
	aList.AddAtEnd(500);
	aList.AddAtEnd(600);

	cout<<"\n **** AddAtEnd"<< endl; 
	aList.Print();

	aList.AddAfter(300,350);
	aList.AddAfter(400,450);
	aList.AddAfter(500,550);
	aList.AddAfter(10,11);
	cout<<"\n **** AddAfter"<< endl; 
	aList.Print();

	aList.DeleteAtStart();
	aList.DeleteAtStart();
	cout<<"\n **** DeleteAtStart"<< endl; 
	aList.Print();

	aList.DeleteAtEnd();
	aList.DeleteAtEnd();
	cout<<"\n **** DeleteAtEnd"<< endl; 
	aList.Print();

	aList.DeleteAfter(600);
	cout<<"\n **** DeleteAtAfter"<< endl; 
	aList.Print();
	
	cout<<"\n **** FindNthNodeFromEnd(4)"<< endl; 
	aList.FindNthNodeFromEnd(4);
	aList.FindNthNodeFromEnd(1);
	aList.FindNthNodeFromEnd(6);
	aList.FindNthNodeFromEnd(7);
	cout<<"\n Proram ended"<<endl;
}
//=======================================================


//https://www.geeksforgeeks.org/data-structures/linked-list/
//10. Nth node from the end of a Linked List
bool List::FindNthNodeFromEnd(int nth)
{
	cout<<"\n List::FindNthNodeFromEnd() nth = "<<nth<<endl;
	if(nth == 0)
		cout<<"\n nth value is Zero !!!"<<endl;

	if(!Head)
		cout<<"\n List is empty"<<endl;
	else
	{
		Node* last = NULL;

		int count =0;
		while ( (count < nth)  )
		{
			if(count == 0)
				last = Head;
			else
				last = last->next;

			if(last == NULL)
			{
				cout<<"\n ERROR : less elements in List size = "<<count<<", required nth = "<<nth<<endl;
				return false;
			}
			else
			{
				count++; 
			}
		}
		Node* nthfromlast = Head;
		while(last->next)
		{
			last = last->next;
			nthfromlast = nthfromlast->next;
		}

		cout<<"\n Nth element from the last: "<< nthfromlast->data<<endl;

	}
	return true;
}

List::~List()
{
	cout<<"\n List::~List() started"<<endl;
	Node* trav= Head;
	while (Head)
		trav = Head->next , delete Head, Head = trav;
	cout<<"\n List::~List() started"<<endl;
}
void List::AddAtStart(int val)
{
	//cout<<"\n List::AddAtStart() started"<<endl;
	Head = new Node(val,Head);
	//cout<<"\n List::AddAtStart() started"<<endl;
}

void List::AddAtEnd(int val)
{
	//cout<<"\n List::AddAtEnd() started"<<endl;
	if(! Head)
		Head = new Node(val);
	else
	{
		Node* trav = Head;
		while(trav->next)
			trav = trav->next;
		trav->next = new Node(val);
	}
	//cout<<"\n List::AddAtEnd() started"<<endl;
}
void List::AddAfter(int key, int val)
{
	//cout<<"\n List::AddAtAfter() started"<<endl;
	Node* keyNode = FindData(key);
	if(keyNode)
		keyNode->next = new Node(val , keyNode->next);
	else
		AddAtEnd(val);
	//cout<<"\n List::AddAtAfter() started"<<endl;
}
void List::Print()
{
	cout<<"\n List::Print() started"<<endl;
	if(!Head)
		cout<<"\n List is empty"<<endl;
	else
	{
		Node* trav = Head;
		while(trav)
			cout<<" \t -> "<<trav->data, trav = trav->next;
	}

	//cout<<"\n List::Print() started"<<endl;
}

bool List::DeleteAtStart()
{
	//cout<<"\n List::DeleteAtStart() started"<<endl;
	if(!Head)
		cout<<"\n List::DeleteAtStart():  List is Empty"<<endl;
	else if(! Head->next)
	{
		delete Head;
		Head = NULL;
	}
	else
	{
		Node* temp = Head; 
		Head = Head->next;
		delete temp;
	}
	//cout<<"\n List::DeleteAtStart() started"<<endl;
	return true;
}

bool List::DeleteAtEnd()
{
	//cout<<"\n List::DeleteAtEnd() started"<<endl;
	if(!Head )
		cout<<"\n List::DeleteAtEnd() : List is Empty"<<endl;
	if(! Head->next )
	{
		delete Head;
		Head = NULL;
	}
	else
	{
		Node* trav = Head;
		while (trav->next->next)
			trav = trav->next;
		Node* temp = trav->next;
		trav->next = NULL;
		delete temp ;
	}
	//cout<<"\n List::DeleteAtEnd() started"<<endl;
	return true;
}
bool List::DeleteAfter(int key)
{
	//cout<<"\n List::DeleteAtAfter() started"<<endl;
	//cout<<"\n List::DeleteAtAfter() started"<<endl;
	return true;
}
Node* List::FindData(int key)
{
	Node* ser = NULL;
	///cout<<"\n List::FindData() started"<<endl;
	if(Head)
	{
		Node* trav = Head;
		while(trav)
			if(trav->data == key) 
				ser = trav, trav=NULL; 
			else
				trav = trav->next;
	}
	else
		cout<<"\n List::FindData() : List is Empty"<<endl;	
	
	if(! ser)
		cout<<"\n List::FindData() : Data Not Found In List :"<<key<<endl;			


	//cout<<"\n List::FindData() started"<<endl;
	return ser;
}


