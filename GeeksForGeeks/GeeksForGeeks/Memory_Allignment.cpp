#include <iostream>
using namespace std;


void PrintBinary(int no)
{
	int totalBits = sizeof(no) * 8;
	cout<<"\n *******  PrintBinary ("<<no<<") = ";
	for(int i = totalBits-1 ; i >= 0 ; --i)
	{
		cout<<( (no & 1<<i)? "1":"0" );
	}
	cout<<endl<<endl;
}

void main()
{
	cout<<"\n Program Started"<<endl;
	
	int bytesNeeded = 15;
	cout<<"\n bytesNeeded = "<<bytesNeeded;
	PrintBinary(bytesNeeded);

	int allignmentNeeded = 16; //32
	cout<<"\n allignmentNeeded = "<<allignmentNeeded;
	PrintBinary(allignmentNeeded);
	
	int memoryAddressOrig = 100;
	cout<<"\n memoryAddressOrig = "<<memoryAddressOrig;
	PrintBinary(memoryAddressOrig);

	int allignedAddress = (memoryAddressOrig + allignmentNeeded-1)		;
	cout<<"\n bytesNeeded = "<<allignedAddress;
	PrintBinary(allignedAddress);

	int masking = ~(allignmentNeeded-1);
	cout<<"\n masking = "<<masking;
	PrintBinary(masking);

	allignedAddress = allignedAddress & masking;
	cout<<"\n allignedAddress = "<<allignedAddress;
	PrintBinary(allignedAddress);




	cout<<"\n Program Ended"<<endl;
}