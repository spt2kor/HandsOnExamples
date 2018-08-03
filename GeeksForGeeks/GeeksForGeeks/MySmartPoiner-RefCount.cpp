#include <iostream>
using namespace std;

template <class T>
class smart_ptr
{
	//==================================================
	struct Mem{

	private:
		T* m_ptr;
		int m_count;
		Mem(const Mem& o);
		Mem& operator= (const Mem& o);

	public:
		Mem( T* ptr = NULL , int count = 1) :m_ptr(ptr) , m_count(count)	{
			cout<<"\n Mem::Mem() , count="<<m_count<<endl;
		}

		~Mem( ) {
			if(m_count <= 0)
				delete m_ptr;
		}

		int IncreaseRef()	{
			if(m_ptr)
				++m_count;
			return m_count;
		}

		int DecreseRef()	{
			if(m_ptr)	{
				if(--m_count <= 0)	{
					delete m_ptr;	m_ptr = NULL;	m_count = 0;
				}
			}
			return m_count;
		}
		
		T* get(){
			return m_ptr;
		}

		int getCount(){
			return m_count;
		}

		friend ostream& operator<<(ostream& out , Mem& m)
		{
			out<<m.m_ptr;
			return out;
		}
	} * m_mem;


	//==================================================

public:
	smart_ptr(T* ptr = NULL): m_mem(NULL) { 
		if(ptr)
			m_mem = new Mem(ptr);
		cout<<"\n smart_ptr::smart_ptr() , count="<<m_mem->getCount()<<endl;
	}

	~smart_ptr(){ 
		if(m_mem )	{
			int count = m_mem->DecreseRef();
			cout<<"\n smart_ptr::~smart_ptr(), m_count = "<<count<<endl;
			if(count <= 0)
				delete m_mem;
		}
	}
	/*
	template<typename U>
	smart_ptr(smart_ptr<U>& s): m_mem(NULL) { 
		int count = 0;			
		if(s.m_mem )	{
			m_mem = s.m_mem;
			count = m_mem->IncreaseRef();			
		}
		cout<<"\n smart_ptr::smart_ptr(smart_ptr& s) , count="<<count<<endl;
	}
	*/
	smart_ptr(smart_ptr& s): m_mem(NULL) { 
		int count = 0;			
		if(s.m_mem )	{
			m_mem = s.m_mem;
			count = m_mem->IncreaseRef();			
		}
		cout<<"\n smart_ptr::smart_ptr(smart_ptr& s) , count="<<count<<endl;
	}

	smart_ptr& operator=(smart_ptr& s) { 
		int count = 0;
		if(m_mem )	{
			count = m_mem->DecreseRef();
			cout<<"\n smart_ptr& operator=(smart_ptr& s) , old count="<<count<<endl;
			if(count <=0)
				delete m_mem;
		}

		if(s.m_mem )	{
			m_mem = s.m_mem;
			count = m_mem->IncreaseRef();
		}
		cout<<"\n smart_ptr& operator=(smart_ptr& s) , new count="<<count<<endl;
		return *this;
	}

	//==============================================================

	T* operator -> ()	{
		return m_mem->get();
	}

	T& operator* ()	{
		return *m_mem->get();
	}


};
//================================================================================



//================================================================================




//================================================================================

class Complex
{
	int x,y;
public:
	Complex(int i=0, int j=0) : x(i) , y(j)	{
		cout<<"\n Complex::Complex() , x="<<x<<", y = "<< y <<endl;
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
	
	void Print() {
		cout<<"\n Complex::Print() , x="<<x<<", y = "<< y <<endl;
	}

	friend ostream& operator<<(ostream& out, Complex& c)
	{
		out<<" Complex, x = "<<c.x<<", y = "<<c.y<<endl;
		return out;
	}
};


void main()
{

	cout<<"\n Program Started"<<endl;
	smart_ptr<int> si = new int(100);
	cout<<" \n *********** si = "<< *si<<endl;
	
	*si = 2000;
	cout<<" \n *********** si = "<< *si<<endl;

	//========================================

	smart_ptr<int> si2(si);
	cout<<" \n *********** si2 = "<< *si2<<endl;

	//smart_ptr<long> sl(si);
	//cout<<" \n si = "<< *sl<<endl;
	{
		smart_ptr<Complex> sc1(new Complex(10,20));
		cout<<" \n *********** sc1 = "<< *sc1<<endl;
		sc1->Print();

		smart_ptr<Complex> sc2(sc1);
		*sc2 = Complex(1000,2000);
		cout<<" \n *********** sc2 = "<< *sc2<<endl;
		sc2->Print();
	}
	//========================================

		/*int* heap_ref = heap_object();
	*heap_ref = 10000;
	cout<< *heap_ref<<endl;

	int* stack_ref = stack_object();
	*stack_ref = 20000;
	cout<< *stack_ref<<endl;		//does not fail - work properly - output = 20000
	*/
		
	cout<<"\n Program ended"<<endl;
	
}


//=============================================================================

/*  linux kernal provided link list data structure - can have hetrogenous elements in list
//===========================================================================================
struct list_head{
 struct list_head *next, *prev;
 };

struct point2D{
 int x,y;
 struct list_head list;
};

#define list_entry(ptr, type, member)  ( (type *)( (char *)(ptr)-(unsigned long)(&( (type *) 0 )->member) ) )
/*
void list_entry_(list_head* ptr, point2D type, int member)  
	{
	(		(type *)	(	(char *)(ptr)	-	(unsigned long)	(&( (type *) 0 )->member)		)		)
}
//===========================================================================================
*/

//================================================================================
/*int* stack_object()
{
	int x = 30;
	return &x;
}

int* heap_object()
{
	int *x = new int(40);
	return x;
}*/

