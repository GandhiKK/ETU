// рекурсивно числа ‘ибоначчи
//  вариант 2 с накапливающими параметрами
#include <iostream>
#include <windows.h>
using namespace std ;
unsigned short int i; // номер экземпл€ра (дл€ демонстрации)
unsigned short int L; // номер уровн€ (дл€ демонстрации)

int main ( )
{	//дл€ правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	unsigned int fib_s ( unsigned int );
	unsigned int fib2 ( unsigned int, unsigned int, unsigned int );
	void pr_bs (unsigned short int);
	unsigned int n, y;
	cout << "¬ведите n >= 0 :\n" ; 
	cin >> n;
	cout << "¬ведено n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0; L = 0;
	y = fib_s (n);
//(y = fact(n)) && (x = n)
	cout << "вычислено F(" << n << ") = " << y << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
unsigned int fib2 ( unsigned int n, unsigned int a, unsigned int b)
// a, b - накапливающие параметры
{   unsigned int y;
	
	L++; i++;
	pr_bs(L);
	cout << "call level: " << L << ", ekz :" << i << " for argument =" << n <<"\n" ;

	if ( n == 1 )  y = a;   
	else y = fib2 (n-1, a+b, a);
	
	pr_bs(L);
	cout << "exit level: " << L << " from  ekz :" << i << " for argument =" << n << "\n" ;
	L--;
	i--;
	return y;
}
unsigned int fib_s ( unsigned int n)
{	return fib2 (n, 1, 0);
}
