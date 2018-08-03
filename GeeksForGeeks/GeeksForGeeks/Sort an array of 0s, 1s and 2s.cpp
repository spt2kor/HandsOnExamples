#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;

#pragma startup test_start
#pragma exit test_end


void swap(int arr[], int i, int j)
{
	if(i != j)
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;	
	}
}

void test_start()
{
	cout<<"\n\n test_start()"<<endl<<endl;
}
void test_end()
{
	cout<<"\n\n test_end()"<<endl<<endl;


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
			int arr[100] = {0};

			int count = 0;
            cin>>count;
            
            if(count > 0)
            {
				for (int i =0; i<count; ++i)
					cin>>arr[i];
				cout<<"\n Initial array content : ";
				for (int i =0; i<count; ++i)
					cout<<arr[i] <<"\t ";

				// 0 2 0 2 0
				int i= 0,j = 0 ; 
				int k=count-1; 

				while( j<= k )
				{
					if(arr[j] == 0)
					{
						swap(arr, i,j);
						++i,++j;
					}
					
					if (arr[j] == 1)
						++j;

					if(arr[j] == 2)
					{
						swap(arr, j,k);
						++j,--k;
					}

				}
				cout<<"\n Finial array content : ";
				for (int i =0; i<count; ++i)
					cout<<arr[i] <<"\t ";
            }
        }
    }
    
	
	return 0;
}

/// 0 0  2 1 0 2 1 0 1 0 1 2