#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
	Node(int val , Node* next):data(val),next(next){}
};

void PrintArr(int arr[] , int size);
void PrintList(Node* head);
//========================================================

struct GraphList
{
	int noOfVertex;
	Node** arrEdges;
	
	GraphList(int noOfVertex);
	~GraphList();
	void AddEdge(int from , int to);
	void PrintGraph();

	void DFSHelperExplicitStack(int key , int* visited);  //iterative

	void DFSHelper(int key , int* visited);		//recursive
	void PrintDFS(int key, bool recurs = true);

	void BFSHelper(int key , int* visited);		//recursive
	void PrintBFS(int key);
	
};

struct GraphMatrix
{
	int noOfVertex;
	int* gMatrix;
	
	GraphMatrix(int noOfVertex);
	~GraphMatrix();
	void AddEdge(int from , int to);

	void PrintGraph();

	void DFSHelper(int key , int* visited);				//recursive
	void DFSHelperExplicitStack(int key , int* visited);  //iterative

	void PrintDFS(int key, bool recurs = true);

	void BFSHelper(int key , int* visited);		 // iterative
	void PrintBFS(int key);	
};

//=============================================================
void main()
{
	cout<<"\n Proram started"<<endl;
	cout<<"\n ********************************* "<<endl;

	//GraphList gpl(5);
	GraphMatrix gpl(5);
	gpl.AddEdge(0,1);
	gpl.AddEdge(0,2);
	gpl.AddEdge(1,2);
	gpl.AddEdge(1,3);
	gpl.AddEdge(2,3);
	gpl.AddEdge(2,4);
	gpl.AddEdge(3,4);

	cout<<"\n\n Graph contents are : "<<endl;
	gpl.PrintGraph();	


	//gpl.PrintDFS(0);
	gpl.PrintDFS(0 , false);
	gpl.PrintDFS(0);
	/*gpl.PrintDFS(1);
	gpl.PrintDFS(1 , false);
	gpl.PrintDFS(2);
	gpl.PrintDFS(2 , false);
	gpl.PrintDFS(3);
	gpl.PrintDFS(3 , false);
	gpl.PrintDFS(4);
	gpl.PrintDFS(4 , false);
	*/
	gpl.PrintBFS(2);
	cout<<"\n Proram ended"<<endl;
}

//=============================================================

void GraphMatrix::DFSHelperExplicitStack(int key , int* visited)
{
	bool *addedToStack = new bool[noOfVertex];
	for(int i = 0 ; i < noOfVertex ; ++i)
		addedToStack[i] = 0;

	Node* head = new Node(key,NULL);
	addedToStack[key] = 1;
	while(head != NULL)
	{
		Node* top = head; head = head-> next;  //pop the top most/front node
		key = top->data;
		if(visited[key] == 0)
		{
			visited[key] = 1;
			cout<< key <<" -> " ;
			for( int i = 0 ; i< noOfVertex ; ++i)
			{
				//cout<<"\n key = "<<key<<", i = "<<i<<", gMatrix[key* noOfVertex + i] = "<<gMatrix[key* noOfVertex + i]<<", visited[i] = "<<visited[i]<<endl;
				if( ( addedToStack[i] == 0) && ( gMatrix[key* noOfVertex + i] == 1) )
				{
					head = new Node(i , head);  //push node to fron / top of stack
					//PrintList(head);
					addedToStack[i] = 1;
				}
			}
		}
		delete top;
	};
}

void GraphMatrix::DFSHelper(int key , int* visited)
{
	visited[key] = 1;
	cout<< key <<" -> " ;
	for( int i = 0 ; i< noOfVertex ; ++i)
	{
		//cout<<"\n key = "<<key<<", i = "<<i<<", gMatrix[key* noOfVertex + i] = "<<gMatrix[key* noOfVertex + i]<<", visited[i] = "<<visited[i]<<endl;
		if( ( visited[i] == 0) && ( gMatrix[key* noOfVertex + i] == 1) )
		{
			DFSHelper( i , visited); //using stack here to iterate implicitly
		}
	}
}

void GraphMatrix::PrintDFS( int key , bool recurs)
{
	int *visited = new int[noOfVertex];
	for(int i = 0;i<noOfVertex ; ++i)
		visited[i] = 0;

	if(recurs)
	{
		cout<<"\n GraphMatrix::PrintDFS() Recursive ::key = "<<key<<endl;
		DFSHelper(key , visited);
	}
	else
	{
		cout<<"\n GraphMatrix::PrintDFS() Iterative ::key = "<<key<<endl;
		DFSHelperExplicitStack(key , visited);
	}
	
}


