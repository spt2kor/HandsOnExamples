#include <iostream>
using namespace std;
class Base{
	char arr[1024];
public:
	//const int x = 20;		//1>TestingC++Basics.cpp(6): error C2864: 'Base::x' : only static const integral data members can be initialized within a class
	const int x ;		
	static const int z=30;		//ok to init here, no need to define outside
	static const int z1;		//if not used outside then wihout defining also its ok, but if used can cause eror
	static int z2 ;
	
	//static const float y1=30;		//1>TestingC++Basics.cpp(12): error C2864: 'Base::y1' : only static const integral data members can be initialized within a class
	static const char y2=30;		//ok
	void print() 
	{
		cout<<"\n BASE::Print(), x= "<<x<<endl;
	}

	~Base()
	{
		cout<<"\n BASE::~BASE(), x= "<<x<<endl;
	}
	/*Base& operator=(const Base& obj)
	{
		x = obj.x;						// cannot define op=() //1>TestingC++Basics.cpp(18): error C2166: l-value specifies const object
		cout<<"\n Base& operator=(const Base& obj), x= "<<x<<endl;
		return *this;
	}*/
	//Base(const Base& obj) : x(obj.x), z(40)			1>TestingC++Basics.cpp(26): error C2438: 'z' : cannot initialize static class data via constructor
	//Base(const Base& obj) : x(obj.x),z1(20)
	Base(const Base& obj) : x(obj.x)
	{
		z2 =30;
		cout<<"\n Base(const Base& obj) , x= "<<x<<endl;
	}
	Base(int y=0):x(y)							//if not init on CTOR initilization list => //1>TestingC++Basics.cpp(18): error C2166: l-value specifies const object
												//1>TestingC++Basics.cpp(26): error C2758: 'Base::x' : must be initialized in constructor base/member initializer list
	{
		cout<<"\n Base(int y=0) , x= "<<x<<endl;
	}
};
	const int Base::z1 = 200;		
	//const int Base::z1;				//	ERROR:   1>TestingC++Basics.cpp(40): error C2734: 'Base::z1' : const object must be initialized if not extern
	int Base::z2 ;
void main()
{
	cout<<"\n Program Started"<<endl;
	register int x1 = 20;
	register char c1 = 20;
	register float f2 = 20;
	register double d2 = 20;

	//register static double d3 = 20;		//1>TestingC++Basics.cpp(53): error C2159: more than one storage class specified

	register Base b3;
	Base b(20);
	b.print();
	b.print();
	cout<<Base::z;			//no need to define outside now.
	cout<<Base::z1;						//if we dont define outside the class //1>TestingC++Basics.obj : error LNK2001: unresolved external symbol "public: static int const Base::z1" (?z1@Base@@2HB)
	cout<<"\n Program Ended : "<<endl;
}
//=================================================================================
/*
class Base{
	
public:
	int x;
	virtual void print() = 0			//can give definition or omit definition both are ok
	{
		cout<<"\n BASE::Print(), x= "<<x<<endl;
	}

	virtual ~Base() = 0 ;				//must give deinition					//1>TestingC++Basics.obj : error LNK2019: unresolved external symbol "public: virtual __cdecl Base::~Base(void)" (??1Base@@UEAA@XZ) referenced in function "int `public: __cdecl Derived::Derived(int,int)'::`1'::dtor$0" (?dtor$0@?0???0Derived@@QEAA@HH@Z@4HA)
	{
		cout<<"\n BASE::~BASE(), x= "<<x<<endl;
	}
	Base& operator=(const Base& obj)
	{
		x = obj.x;
		cout<<"\n Base& operator=(const Base& obj), x= "<<x<<endl;
		return *this;
	}
	Base(const Base& obj) : x(obj.x)
	{
		cout<<"\n Base(const Base& obj) , x= "<<x<<endl;
	}
	Base(int y=0) : x(y)
	{
		cout<<"\n Base(int y=0) , x= "<<x<<endl;
	}
};

class Derived : public Base{
	
public:
	int y;
	virtual void print()
	{
		cout<<"\n Derived::Print(), y= "<<y<<endl;
	}

	~Derived()
	{
		cout<<"\n Derived::~Derived(), y= "<<y<<endl;
	}													//1>TestingC++Basics.obj : error LNK2019: unresolved external symbol "public: virtual __cdecl Base::~Base(void)" (??1Base@@UEAA@XZ) referenced in function "int `public: __cdecl Derived::Derived(int,int)'::`1'::dtor$0" (?dtor$0@?0???0Derived@@QEAA@HH@Z@4HA)
	Derived& operator=(const Derived& obj)
	{
		Base::operator=(obj);
		y = obj.y;
		cout<<"\n Derived& operator=(const Derived& obj), x= "<<x<<endl;
		return *this;
	}
	Derived(const Derived& obj) : Base(obj), y(obj.y)
	{
		cout<<"\n Derived(const Derived& obj) , y= "<<y<<endl;
	}
	Derived(int x=0,int y=0) : Base(x),y(y)
	{
		cout<<"\n int y=0(int x=0, int y=0) , y= "<<y<<endl;
	}
};
void main()
{
	cout<<"\n Program Started"<<endl;
	//Base b;						//1>TestingC++Basics.cpp(65): error C2259: 'Base' : cannot instantiate abstract class
								//1>          due to following members:
								//1>          'void Base::print(void)' : is abstract
								//1>          TestingC++Basics.cpp(8) : see declaration of 'Base::print'				
	Derived d(10,20);
	d.print();
	d.Base::print();

	cout<<"\n Program Ended"<<endl;
}*/
///////////////////////////////////////////////////////////////////////
/*
class Base{
	
public:
	int x;
	void print()
	{
		cout<<"\n BASE::Print(), x= "<<x<<endl;
	}

	~Base()
	{
		cout<<"\n BASE::~BASE(), x= "<<x<<endl;
	}
	Base& operator=(const Base& obj)
	{
		x = obj.x;
		cout<<"\n Base& operator=(const Base& obj), x= "<<x<<endl;
		return *this;
	}
	Base(const Base& obj) : x(obj.x)
	{
		cout<<"\n Base(const Base& obj) , x= "<<x<<endl;
	}
};

void main()
{
	cout<<"\n Program Started"<<endl;
	//Base b;								//Error : error C2512: 'Base' : no appropriate default constructor available	

	b.x=100;
	b.print();

	cout<<"\n Program Ended"<<endl;
}
*/