#include <iostream>
using namespace std;

//login.name/ftp/pub/docs/programming_languages/cpp/cffective_cpp/MEC/MI30_FR.HTM

class Array2D
{
	
	
	class Array1D;

	int m_row;
	Array1D* m_Array1D;			//proxy objects

public:
	//==============================================================================================
			class Array1D{			//proxy class
				int m_col;
				int* m_arr;
			public:
				Array1D(): m_col(0) , m_arr(NULL){
					cout<<"\n Array1D::Array1D() "<<endl;
				}

				void Init(int col ){
					m_col = col;
					m_arr = new int[col];
					cout<<"\n Array1D::Init(int col) , col="<<col<<endl;
				}
		
				~Array1D(){
					delete[] m_arr;
					cout<<"\n Array1D::~Array1D() , col="<<m_col<<endl;
				}

				int& operator[](int col)	{
					cout<<"\n int& Array1D::operator[](int row) , col="<<m_col<<endl;
					return m_arr[col];
				}

				const int& operator[](int col)	const {
					cout<<"\n const int& Array1D::operator[](int col)	const  , col="<<m_col<<endl;
					return m_arr[col];
				}
			};//end of Array1D
	//==============================================================================================

	Array2D(int row, int col): m_row(row)	{
		cout<<"\n Array2D::Array2D(int row, int col) , row="<<row<<", col="<<col<<endl;
		m_Array1D = new Array1D[m_row];
		for(int i = 0; i< row; ++i)
			m_Array1D[i].Init(col);	
	}
	~Array2D(){
		cout<<"\n Array2D::~Array2D() , row="<<m_row<<endl;
		delete[] m_Array1D ;
	}

	Array1D& operator[](int row)	{
		cout<<"\n Array1D& Array2D::operator[](int row) , row="<<m_row<<endl;
		return m_Array1D[row];
	}

	const Array1D& operator[](int row)	const {
		cout<<"\n const Array1D& Array2D::operator[](int row) const , row="<<m_row<<endl;
		return m_Array1D[row];
	}
};//end of Array2D



void main()
{
	cout<<"\n Program Started"<<endl;

	Array2D arr(3,4);
	arr[2][3] = 100;
	//(arr[2])[3] => (*Array1D)[3] => int

	cout<<"\n arr[2][3] = "<<arr[2][3]<<endl;

	const Array2D& r_arr = arr;
	//r_arr[2][3] = 100;
	cout<<"\n r_arr[2][3] = "<<r_arr[2][3]<<endl;

	cout<<"\n Program ended"<<endl;
}