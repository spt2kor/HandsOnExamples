#include <iostream>
using namespace std;
 
struct emp
{
	int rollno;
	int len;
	char name[0];			//warning in C++
};

class student
{
private:
    const int roll;			//	compiler error
	//int roll;			//	ok
public:
    // constructor
    student(int r):roll(r) {}
 
    // A const function that changes roll with the help of const_cast
    void fun() const
    {
		student* s = const_cast <student*> (this) ;
        s->roll = 5;
    }
 
    int getRoll()  { return roll; }
};
 
int main(void)
{
    student s(3);
    cout << "Old roll number: " << s.getRoll() << endl;
 
    s.fun();
 
    cout << "New roll number: " << s.getRoll() << endl;
 
    return 0;
}

/*#include <iostream>
using namespace std;
 
int main(void)
{
    int a1 = 40;
    const int* b1 = &a1;
	//int* b2 = (int*)b1;			//ok

    char* c1 = (char *)(b1);
	//char* c1 = const_cast <char *> (b1); // compiler error
    *c1 = 'A';
	cout<<"\n a1="<<a1<<", *c1="<<*c1<<endl;
    return 0;
}
*/
/*
#include <iostream>
using namespace std;
 
int fun(int* ptr)
{
    *ptr = *ptr + 10;
	cout << *ptr <<endl;
    return (*ptr);
}
 
int main(void)
{
    int val = 10;
	//const int val = 10;
    const int *ptr = &val;
    int *ptr1 = const_cast <int *>(ptr);
    fun(ptr1);
    cout << val<<endl;
    return 0;
}
*/