//====================================================================================

void GraphMatrix::BFSHelper(int key , int* visited)		//iterative
{
	int* isQueuedAlready = new int[noOfVertex];
	for (int i = 0 ; i < noOfVertex ; ++i)
		isQueuedAlready[i] = 0;

	Node* rear = new Node(key , NULL); 
	rear->next = rear;			//circular link list pointing to last node and next is first node
	isQueuedAlready[key] = 1;
	while ( rear )
	{
		Node* front = rear->next;
		if(rear == rear->next ) // if only 1 node in Queue
			rear = NULL;
		else
			rear->next = rear->next->next;	

		key = front->data;
		visited[key] = 1;
		cout<<key <<" -> ";
		//===============================
		
		for( int i = 0 ; i< noOfVertex ; ++i)
		{
			//cout<<"\n key = "<<key<<", i = "<<i<<", gMatrix[key* noOfVertex + i] = "<<gMatrix[key* noOfVertex + i]<<", visited[i] = "<<visited[i]<<endl;
			if( ( isQueuedAlready[i] == 0) && ( gMatrix[key* noOfVertex + i] == 1) )
			{
				if(rear == NULL)
				{
					rear =  new Node(i , NULL); 
					rear->next = rear;			//circular link list pointing to last node and next is first node
				}
				else
				{
					rear->next = new Node(i , rear->next); //give poiner of front node to new node
					rear = rear->next;
				}
				isQueuedAlready[i] = 1;
			}
		}


		delete front;
	}
}

void GraphMatrix::PrintBFS(int key)
{
	cout<<"\n GraphList::PrintBFS() ::kay ="<<key<<endl;
	int* visited = new int[noOfVertex];
	for (int i = 0 ; i < noOfVertex ; ++i)
		visited[i] = 0;
	
	BFSHelper(key , visited);
}

GraphMatrix::GraphMatrix(int noOfVertex):noOfVertex(noOfVertex) , gMatrix(NULL)
{
	gMatrix = new int[noOfVertex * noOfVertex];
	for (int i = 0 ; i< noOfVertex*noOfVertex ; ++i)
	{
		gMatrix[i] = 0;
	}
	cout<<"\n GraphMatrix::GraphMatrix() is created"<<endl;
}

GraphMatrix::~GraphMatrix()
{
	delete[] gMatrix;
	cout<<"\n GraphMatrix::~GraphMatrix() is deleted"<<endl;
}

void GraphMatrix::AddEdge(int from , int to)
{
	if( ( 0 <= from ) && ( from < noOfVertex ))
	{
		if( ( 0 <= to ) && ( to < noOfVertex ))
		{
			gMatrix[from *noOfVertex + to ] = 1;
			gMatrix[to * noOfVertex + from] = 1;
		}
	}
}

void GraphMatrix::PrintGraph()
{
	cout<<"\n GraphMatrix is: "<<endl;
	for (int i = 0 ; i< noOfVertex ; ++i)
	{
		cout<<endl<<" [ ";
		for (int j = 0 ; j< noOfVertex ; ++j)
		{
			cout <<gMatrix[i *noOfVertex + j] << " , ";
			//cout <<gMatrix[i][j]<< " , ";
		}
		cout<<" ] ";
		
	}
}

//=============================================================
//=============================================================
//=============================================================
//=============================================================

void GraphList::DFSHelperExplicitStack(int key , int* visited)
{
	int *addedToStack = new int[noOfVertex];
	for(int i = 0 ; i < noOfVertex ; ++i)
		addedToStack[i] = 0;

	Node* head = new Node(key,NULL);
	addedToStack[key] = 1;
	while(head != NULL)
	{
		Node* top = head; head = head-> next;  //pop the top most/front node
		key = top->data;
		if(visited[key] == 0)
		{
			visited[key] = 1;
			cout<< key <<" -> " ;
			
			Node* CurrVertex = arrEdges[key];
			while(CurrVertex)
			{
				//cout<<"\n key = "<<key<<", CurrVertex->data = "<<CurrVertex->data<<", visited[CurrVertex->data] = "<<visited[CurrVertex->data]<<endl;
				if ( ( addedToStack[CurrVertex->data] == 0)  && (visited[CurrVertex->data] == 0) )
				{
					head = new Node(CurrVertex->data , head);  //push node to fron / top of stack
					//PrintList(head);
					addedToStack[CurrVertex->data] = 1;
				}
				CurrVertex = CurrVertex->next;
			}
		}
		delete top;
	};
}

