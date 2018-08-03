#include <iostream>
using namespace std;

#define SIZE 15

template <typename T>
void Swap(T& x, T& y)
{	T temp = x; x = y; y = temp;	}

void Swap(int* x, int* y)
{	int temp = *x; *x = *y; *y = temp;	}

struct Node
{
	int data;
	Node* next;
	Node(int val , Node* next):data(val),next(next){}
};

void PrintArr(int arr[] , int size);
void PrintList(Node* head);
//========================================================
void BubbleSort(int arr[] , int size);
void InsertionSort(int arr[] , int size);
void SelectionSort(int arr[] , int size);
void MergeSort(int arr[] , int start , int end);
void MergeSortInList(int arr[], int size);
void QuickSort(int arr[] , int start , int end);
void QuickSortKthSmallestElement(int arr[] , int start , int end);

void MaxHeapSort(int arr[] , int size);

//=============================================================
void main()
{
	cout<<"\n Proram started"<<endl;
	int arr[15] = {256,34,74,765,15,345,511,2,634,5,987,9,434,11,119};
	PrintArr(arr , SIZE);
	cout<<"\n ********************************* "<<endl;
	//BubbleSort(arr,SIZE);
	//InsertionSort(arr,SIZE);
	//SelectionSort(arr,SIZE);

	//MergeSort(arr, 0 , SIZE-1);
	//MergeSortInList(arr, SIZE);			//TODO
	//QuickSort(arr,0 , SIZE-1);

	//QuickSortKthSmallestElement(arr,0 , SIZE-1);

	//TODO Dutch National Flag algorithm
	//https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/

	//TODO - VIMP // https://www.geeksforgeeks.org/iterative-quick-sort/

	MaxHeapSort(arr,SIZE);
	PrintArr(arr , SIZE);
	cout<<"\n Proram ended"<<endl;
}

//=============================================================
int ParentOfHeapElement( int pos)
{
	return (pos -1)/2; 
}

int LeftChildOfHeapElement( int pos)
{
	return 2*pos +1; 
}

int RightChildOfHeapElement( int pos)
{
	return 2*pos + 2; 
}

void Heapify(int arr[] , int last, int pos)	//place pos node into correct place.
{
	
	if ( ( 0 <= pos ) && ( pos <= last) ) 
	{
		int left = LeftChildOfHeapElement(pos);
		int right = RightChildOfHeapElement(pos);
		int large = pos;

		if( (left <=last) & (arr[left] > arr[large]) )
			large = left;
		
		if( (right <=last) & (arr[right] > arr[large]) )
			large = right;
	
		if(large != pos)
		{
			Swap(&arr[large] , &arr[pos]);
			Swap(&pos, &large);
			//cout<<"\n pos="<<pos <<", large ="<<large <<", last = "<<last;
			//cout<<"\n arr[pos]="<<arr[pos] <<", arr[large] ="<<arr[large] <<", arr[last] = "<<arr[last]<<endl;
			//PrintArr(arr,SIZE);
			Heapify(arr , last,  pos);
		}
	}
}

void MaxHeapSort(int arr[] , int size)
{
	cout<<"\n MaxHeapSort() started"<<endl;

	for(int i = (size/2) -1; i>=0 ; --i)
	{
		//cout<<"\n\n i =" << i ; 
		//BuildHeap(arr,size,i);
		Heapify(arr , size-1, i);	//place pos node into correct place.
		//cout<<"\n";
		//PrintArr(arr, size);
	}
	
	cout<<"\n Building Heap() : "<<endl;
	PrintArr(arr, size);
	
	cout<<"\n\n HeapSort() :"<<endl;

	for(int i = 0; i < (size-1) ; ++i)
	{
		Swap(arr[0] , arr[size-i -1]);	//move the max element to last
		//cout<<"\n ************* i = "<<i <<endl ;
		Heapify(arr,size-i-2,0);	//heapify remaining elements 
	}
	
	cout<<"\n MaxHeapSort() ended"<<endl;
}

//=============================================================

void QuickSortKthSmallestElement(int arr[] , int start , int end)
{

}

//=============================================================

int partition(int arr[] , int start , int end)
{
	int pivot = arr[end];
	int i = start ; int j = end-1;

	if(j <= i  ) return i;

	while ( i < j)
	{
		while( ( arr[i] < pivot) && (i < j) )
			++i;
		while ( (pivot < arr[j]) && (i < j) )
			--j;
		if(i<j)
			Swap( arr[i] , arr[j]);
		//++i ; --j;
	};
	if(arr[i]  > arr[end])
		Swap(arr[i] , arr[end]);

	cout<<"\n\n\n partition : start= "<<start <<", pivot = "<<i<<", pivot = "<< arr[i]<<", end = "<<end;
	PrintArr(arr+start , end-start+1);
	PrintArr(arr, SIZE);
	return i;
}

