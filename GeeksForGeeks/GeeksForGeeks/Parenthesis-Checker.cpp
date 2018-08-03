#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
struct Node
{
    char data;
    Node* next;
    Node (char ch , Node* ne): data(ch),next(ne){}
};

void AddNodeAtStart( Node*& Head ,char ch)
{
    Head = new Node(ch,Head);
    //cout<<"\n node Added : "<< ch <<endl;
}
bool GetNodeFromStart( Node*& Head ,char ch)
{
    if(Head != NULL)
    {
        //cout<<"\n Head: "<< Head->data <<" :  ch == "<< ch <<endl;
        if( Head->data == ch )
        {
            Node* toDelete = Head;
            Head = Head->next;
            delete toDelete;
            return true;
        }
    }
    return false;
}
void DeleteAll(Node*& Head)
{
    while(Head != NULL)
    {
        Node* toDelete = Head;
        Head = Head->next;
        delete toDelete;
    }
}

int main() 
{
    int NosToRead = 0;
    cin>> NosToRead;
	cout<<endl;
    if(NosToRead > 0)
    {        
        int i =0;
        while(i++ < NosToRead)
        {
            char expr[256] = {0};
            cin>>expr;
            cout<< "expr = "<<expr;
            int len = strlen(expr);
            bool isok = true;

            if(len > 0)
            {
                struct Node* Head = NULL;
                for( int j = 0; j< len ; ++j )
                {
                    
                    if( (expr[j] == '{') || (expr[j] == '[') || (expr[j] == '(') )
                    {
                        AddNodeAtStart(Head , expr[j]);
                    }
                    else
                    {
                        switch (expr[j])
                        {
                            case '}':
                                isok = GetNodeFromStart(Head, '{');
                            break;
                            case ')':
                                isok = GetNodeFromStart(Head, '(');
                            break;
                            case ']':
                                isok = GetNodeFromStart(Head, '[');
                            break;
                        }
                        if(isok == false)
                        {
                            cout<<"\tnot balanced"<<endl;
                            DeleteAll(Head);
                            break;
                        }
                    }
                }
				if(Head != NULL)
                {
                    cout<<"\tnot balanced"<<endl;
                    DeleteAll(Head);
					isok = false;
                }
            }
            if(isok == true)
                cout<<"\tbalanced"<<endl;
        }
    }
    
	
	return 0;
}