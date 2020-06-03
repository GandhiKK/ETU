// ���������� ����� ���������
//  ������� 3 � "����������" (� ����������� �������� (���������))
#include <iostream>
#include <windows.h>
using namespace std ;
unsigned short int i; // ����� ���������� (��� ������������)
unsigned short int L; // ����� ������ (��� ������������)

int main ( )
{	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	void fib ( unsigned int, unsigned int &, unsigned int &);
	void pr_bs (unsigned short int);
	unsigned int n, x, y;
	cout << "������� n >= 0 :\n" ; 
	cin >> n;
	cout << "������� n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0; L = 0;
	fib (n, x, y);
//(y = fact(n)) && (x = n)
	cout << "��������� F(" << n << ") = " << x << " \n" ;
	cout << "End of the recursive program Fibonacci\n" ; 
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
void fib ( unsigned int n, unsigned int &u, unsigned int &v)
// ���������: u=F(n), v=F(n�1) ��� n>0}  
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
