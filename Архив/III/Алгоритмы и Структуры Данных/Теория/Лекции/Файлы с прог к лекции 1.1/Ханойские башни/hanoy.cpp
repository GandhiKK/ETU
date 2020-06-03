//  Пример: Ханойские башни
//  вариант 1 (с перечислимым типом) 
#include <iostream>
#include <windows.h>

using namespace std ;
enum col {a, b, c} ; // from, to, work
int main ( )
{	//для правильной кодировки русских букв:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	void Hanoi ( unsigned short, enum col, enum col, enum col); 
	void Step ( enum col, enum col);
	void print_col (enum col);
	enum col from, to, work;
	from = a, work = b, to = c;
	unsigned short n;

	cout << "Введите число дисков n >= 0 :\n" ; 
	cin >> n;
	cout << "Введено n >= 0 :" << n << "\n" ;
	cout << "Результат " << "\n" ;

	Hanoi (n, from, to, work );
	return 0;
}

void print_col (enum col s)
{	switch (s) {
	case a: cout << "a"; break;
	case b: cout << "b"; break;
	case c: cout << "c"; break;
	default: cout << "error of type col";
	}
} 

void Step ( col p, col q)
 {	print_col (p);
	cout << "->";
	print_col (q);
	cout << endl;
 }
void Hanoi( unsigned short n, enum col from,   enum col to,  enum col  work )
{			
		if (n==1) Step( from, to);
		else
		{	Hanoi( n-1, from,  work, to); // (1)
			Step ( from, to);
			Hanoi( n-1, work, to, from);  // (2)
		}
}
