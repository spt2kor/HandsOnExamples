#include <iostream>
using namespace std;


//https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
struct Node
{
	int m_data;
	Node* m_left;
	Node* m_right;
	Node(int data, Node* left = nullptr, Node* right = nullptr): m_data(data), m_left(left), m_right(right)
	{
		cout<<"\n "<<__FUNCTION__<<",data="<<data<<", left:"<<m_left<<",right="<<m_right<<endl;
	}
};

struct BST 
{
	Node* m_Head;
	BST(Node* ptr = nullptr): m_Head(ptr){}
	~BST();
	void clearBST();
	bool insertNodeImpl(Node* &root, int data);
	bool insertNode(int data);
	bool deleteNode(int data);
	bool findNode(int data);
	void printInOrder();
	void printPreOrder();
	void printPostOrder();
};

void main()
{
	cout<<"\n Program Started:"<<__FILE__<<endl;
	BST aBST;
	aBST.insertNode(20);
	aBST.insertNode(40);
	aBST.insertNode(50);
	aBST.insertNode(10);
	aBST.insertNode(30);
	aBST.insertNode(33);
	aBST.insertNode(70);
	
	aBST.insertNode(20);

	aBST.printInOrder();
	aBST.printPreOrder();
	aBST.printPostOrder();

	aBST.findNode(33);
	aBST.findNode(35);

	aBST.findNode(35);

	aBST.deleteNode(33);
	aBST.deleteNode(20);
	aBST.deleteNode(100);

	aBST.printInOrder();

	cout<<"\n Program Ended"<<endl;
}
//==========================================
BST::~BST()
{
	cout<<"\n "<<__FUNCTION__<<endl;
	clearBST();
}
void BST::clearBST()
{
	cout<<"\n "<<__FUNCTION__<<endl;
}

//--------------------------------------------------------------

bool BST::insertNodeImpl(Node* &root, int data)
{
	cout<<"\n "<<__FUNCTION__<<",data="<<data<<endl;
	if(! root)
		root = new Node(data);
	else
	{
		if(data < root->m_data)
			insertNodeImpl(root->m_left,data);
		else if(root->m_data < data)
			insertNodeImpl(root->m_right,data);
		else // equal values - does not support duplicate values
			return false;			
	}
	return true;
}

bool BST::insertNode(int data)
{
	cout<<"\n "<<__FUNCTION__<<",data="<<data<<endl;
	insertNodeImpl(m_Head , data);

	return true;
}

//--------------------------------------------------------------

bool BST::deleteNode(int data)
{
	cout<<"\n "<<__FUNCTION__<<",data="<<data<<endl;
	return false;
}
bool BST::findNode(int data)
{
	cout<<"\n "<<__FUNCTION__<<",data="<<data<<endl;
	return false;
}
void BST::printInOrder()
{
	cout<<"\n "<<__FUNCTION__<<endl;
}
void BST::printPreOrder()
{
	cout<<"\n "<<__FUNCTION__<<endl;
}

void BST::printPostOrder()
{
	cout<<"\n "<<__FUNCTION__<<endl;
}











