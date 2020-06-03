//  Пример: рекурсивное вычисление степени a^n
//  Бинарный алгоритм
//  вариант 1-6
//	последовательное преобразование рекурсивной версии в итеративную
//  через хвостовую рекурсию
//  ! вместо n/2 пробовать n >> 1, см. А.Степанов "От мат. к обобщ.прог."
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std ;
int main ( )
{	//для правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	float power (float, unsigned int);
	float power2 (float a, unsigned int n); // accumulator
	float power3 ( float a, unsigned int n, float b);
	float power4 ( float a, unsigned int n, float b); // accumulator + tail recursion
	float power5 ( float a, unsigned int n); // not recursion
	float power6 ( float a, unsigned int n); // not recursion 2 while

	float a, y;
	unsigned int n;
	cout << scientific << setprecision(10) <<  endl;// маниуляторы вывода

	cout << "Введите вещественное a:" << endl ; 
	cin >> a;
	cout << "Введено a:" << a << "\n" ;
	cout << "Введите показатель степени n >= 0 :" << endl ; 
	cin >> n; 
	cout << "Введено n >= 0 :" << n << "\n" ;
//{n >= 0} 
	y = power(a, n);
//(y = a^n)
	cout << "Конец рекурсивного вычисления 1 -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
//другая функция	
	y = power2(a, n);
	cout << "Конец рекурсивного вычисления 2 -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
//ещё другая функция	
	float b = 1;
	y = power3(a, n, b);
	cout << "Конец рекурсивного вычисления 3 -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
//ещё другая функция	
	b = 1;
	y = power4(a, n, b);
	cout << "Конец рекурсивного вычисления 4 -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
//ещё другая функция	
	y = power5(a, n);
	cout << "Конец рекурсивного вычисления 5 -\n" ; 
	cout << "Вычислено " << a << "^" << n << " = " << y << " \n" ;
//ещё другая функция	
	y = power6(a, n);
	cout << "Конец рекурсивного вычисления 6 -\n" ; 
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
// --------------------------------------
float power2 ( float a, unsigned int n)
{	float p;
	if (n == 0) return 1;
	else	{
			p = power2 (a*a, n/2);
			if ( n % 2) p = p*a;
			return p;
	};
}
// --------------------------------------
float power3 ( float a, unsigned int n, float b) // accumulator
{	float p;
	if (n == 0) return b;
	else	{
			if ( n % 2) p = power3 (a, n-1, b*a);
			else p = power3 (a*a, n/2, b);
			return p;
		};
}
// --------------------------------------
float power4 ( float a, unsigned int n, float b) // accumulator + tail recursion !
{	
	if (n == 0) return b;
	else	{
		if ( n % 2) {b = b*a; n = n-1;} 
		else {a = a*a; n = n/2;}
			return power4 (a, n, b);
	};
}
// --------------------------------------
float power5 ( float a, unsigned int n) // not recursion
{	float b = 1;	
	while(n!=0) {
		if (n % 2) {b = b*a; n = n-1;} 
		else {a = a*a; n = n/2;}
	}
	return b;
}
// --------------------------------------
float power6 ( float a, unsigned int n) // not recursion 2
{	float b = 1;	
	while(n!=0) {
		while( n % 2 == 0) {a = a*a; n = n/2;}
		n = n-1; b = b*a;
	}
	return b;
}