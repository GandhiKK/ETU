// рекурсивно числа ‘ибоначчи
//  вариант 3 с "процедурой" (с параметрами ссылками (выходными))
#include <iostream>
#include <windows.h>
using namespace std ;
unsigned short int i; // номер экземпл€ра (дл€ демонстрации)
unsigned short int L; // номер уровн€ (дл€ демонстрации)

int main ( )
{	//дл€ правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	void fib ( unsigned int, unsigned int &, unsigned int &);
	void pr_bs (unsigned short int);
	unsigned int n, x, y;
	cout << "¬ведите n >= 0 :\n" ; 
	cin >> n;
	cout << "¬ведено n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0; L = 0;
	fib (n, x, y);
//(y = fact(n)) && (x = n)
	cout << "вычислено F(" << n << ") = " << x << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
void fib ( unsigned int n, unsigned int &u, unsigned int &v)
// результат: u=F(n), v=F(nЦ1) при n>0}  
{   
	L++; i++;
	pr_bs(L);
	cout << "call level: " << L << ", ekz :" << i << " for argument =" << n <<"\n" ;

	if ( n == 1 ) { u = 1,  v = 0; } 
	else {	fib (n - 1, v, u);   // v=F(n-1), u=F(n-2)
			u = v + u ;	// u=F(n)} 
	}
	pr_bs(L);
	cout << "exit level: " << L << " from  ekz :" << i << " for argument =" << n << "\n" ;
	L--;
	i--;
}