void GraphList::DFSHelper(int key , int* visited)
{
	visited[key] = 1;
	cout<< key <<" -> " ;
	Node* CurrVertex = arrEdges[key];
	while(CurrVertex)
	{
		int key = CurrVertex->data;
		//cout<<"\n key = "<<key<<", i = "<<i<<", gMatrix[key* noOfVertex + i] = "<<gMatrix[key* noOfVertex + i]<<", visited[i] = "<<visited[i]<<endl;
		if( visited[key] == 0) 
		{
			DFSHelper( key , visited); //using stack here to iterate implicitly
		}
		CurrVertex = CurrVertex->next;
	}
}

void GraphList::PrintDFS(int key, bool recurs )
{
	int* visited = new int[noOfVertex];
	for (int i = 0 ; i < noOfVertex ; ++i)
		visited[i] = 0;

	if(recurs)
	{
		cout<<"\n GraphList::PrintDFS() recursive ::kay ="<<key<<endl;
		DFSHelper(key , visited);
	}
	else
	{
		cout<<"\n GraphList::PrintDFS() Iterative ::kay ="<<key<<endl;
		DFSHelperExplicitStack(key , visited);
	}

}

//====================================================================================

void GraphList::BFSHelper(int key , int* visited)		//recursive
{
	int* isQueuedAlready = new int[noOfVertex];
	for (int i = 0 ; i < noOfVertex ; ++i)
		isQueuedAlready[i] = 0;

	Node* rear = new Node(key , NULL); 
	rear->next = rear;			//circular link list pointing to last node and next is first node
	isQueuedAlready[key] = 1;
	while ( rear )
	{
		Node* front = rear->next;
		if(rear == rear->next ) // if only 1 node in Queue
			rear = NULL;
		else
			rear->next = rear->next->next;	

		key = front->data;
		visited[key] = 1;
		cout<<key <<" -> ";
		//===============================
		Node* CurrVertex = arrEdges[key];
		while(CurrVertex)
		{
			int key = CurrVertex->data;
			//cout<<"\n key = "<<key<<", i = "<<i<<", gMatrix[key* noOfVertex + i] = "<<gMatrix[key* noOfVertex + i]<<", visited[i] = "<<visited[i]<<endl;
			if( ( visited[key] == 0) && (isQueuedAlready[key] == 0) )
			{
				if(rear == NULL)
				{
					rear =  new Node(key , NULL); 
					rear->next = rear;			//circular link list pointing to last node and next is first node
				}
				else
				{
					rear->next = new Node(key , rear->next); //give poiner of front node to new node
					rear = rear->next;
				}
				isQueuedAlready[key] = 1;
			}
			CurrVertex = CurrVertex->next;
		}
		delete front;
	}
}

void GraphList::PrintBFS(int key)
{
	cout<<"\n GraphList::PrintBFS() ::kay ="<<key<<endl;
	int* visited = new int[noOfVertex];
	for (int i = 0 ; i < noOfVertex ; ++i)
		visited[i] = 0;
	
	BFSHelper(key , visited);
}

//====================================================================================
GraphList::GraphList(int Vertex):noOfVertex(Vertex) , arrEdges(new Node*[noOfVertex])
{
	for (int i = 0 ; i< noOfVertex ; ++i)
	{
		arrEdges[i] = NULL;
	}
	cout<<"\n GraphList::GraphList() is created"<<endl;
}

GraphList::~GraphList()
{
	for (int i = 0 ; i< noOfVertex ; ++i)
	{
		Node* head = arrEdges[i];
		while(head)
		{
			Node* temp = head; head = head->next;
			delete temp;
		}
	}
	delete[] arrEdges;
	cout<<"\n GraphList::~GraphList() is deleted"<<endl;
}

void GraphList::AddEdge(int from , int to)
{
	if( ( 0 <= from ) && ( from < noOfVertex ))
	{
		if( ( 0 <= to ) && ( to < noOfVertex ))
		{
			arrEdges[from] = new Node(to,arrEdges[from]);
			arrEdges[to] = new Node(from,arrEdges[to]);
		}
	}
}

void GraphList::PrintGraph()
{
	for (int i = 0 ; i< noOfVertex ; ++i)
	{
		Node* head = arrEdges[i];
		cout<<"\n Edge list of Node : "<< i <<" , is : -> ";
		while(head)
		{
			cout<<head->data<<" , ";
			head = head->next;
		}
	}
}



//=============================================================

void PrintList(Node* head)
{
	cout<<"\n List elements are: ";
	while (head)
	{
		cout<<" -> "<< head->data; 
		head = head->next;
	}
	cout<<endl;
}

//=============================================================

//=============================================================

//=============================================================