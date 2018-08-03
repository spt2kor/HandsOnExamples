#include <iostream>
using namespace std;

class Base
{
public:
	int Fun()
	{
		cout<<"\n Base::Fun()"<<endl;
		return 2000;
	}
	virtual void Fun1()
	{
		cout<<"\n Base::Fun1()"<<endl;
	}
	virtual void Fun2()
	{
		cout<<"\n Base::Fun2()"<<endl;
	}
	virtual void Fun3()
	{
		cout<<"\n Base::Fun3()"<<endl;
	}
	virtual void Fun4()
	{
		cout<<"\n Base::Fun4()"<<endl;
	}
};
class Derived : public Base
{
public:
	void Fun2()
	{
		cout<<"\n Derived::Fun2()"<<endl;
	}
	void Fun4()
	{
		cout<<"\n Derived::Fun4()"<<endl;
	}
};
class LastDerived: public Derived
{
public:
	void Fun5()
	{
		cout<<"\n LastDerived::Fun5()"<<endl;
	}
};


class ABC
{
	int x;
public:
	int fun()
	{
		cout<<"\n ABC::Fun()"<<endl;
		return 200;
	}
};
void main()
{        	//prolog

	ABC obj;
	obj.fun();

	cout<<"\n Program started"<<endl;
	Base* bp = NULL;
	cout<<"\n ========for Derived ========="<<endl;
	bp = new Derived();
	bp->Fun();
	bp->Fun1();
	bp->Fun2();
	bp->Fun3();
	bp->Fun4();
	/*
	cout<<"\n ========for LastDerived ========="<<endl;
	bp = new LastDerived();
	bp->Fun1();
	bp->Fun2();
	bp->Fun3();
	bp->Fun4();

	decltype(bp) pp= NULL;
	unsigned long long int x = 100ull;
	cout<<"\n sizeof(x) = : "<<sizeof(x)<<endl;
	
	double d = 100.23L;
	cout<<"\n sizeof(d) = : "<<sizeof(d)<<endl;
	
	long double d1 = 100.23L;
	cout<<"\n sizeof(d1) = : "<<sizeof(d1)<<endl;
	cout<<"\n Program Ended"<<endl;*/
}//epilog