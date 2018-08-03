#include <iostream>
#include <string>
using namespace std;
 
//http://www.drdobbs.com/cpp/volatile-the-multithreaded-programmers-b/184403766			-	VIMP


class Gadget
{
public:
    void Foo() volatile
	{
		cout<<"\n Gadget::Foo()"<<endl;
	}
    void Bar()
	{
		cout<<"\n Gadget::Bar()"<<endl;
	}
    
private:
    int state_;
};


int main(void)
{
    cout<<"\n Program started"<<endl;

	Gadget regularGadget;
	volatile Gadget volatileGadget;

	volatileGadget.Foo(); // ok, volatile fun called for
                      // volatile object
 
 
	regularGadget.Foo();  // ok, volatile fun called for
						  // non-volatile object
	volatileGadget.Bar(); // error! Non-volatile function called for
						  // volatile object!
	cout<<"\n Program ended"<<endl;
    return 0;
}
