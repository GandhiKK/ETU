//  ������: ����������� ���������� n!
//  ������� 2 � ������������� ����������
#include <iostream>
#include <windows.h>
using namespace std ;
unsigned short int i; // ����� ���������� (��� ������������)- ���������� ����������
int main ( )
{	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	unsigned int factr2 ( unsigned int );
	unsigned int fct_p ( unsigned int, unsigned int );
	void pr_bs (unsigned short int);
	
	unsigned int n, y;
	cout << "������� n >= 0 :\n" ; 
	cin >> n;
	cout << "������� n >= 0 :" << n << "\n" ;
//{n >= 0}
	i = 0;
	y = factr2 (n);
//(y = fact(n))
	cout << "����� ������������ ���������� -\n" ; 
	cout << "��������� " << n << "! = " << y << " \n" ;
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}
unsigned int fct_p ( unsigned int n, unsigned int z)
{   unsigned int y;
	i++;
	pr_bs(i);
	cout << "����� ���������� " << i << " � ���������� =" << n << "  (��������� z = " << z << ")\n" ;

	if ( n > 0 ) y = fct_p ( n-1, z*n);
	else y = z ; // ��� n=0

	pr_bs(i);
	cout << "���������� ���������� " << i << " � ���������� =" << n << ",  ��������� = " << y << "\n" ;
	i--;
	return y;
}
unsigned int factr2 ( unsigned int n )
{	return fct_p ( n, 1);
}
 
