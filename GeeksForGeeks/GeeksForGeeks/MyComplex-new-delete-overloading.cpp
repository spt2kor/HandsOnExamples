#include <iostream>
using namespace std;
//================================================================================

class Complex
{
	int x,y;
public:
	Complex(int i=0, int j=0) : x(i) , y(j)	{
		cout<<"\n Complex::Complex() , x="<<x<<", y = "<< y <<endl;
		//throw int(100); 
		//if on "Complex*ptr = new Complex()", CTOR throw exception then it calls respective operator delete(),it does not call ~Complex()
		//if on "Complex obj;", CTOR throw exception then it does not call ~Complex(),
	}
	~Complex() {
		cout<<"\n Complex::~Complex() , x="<<x<<", y = "<< y <<endl;
	}
	Complex(const Complex& c) : x(c.x) , y(c.y)	{
		cout<<"\n Complex::Complex(const Complex& c) , x="<<x<<", y = "<< y <<endl;
	}
	Complex& operator= (const Complex& c) {
		x = c.x , y = c.y;
		cout<<"\n Complex& operator= (const Complex& c) , x="<<x<<", y = "<< y <<endl;
		return *this;
	}
	//=============================================
	void SetVal(int i, int j) {
		x=i;y=j;
		cout<<"\n Complex::SetVal(int i, int j) , x="<<x<<", y = "<< y <<endl;
	}

	void Print() {
		cout<<"\n Complex::Print() , x="<<x<<", y = "<< y <<endl;
	}

	//==============================================================
	friend ostream& operator<<(ostream& out, Complex& c)
	{
		out<<" Complex, x = "<<c.x<<", y = "<<c.y<<endl;
		return out;
	}
	bool operator == (const Complex& c2) const	{
		return  (x==c2.x) && (y == c2.y);
	}
	bool operator != (const Complex& c2) const
	{
		return !(*this==c2);
	}
	bool operator < (const Complex& c2)	const 
	{
		return  (x < c2.x) && (y < c2.y);
	}
	bool operator > (const Complex& c2) const 
	{
		return  (c2 < *this );
	}
	//========================================================================
	//operator new called as placement new - specialiesd new for Complex class
	static void* operator new(size_t size , void* mem)	
	{ 
		cout<<"\n static void* operator new( "<<size<<" , void* mem)"<<endl;
		
		return mem;
	}
	//https://msdn.microsoft.com/en-us/library/cxdxz3x6.aspx?f=255&MSPPError=-2147217396			VIMP

	//if this function is missing - Compiler - Warning	1	warning C4291: 'void *Complex::operator new(size_t,void *)' : no matching operator delete found; memory will not be freed if initialization throws an exception	d:\reading_s\problem-solving-code\geeksforgeeks\geeksforgeeks\mucomplex-operatoroverloading.cpp	122	GeeksForGeeks
	//operator delete called as placement delete - specialiesd deletefor Complex class
	//// in case of exception in Complex::Complex() CTOR , it will delete object by calling : static void operator delete(void* ptr , void* mem)			-		VIMP
	// it is not called explicitly even on "delete ptr" .
	static void operator delete(void* ptr , void* mem)
	{
		cout<<"\n static void operator delete(void* ptr , void* mem)"<<endl;
	}
	//========================================================================
	//operator new- specialiesd new for Complex class
	static void* operator new(size_t size)	throw(bad_alloc)		//may throw bad_alloc exception on failure to allocate memory
	{
		cout<<"\n static void* operator new("<<size<<")"<<endl;
		//return malloc(size);// ok to do
		return ::operator new(size);	//calling global(generic) operator new in std namespace
	}
	//operator delete - specialiesd delete for Complex class, 
	//// in case of exception in Complex::Complex() CTOR , it will delete object by calling : static void operator delete(void* ptr )			-		VIMP
	//can be called explicitly as well by "delete ptr";
	static void operator delete (void* ptr)
	{
		cout<<"\n void operator delete (void* ptr)"<<endl;
		//	free(ptr);		//ok to do
		::operator delete(ptr);	//calling global(generic) operator delete in std namespace, because memory allocated by global ::operator new();
	}
	//=======================================================================
	//placement new with diff ypes of arguments - but must return memory to create the variable
	void* operator new(size_t size , int x, int y)
	{
		cout<<"\n void* operator new(size_t "<<size <<" , "<< x <<" , "<<y<<" )"<<endl;
		return malloc(size);
	}
	void operator delete(void* mem, int x, int y)
	{
		cout<<"\n void operator delete(void* mem, "<< x <<" , "<<y<<" )"<<endl;
		free(mem);
	}
	//=======================================================================
	//http://www.cplusplus.com/reference/new/operator%20new/
	void* operator new (size_t size , const nothrow_t& noth)		//will not throw bad_alloc , but return NULL, in case of failure to allocae memory
	{
		cout<<"\n void* operator new(size_t "<<size <<", const nothrow_t& noth)"<<endl;
		return malloc(size);
	}
	//http://www.cplusplus.com/reference/new/operator%20delete/	
	static void operator delete(void* mem , const nothrow_t& not)	//called in case of CTOR failure
	{
		cout<<"\n void* operator new(void* mem , const nothrow_t& noth)"<<endl;
		free(mem);
	}

