// ���������� ����� ���������
//  ������� 1.0 "� ���" (��� ������������)
#include <iostream>
#include <windows.h>
using namespace std ;
int main ( )
{	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	unsigned int fib ( unsigned int );
	unsigned int n, y;
	cout << "������� n >= 0 :\n" ; 
	cin >> n;
	cout << "������� n >= 0 :" << n << "\n" ;
//{n >= 0}
		y = fib (n);
//(y = fact(n)) && (x = n)
	cout << "��������� F(" << n << ") = " << y << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
unsigned int fib ( unsigned int n)
{   if ( n > 1 ) return fib(n-1) + fib(n-2);
	else if (n==1) return 1;
	else return 0; // for n=0  (or n<0)
}
 