void QuickSort(int arr[] , int start , int end)
{
	//cout<<"\n QuickSort() started"<<endl;

	if(start < end)
	{
		int pivot = partition(arr , start , end);
		QuickSort(arr , start , pivot -1 );
		QuickSort(arr , pivot + 1, end);
	}

	//cout<<"\n QuickSort() ended"<<endl;
}




//=============================================================
void CreateListFromArr(int arr[], int size, Node** head)
{
	Node* last = *head = new Node(arr[0],NULL);
	for (int i =1 ; i< size ; ++i)
	{
		last->next = new Node(arr[i] , NULL); last = last->next;
	}
}

void MergeShortHelper(Node** head , int size)
{

}

void MergeSortInList(int arr[], int size)
{
	Node* head = NULL;
	CreateListFromArr(arr , size, &head);
	PrintList(head);
	Node* last = head;
	while(last->next != NULL)
		last = last->next;
	MergeShortHelper(&head , size);
}

void PrintList(Node* head)
{
	cout<<"\n List elements are: ";
	while (head)
	{
		cout<<" -> "<< head->data; 
		head = head->next;
	}
	cout<<endl;
}

//=============================================================
void Merge2Arr(int arr[] , int start1,int end1, int start2, int end2) //array from [start,mid]  and (mid,last]
{                             // 0  , 1  , 2      , 3       ,  4
							  //
	int size1 = end1 - start1 +1;
	int size2 = end2 - start2 +1;
	int *arr1 = new int[size1];
	int *arr2 = new int[size2];
	for (int x = start1 , y=0; x <= end1 ; ++x, ++y)
		arr1[y] = arr[x];
	for (int x = start2 , y = 0; x <= end2 ; ++x, ++y)
		arr2[y] = arr[x];

	int i = 0 ; 
	int j = 0; 
	int m = start1;

	while ( (i < size1) && (j < size2)  && (m <= end2))
	{
		if(arr1[i] < arr2[j] )
		{
			arr[m] = arr1[i];
			++i;
		}
		else
		{
			arr[m] = arr2[j];
			++j;
		}
		m++;
	}
	while ((i < size1) && (m <= end2))
	{
		arr[m] = arr1[i];
		++i;++m;
	}
	while ( (j < size2) && (m <= end2) )
	{
		arr[m] = arr2[j];
		++j;m++;
	}
}

void MergeSort(int arr[] , int start , int end)
{
	//cout<<"\n MergeSort() started"<<endl;
	int size = end-start+1 ;
	if(size < 2 )
		return;	//no need to merge 1 element
	if(size == 2)
	{
		if(arr[start] > arr[end])
			Swap(&arr[start] , & arr[end]);
	}
	else //size >=3
	{
		int mid = (size-1)/2;  
		//size = 3	=> mid = 1		0,1,2
		//size = 4	=> mid = 1		0,1,2,3
		//size = 5	=> mid = 2		0,1,2,3,4
		MergeSort(arr,start , start+mid);

		MergeSort(arr,start+mid + 1, end);

		Merge2Arr(arr, start , start+mid , start+mid+1, end);

		cout <<"\n \n\n *** start= "<<start <<", end = "<<end; 
		PrintArr(arr+start, size);
	}
	//cout<<"\n MergeSort() Ended"<<endl;
}

//=============================================================
void SelectionSort(int arr[] , int size)
{
	cout<<"\n SelectionSort() started"<<endl;
	for(int i=0 ; i<size ; ++i )
	{
		int minIndex = i;
		for( int j = i+1 ; j<size ; ++j )
		{
			if( arr[minIndex] > arr[j])
			{
				minIndex = j;
			}
		}
		if(minIndex!=i)
			Swap( &(arr[minIndex]), &(arr[i]) );
		cout<<"\n i = "<< i<< endl; PrintArr(arr,size);
	}
	cout<<"\n SelectionSort() Ended"<<endl;
}

//=============================================================
void InsertionSort(int arr[] , int size)
{
	cout<<"\n InsertionSort() started"<<endl;
	for(int i=1 ; i<size ; ++i )
	{
		for( int j = i ; j>0 ; --j )
		{
			if( arr[j-1] > arr[j])
			{
				Swap( &(arr[j]), &(arr[j-1]) );
			}
		}
	}
	cout<<"\n InsertionSort() Ended"<<endl;
}
//=============================================================
void BubbleSort(int arr[] , int size)
{
	cout<<"\n BubbleSort() started"<<endl;
	for(int i=0;i<(size-1);++i)
	{
		for(int j=0;j<(size-i-1);++j)
		{
			if( arr[j] > arr[j+1])
				Swap( &(arr[j]), &(arr[j+1]) );
		}
	}
	cout<<"\n BubbleSort() Ended"<<endl;
}
//=============================================================
void PrintArr(int arr[] , int size)
{
	cout<<"\n PrintArr() : "<<endl;
	for(int i=0;i<size;++i)
		cout<<" -> "<<arr[i];
}
//=============================================================


//=============================================================


//=============================================================

//=============================================================

//=============================================================