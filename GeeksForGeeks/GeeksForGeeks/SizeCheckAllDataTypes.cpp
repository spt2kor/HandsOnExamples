#include <iostream>
using namespace std;

void main()
{
	cout<<"\n Program Started"<<endl;

	cout<<"\n sizeof(int) = " <<sizeof(int)<<endl;				//	4 bytes for x64 , 
	cout<<"\n sizeof(int*) = " <<sizeof(int*)<<endl;

	cout<<"\n sizeof(float) = " <<sizeof(float)<<endl;			//	4 bytes
	cout<<"\n sizeof(float*) = " <<sizeof(float*)<<endl;

	cout<<"\n sizeof(double) = " <<sizeof(double)<<endl;		//	8 bytes
	cout<<"\n sizeof(double*) = " <<sizeof(double*)<<endl;

	cout<<"\n sizeof(long) = " <<sizeof(long)<<endl;					// 4 bytes
	cout<<"\n sizeof(long int ) = " <<sizeof(long int)<<endl;			//	4 bytes
	cout<<"\n sizeof(long long int ) = " <<sizeof(long long int)<<endl;		//8 bytes
	cout<<"\n sizeof(long long int ) = " <<sizeof(long long int)<<endl;

	cout<<"\n sizeof(long double) = " <<sizeof(long double)<<endl;		//	8 bytes
	//cout<<"\n sizeof(long long double) = " <<sizeof(long long double)<<endl;//error C2632: '__int64' followed by 'double' is illegal	


	cout<<"\n sizeof(long float) = " <<sizeof(long float)<<endl;		//	8 bytes //warning C4215: nonstandard extension used : long float

	cout<<"\n Program ended"<<endl;
}
