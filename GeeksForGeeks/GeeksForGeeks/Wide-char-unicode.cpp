// An example C++ program to demonstrate use of wchar_t
#include <iostream>
using namespace std;
/* 
int main()
{
    wchar_t w  = L'A';
    cout << "Wide character value:: " << w << endl ;
    cout << "Size of the wide char is:: " << sizeof(w)<<endl;
    return 0;
}
*/

int main()
{
    // char type array string
    char caname[] = "geeksforgeeks" ;
    cout << caname << endl ;
	cout << "\n Size of the char  string is:: " << sizeof(caname)<<endl;

    // wide-char type array string
    wchar_t waname[] = L"geeksforgeeks" ;
    wcout << waname << endl;
	cout << "\n Size of the wide string is:: " << sizeof(waname)<<endl;
 
	   wcout << L"The length of '" << waname
          << L"' is " << wcslen(waname) << endl;

    return 0;
}
