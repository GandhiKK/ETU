//  ������: ����������� ���������� n!
//  ������� 1
#include <iostream>
//#include <fstream>
//#include <iomanip>
#include <windows.h>

using namespace std ;
int main ( )
{	
	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned int factr1 ( unsigned int );

	unsigned int n, y;
	cout << "������� n >= 0 :" << endl ; 
	cin >> n;
	cout << "������� n >= 0 :" << n << "\n" ;
//{n >= 0} 
	y = factr1 (n);
//(y = fact(n))
	cout << "����� ������������ ���������� -\n" ; 
	cout << "��������� " << n << "! = " << y << " \n" ;
	return 0 ;
}
unsigned int factr1 ( unsigned int n )
{
	if ( n > 0 ) return n*factr1(n-1);
	else return 1 ; // ��� n=0
}