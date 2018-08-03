#include <iostream>
using namespace std;
//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-Virtual_Interface
//https://www.cse.wustl.edu/~schmidt/PDF/locking-patterns.pdf
//http://www.drdobbs.com/conversations-virtually-yours/184403760
class Base
{
	virtual void ToDo()
	{
		cout<<"\n Base::ToDo()"<<endl;
	}
	void ToDo1()
	{
		cout<<"\n Base::ToDo1()"<<endl;
	}
public:
	Base()
	{
		cout<<"\n Base::Base()"<<endl;
	}
	void ToDoHelper()			//	NVI idioms - Non virtual interface idioms
	{
		cout<<"\n Base::ToDoHelper() Start"<<endl;
		ToDo();
		cout<<"\n Base::ToDoHelper() End"<<endl;
	}
};

//class Derived: private Base
class Derived: public Base
{
	virtual void ToDo() override
	{
		cout<<"\n Derived::ToDo()"<<endl;
		//Base::ToDo(); //error base function is private hence unaccecible
	}
	/*void ToDo1()	override
	{
		cout<<"\n Derived::ToDo1()"<<endl;
	}*/
public:
	Derived()
	{
		cout<<"\n Derived::Derived()"<<endl;
		//ToDo1();
	}
};
//===========================================================
struct C1	//sizeof->1bytes
{
	enum abc{ x=20};
	void fun(){}
	void fun1(){}
	static int i;
};
int C1::i = 0;
struct C2 : public C1	//empty base optimization happens - EBO -sizeof->4bytes
{
	 int x;
};
struct C3 : public C2	//empty base optimization happens - EBO -sizeof->8bytes
{
	int y;
};
struct D1			//sizeof->1bytes
{
};
struct C4 : public C1 , public D1		//empty base optimization filed sizeof => 8bytes, 
{
	int z;
};
//===========================================================
void main()
{
	cout<<"\n Program Started"<<endl;

	Derived d;
	Base* bp = &d;		//if Deriverd: private Bbase, then error : 'type cast' : conversion from 'Derived *' to 'Base *' exists, but is inaccessible
	bp->ToDoHelper();
	
	C1 c1;
	C2 c2;
	C3 c3;
	cout<<"\n sizeof(c1) = "<<sizeof(c1)<<endl;
	cout<<"\n sizeof(c2) = "<<sizeof(c2)<<endl;
	cout<<"\n sizeof(c3) = "<<sizeof(c3)<<endl;
	D1 d1;
	C4 c4;
	cout<<"\n sizeof(d1) = "<<sizeof(d1)<<endl;
	cout<<"\n sizeof(c4) = "<<sizeof(c4)<<endl;
	cout<<"\n Program Ended"<<endl;
}
//===========================================================