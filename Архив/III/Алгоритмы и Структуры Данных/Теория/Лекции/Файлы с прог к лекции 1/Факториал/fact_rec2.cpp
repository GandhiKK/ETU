//  ѕример: рекурсивное вычисление n!
//  вариант 2 с накапливающим параметром
#include <iostream>
#include <windows.h>
using namespace std ;
unsigned short int i; // номер экземпл€ра (дл€ демонстрации)- глобальна€ переменна€
int main ( )
{	//дл€ правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	unsigned int factr2 ( unsigned int );
	unsigned int fct_p ( unsigned int, unsigned int );
	void pr_bs (unsigned short int);
	
	unsigned int n, y;
	cout << "¬ведите n >= 0 :\n" ; 
	cin >> n;
	cout << "¬ведено n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0;
	y = factr2 (n);
//(y = fact(n))
	cout << " онец рекурсивного вычислени€ -\n" ; 
	cout << "вычислено " << n << "! = " << y << " \n" ;
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
unsigned int fct_p ( unsigned int n, unsigned int z)
{   unsigned int y;
	i++;
	pr_bs(i);
	cout << "вызов экземпл€ра " << i << " с аргументом =" << n << "  (накоплено z = " << z << ")\n" ;

	if ( n > 0 ) y = fct_p ( n-1, z*n);
	else y = z ; // при n=0

	pr_bs(i);
	cout << "завершение экземпл€ра " << i << " с аргументом =" << n << ",  результат = " << y << "\n" ;
	i--;
	return y;
}
unsigned int factr2 ( unsigned int n )
{	return fct_p ( n, 1);
}
 
