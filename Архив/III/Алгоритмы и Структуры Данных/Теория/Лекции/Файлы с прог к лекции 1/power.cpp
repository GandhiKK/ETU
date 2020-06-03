//  Пример: рекурсивное вычисление степени a^n
//  вариант 1
#include <iostream>
#include <windows.h>
using namespace std ;
int main ( )
{	//для правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	float power (float, unsigned int);
	float a, y;
	unsigned int n;
	cout << "Введите вещественное a:" << endl ; 
	cin >> a;
	cout << "Введено a:" << a << "\n" ;
	cout << "Введите показатель степени n >= 0 :" << endl ; 
	cin >> n;
	cout << "Введено n >= 0 :" << n << "\n" ;
//{n >= 0} 
	y = power(a, n);
//(y = a^n)
	cout << "Конец рекурсивного вычисления -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
	return 0 ;
}
float power ( float a, unsigned int n)
{	float p;
	if (n == 0) return 1;
	else	{
			p = power (a, n/2);
			p = p*p;
			if ( n % 2) p = p*a;
			return p;
	};
}