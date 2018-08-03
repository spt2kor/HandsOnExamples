#include <iostream>

using namespace std;
class String
{
				////////		TOTO DO  - Not Completed



	union {
		struct {						//NormalString
		int m_size;
		char* m_ptr;
		} ;
		struct {						//SSOptimization
		char m_arrSize;
		char m_str[23];		//24 char for word(24 leters + no '\0') , + 1 byte for size storage
		};
	};
	bool isSSOEnabled;			//occupying 4 byes of memory				///TODO

public:
	String(): m_size(0), m_ptr(NULL), isSSOEnabled(false)	{
		cout<<"\n String::String() "<<endl;
	}		

	~String()	{
		cout<<"\n String::~String() "<<endl;
		delete m_ptr;
	}
	//=================================================================================================================
	String(const char* str): m_size(0), m_ptr(NULL), isSSOEnabled(false)	{                        //String str1 = "String";
		if(str )	{
			m_size = strlen(str);
			m_ptr = new char[m_size+1];
			strcpy(m_ptr,str);
		}
		cout<<"\n String::String(const char* str) str = "<<m_ptr<<endl;
	}

	String(const char* str1, const char* str2): m_size(0), m_ptr(NULL)	{                        //String ("String" + "Hello"); //helper for return value optimization - reduced from 4=>2
		if(str1 || str2)	{
			m_size = strlen(str1) + strlen(str2);
			m_ptr = new char[m_size+1];
			strcpy(m_ptr,str1);
			strcat(m_ptr,str2);
		}
		cout<<"\n String(const char* str1, const char* str2), str = "<<m_ptr<<endl;
	}

	String(const String& str): m_size(str.m_size), m_ptr(NULL)	{            //String str1(str2);
		cout<<"\n String::String(const String& str) "<<endl;
		this->String::String(str.c_str());		
	}
	//=================================================================================================================

	String& operator = (const String& str){                        //str1 = str2;
		cout<<"\n String& operator = (const String& str) "<<endl;
		this->String::operator=(str.c_str());		
		return *this;
	}

	String& operator = (const char* str){                        //str1 = "String";
		char* x_str = NULL;
		if(str)	{
			x_str = new char [ strlen(str) + 1];
			strcpy(x_str , str);
		}
		delete m_ptr;
		m_ptr = x_str, m_size = strlen(str) , x_str = NULL;
		cout<<"\n String& operator = (const char* str) str = "<< m_ptr<<endl;
		return *this;
	}
	//=================================================================================================================

	friend ostream& operator<<(ostream& out, const String& str)	                        //cout<<str1;;
	{
		out<<str.m_ptr;
		return out;
	}
	//=================================================================================================================		
	String& operator += (const char* ptr){						  // str2 += "String";
		if(ptr) {
			m_size += strlen(ptr);
			char* x_ptr = new char[m_size +1];
			strcpy(x_ptr,m_ptr);
			strcat(x_ptr , ptr);


			delete m_ptr;
			m_ptr = x_ptr , x_ptr = NULL;
		}
		cout<<"\n String& operator += (const char* val) str = "<<m_ptr<<endl;
		return *this;
	}

	String& operator += (const String& str ){										// str2 += str1;
		cout<<"\n String& operator += (const String& str) "<<endl;
		//this->operator+=(str.c_str());
		*this += str.c_str();
		return *this;
	}
	//=================================================================================================================		
	friend String operator + (const String& first, const char* str){						  // str2 = str1 + "String";
		cout<<"\n friend String operator + (const String& first, const char* str) "<<endl;
		//return String(first).operator += (str);													//try for return value optimization - causing 4 temporary objects
		//return String( String(first) += str );													//try for return value optimization - causing 4 temporary objects
		return String(first.c_str() , str);													//try for return value optimization - reduced from 4=>2
	}

	friend String operator + (const char* str1 , const String& str2 ){						  // str2 = "String" + str1;
		cout<<"\n friend String operator + (const char* val , const String& str) "<<endl;
		//return String( String(str2) += str1 );													//try for return value optimization - causing 4 temporary objects
		return String(str1 , str2.c_str() );													//try for return value optimization - reduced from 4=>2
	}
	//=================================================================================================================		
	const char* c_str() const {
		return m_ptr;
	}

	bool empty() const {
		return (m_size==0);
	}

	int size() const {
		return m_size;
	}
	//=================================================================================================================		
	char& operator[](int index) {                //can throw OUT_OF_BOUND error
/*		static  char dummy = -1;
		if( 0 <= index && index < m_size)
			return m_ptr[index];
		else
			return dummy;*/
		cout<<"\n char& operator[](int index) "<<endl;
		return const_cast<char&>( (* static_cast<const String* const >(this))[index] );
	}

	const char& operator[](int index) const {                //can throw OUT_OF_BOUND error
	cout<<"\n const char& operator[](int index) const "<<endl;
		static  char dummy = -1;
		if( 0 <= index && index < m_size)
			return m_ptr[index];
		else
			return dummy;
	}
	//=================================================================================================================		
};

void main()
{
	cout<<"\n *********** Program started"<<endl;
	String str1;
	cout<<"size of(str1) = "<<sizeof(str1)<<endl;
	cout<<"sizeof(String) = "<<sizeof(String)<<endl;
	/*str1 = "Monday";
	cout<<"\n ***********  str1 = "<<str1<<endl;
	String str2(str1);
	cout<<"\n  *********** str2 = "<<str2<<endl;
	str2 = "Tuesday";
	cout<<"\n  *********** str2 = "<<str2<<endl;

	String str3 = str1;
	cout<<"\n  *********** str3 = "<<str3<<endl;
	str3 += str2;
	cout<<"\n  *********** str3.c_str() = "<<str3.c_str()<<endl;

	//str3 = str1+ "Days" + "Month";		//causing only 2 temp objects , reduced from 4=>2
	//cout<<"\n  *********** str3 = "<<str3<<endl;

	str3 = str1;			//trying to reduce temp object by changing the statements
	str3 += "Days" ;		// zero temp objects 4=>2=>0 
	str3 += "Month";		//
	cout<<"\n  *********** str3 = "<<str3<<endl;


	str3 = "showme" + str3;	//1 temp object
	cout<<"\n  *********** str3 = "<<str3<<endl;

	if(!str3.empty()) 
		cout<<"\n  *********** str3.c_str() = "<<str3.c_str()<<", len ="<<str3.size()<<endl;

	str3[20] = 'x';
	cout<<"\n  *********** str3 = "<<str3<<endl;

	const String str4 = str3;
	cout<<"\n  *********** str4[4] = "<<str4[4]<<endl;

	*/
	cout<<"\n  *********** Program ended"<<endl;
}