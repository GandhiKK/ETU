//  Пример: Ханойские бащни
//  вариант 2 (колышки - целые 1..3)
#include <iostream>
using namespace std ;
int main ( )
{	void Hanoi ( unsigned short, unsigned short, unsigned short, unsigned short); 
	void Step ( unsigned short, unsigned short);
	unsigned  short from, work, to;
	from = 1, work = 2, to = 3;
	unsigned short n;
	
	cout << "Enter the number n >= 0 :\n" ; 
	cin >> n;
	cout << "Introduced the number n >= 0 :" << n << "\n" ;
	cout << "Result" << "\n" ;

	Hanoi (n, from, to, work );
	return 0;
}
void Step ( unsigned short p, unsigned short q)
 {	
	cout << p << "->" << q;
	cout << endl;
 }
void Hanoi( unsigned short n, unsigned short from,   unsigned short to,  unsigned short work )
{			
		if (n==1) Step( from, to);
		else
		{	Hanoi( n-1, from,  work, to); // (1)
			Step ( from, to);
			Hanoi( n-1, work, to, from);  // (2)
		}
}
