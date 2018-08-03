#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;

void reverseString(char* start, char* end)
{
	while ( start != end )
	{
		char temp = *start;
		*start = *end;
		*end = temp;

		if(start == (end-1))
			return;

		++start;
		--end;
	}
}

int main() 
{
    int NosToRead = 0;
    cin>> NosToRead;

    if(NosToRead > 0)
    {        
        int i =0;
        while(i++ < NosToRead)
        {
            string str;
            char expr[2001] = {0};
            getline(cin>>std::ws,str);
            strcpy(expr,str.c_str()) ;
            
            cout<< "\n expr = "<<expr <<endl;
			int len = strlen(expr);
            if(len > 0)
            {
				char* start = expr, *end = expr+len-1;
				//remove space from start and end
				while (*start == ' ')
						++start;
				while (*end == ' ')
						--end;

				reverseString(start, end);	//reverse complete sentence
				cout<< "\n mid expr = "<<expr <<endl;
				char* mid = start;

                cout<< "\nstart="<<*start<<",mid="<<*mid<<",end="<<*end <<endl;
				//==================================word reverse
				while( start < end)
				{
				    cout<< "\n###start="<<*start<<",mid="<<*mid<<",end="<<*end <<endl;
					while (*start == '.')
							++start;
					mid = start+1;
					
					while( (*mid != '.') && (mid!=end) )
						++mid;

					if(mid==end)
						reverseString(start, mid);
					else
						reverseString(start, mid-1);
                    
                    cout<< "\n Intermidiate expr : "<<expr <<endl;
					start = mid + 1;
				}
            }
			cout<< "\n Final expr : "<<expr <<endl;
            //cout<< expr <<endl;
        }
    }
    
	
	return 0;
}