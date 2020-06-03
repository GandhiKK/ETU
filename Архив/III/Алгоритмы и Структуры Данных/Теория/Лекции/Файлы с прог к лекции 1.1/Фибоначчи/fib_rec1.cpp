// рекурсивно числа Фибоначчи
//  вариант 1.1 "в лоб" (с демонстрацией)
#include <iostream>
using namespace std ;
unsigned short int i; // номер экземпляра (для демонстрации)
unsigned short int L; // номер уровня (для демонстрации)

int main ( )
{	unsigned int fib ( unsigned int);
	void pr_bs (unsigned short int);
	unsigned int n, y;
	unsigned short int i;

	cout << "Enter n >= 0 :\n" ; 
	cin >> n;
	cout << "Introduced  n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0; L = 0;
	y = fib (n);
//(y = fact(n)) && (x = n)
	cout << "Calculated F(" << n << ") = " << y << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
unsigned int fib ( unsigned int n)
{   unsigned int y;
	unsigned short int i_in;	// копия номера этого экземпляра (для демонстрации)
	L++; i++;
	i_in = i;
	pr_bs(L);
	cout << "call level: " << L << ", ekz :" << i << " for argument =" << n <<"\n" ;

	if ( n > 1 )  y= fib(n-1) + fib(n-2);
	else if (n==1) y = 1;
	else y = 0; // for n=0

	pr_bs(L);
	cout << "exit level: " << L << " from  ekz :" << i_in << " for argument =" << n << "\n" ;
	L--;
	return y;
}
 