	//=======================================================================
	static void* operator new[](size_t size)
	{
		cout<<"\n void* operator new[](size_t :"<<size <<")"<<endl;
		return malloc(size);
	}
	static void operator delete[](void* ptr)
	{
		cout<<"\n void operator delete[](ptr :"<<ptr<<")"<<endl;
		free(ptr);
	}
	//=======================================================================
	static void* operator new[](size_t size, const nothrow_t& not)
	{
		cout<<"\n void* operator new[](size_t :"<<size <<",  const nothrow_t& not)"<<endl;
		return malloc(size);
	}
	static void operator delete[](void* ptr, const nothrow_t& not)
	{
		cout<<"\n void operator delete[](ptr :"<<ptr<<" , const nothrow_t& not)"<<endl;
		free(ptr);
	}
	//=======================================================================
	static void* operator new[](size_t size, void* ptr)
	{
		cout<<"\n void* operator new[](size_t :"<<size <<",  ptr : "<<ptr<<" )"<<endl;
		return ptr;
	}
	static void operator delete[](void* ptr, void* mem)
	{
		cout<<"\n void operator delete[](ptr :"<<ptr<<" , mem : " << mem  <<" )"<<endl;
		;
	}
//=======================================================================
};

//http://www.drdobbs.com/cpp/calling-constructors-with-placement-new/232901023
/*
References
Saks, Dan. "Throw and catch," ESD, May, 2007.
		https://www.embedded.com/electronics-blogs/programming-pointers/4026038/Throw-and-catch
Saks, Dan. "Function Name Overloading," Embedded Systems Programming, May 1999.
Bjarne Stroustrup. The Design and Evolution of C++. Addison-Wesley, 1994.
*/
void main()
{
try
{

	cout<<"\n Program Started"<<endl;
	
	//Complex c1(100,200);
	//cout<<"\n ********* c1 = "<<c1<<endl;
	cout<<"\n-----------------------------"<<endl;
	/*
	Complex c2(100,200);
	//cout<<"\n ********* c2 = "<<c2<<endl;
	cout<<"\n-----------------------------"<<endl;
	cout<<"\n (c1 == c2) ==>"<< ( (c1 == c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n (c1 != c2) ==>"<< ( (c1 != c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n (c1 < c2) ==>"<< ( (c1 < c2)?"TRUE":"FALSE" ) <<endl; 
	
	cout<<"\n-----------------------------"<<endl;
	c2.SetVal(20,30);
	cout<<"\n-----------------------------"<<endl;
	cout<<"\n (c1 == c2) ==>"<< ( (c1 == c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n (c1 != c2) ==>"<< ( (c1 != c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n (c1 < c2) ==>"<< ( (c1 < c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n (c1 > c2) ==>"<< ( (c1 > c2)?"TRUE":"FALSE" ) <<endl; 
	cout<<"\n-----------------------------"<<endl;
	cout<<"\n-----------------------------"<<endl;
	*/
	//Complex* ptr1 = new Complex(22,33);
	//delete ptr1;

	cout<<"\n-----------------------------"<<endl;
	/*void* mem = malloc(sizeof(Complex));
	Complex* ptr2 = new(mem) Complex(22,33);		//	call placement new() then call CTOR()
					//calls Complex::Complex() , if throws exception it calls
					// in case of exception calls : static void operator delete(void* ptr , void* mem)			-		VIMP
	//delete ptr1;		//working	- but dont call explicitly because its allocated by malloc()
	ptr2->~Complex();	//	need to call DTOR() explicitly
	
	free(mem);		//must free explicitly
	*/
	cout<<"\n-----------------------------"<<endl;
	/*Complex* ptr3 = new(20,40) Complex(22,33);		//	call placement new() then call CTOR()
					//calls Complex::Complex() , if throws exception it calls
					// in case of exception calls : static void operator delete(void* ptr , void* mem)			-		VIMP
	//delete ptr1;		//working	- but dont call explicitly because its allocated by malloc()
	ptr3->~Complex();	//	need to call DTOR() explicitly
	
	//Complex::operator delete(ptr3,20,30);	//can call manually -works - but not recommonded practice.
	delete ptr3; // calls static void operator delete (void* ptr) 
	*/

	cout<<"\n-----------------------------"<<endl;
	//Complex* ptr4 = new(nothrow) Complex(44,55);
	//delete ptr4;		//canno call delete(nothrow) version explicitly
	cout<<"\n-----------------------------"<<endl;

	/*Complex* arr1 = new Complex[3];
	arr1[0].Print();
	delete[] arr1;*/
	cout<<"\n-----------------------------"<<endl;

	/*Complex* arr2 = new(nothrow) Complex[3];
	arr2[0].Print();
	delete[] arr2;*/
	cout<<"\n-----------------------------"<<endl;
	/*void * mem3 = malloc(sizeof(Complex)*3);
	Complex* arr3 = new(mem3) Complex[3];
	arr3[0].Print();
	//delete[] arr3;
	free(mem3);*/
}//end of try block			
catch(...)
{
	cout<<"\n @@@@@@@ caught Exception here @@@@@@ "<<endl;	
}
	cout<<"\n-----------------------------"<<endl;
	cout<<"\n Program ended"<<endl;	
}


//=============================================================================


