//  Пример: рекурсивное сложение
//  вариант 1
#include <iostream>
//#include <fstream>
//#include <iomanip>
#include <windows.h>

using namespace std ;
typedef unsigned int uint;

int main ( )
{	
	//для правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//typedef unsigned int uint;

	uint addRec (uint, uint);

	uint m, n, p;
	cout << "Введите m >= 0 :" << endl ; 
	cin >> m;
	cout << "Введите n >= 0 :" << endl ; 
	cin >> n;
	cout << "Введены m >= 0 :" << m << " и n >= 0 :" << n << "\n" ;
//{m, n >= 0} 
	p = addRec(m,n);
//(p = m+n)
	cout << "Конец рекурсивного вычисления -\n" ; 
	cout << "вычислено " << m << " + " << n << " = " << p << " \n" ;
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
