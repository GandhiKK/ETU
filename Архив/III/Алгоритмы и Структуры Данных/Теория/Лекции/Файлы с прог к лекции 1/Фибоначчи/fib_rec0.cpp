// рекурсивно числа ‘ибоначчи
//  вариант 1.0 "в лоб" (без демонстрации)
#include <iostream>
#include <windows.h>
using namespace std ;
int main ( )
{	//дл€ правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	unsigned int fib ( unsigned int );
	unsigned int n, y;
	cout << "¬ведите n >= 0 :\n" ; 
	cin >> n;
	cout << "¬ведено n >= 0 :" << n << "\n" ;
//{n >= 0}
		y = fib (n);
//(y = fact(n)) && (x = n)
	cout << "вычислено F(" << n << ") = " << y << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
unsigned int fib ( unsigned int n)
{   if ( n > 1 ) return fib(n-1) + fib(n-2);
	else if (n==1) return 1;
	else return 0; // for n=0  (or n<0)
}
 