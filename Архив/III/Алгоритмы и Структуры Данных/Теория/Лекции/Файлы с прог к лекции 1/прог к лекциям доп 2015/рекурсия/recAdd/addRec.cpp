//  ������: ����������� ��������
//  ������� 1
#include <iostream>
//#include <fstream>
//#include <iomanip>
#include <windows.h>

using namespace std ;
typedef unsigned int uint;

int main ( )
{	
	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//typedef unsigned int uint;

	uint addRec (uint, uint);

	uint m, n, p;
	cout << "������� m >= 0 :" << endl ; 
	cin >> m;
	cout << "������� n >= 0 :" << endl ; 
	cin >> n;
	cout << "������� m >= 0 :" << m << " � n >= 0 :" << n << "\n" ;
//{m, n >= 0} 
	p = addRec(m,n);
//(p = m+n)
	cout << "����� ������������ ���������� -\n" ; 
	cout << "��������� " << m << " + " << n << " = " << p << " \n" ;
	return 0 ;
}
// 
uint addRec(uint m, uint n)  
{
	if ( m == 0 ) return n;
	else if ( n == 0 ) return m;
		else /* m != 0 & n != 0 */
			return addRec (m-1,n+1);
			//addRec (--m,++n);
}		
