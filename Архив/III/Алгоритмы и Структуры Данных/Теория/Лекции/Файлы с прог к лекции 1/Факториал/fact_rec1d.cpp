//  ������: ����������� ���������� n!
//  ������� � ������������� ����������
#include <iostream>
#include <windows.h>

using namespace std ;
//  unsigned short int i; // ����� ���������� (��� ������������)- ���������� ����������
int main ( )
{	//��� ���������� ��������� ������� ����:
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
		
	unsigned int factr1 ( unsigned int, unsigned short int );
	void pr_bs (unsigned short int);
	
	unsigned int n, y;
	unsigned short int i; // ����� ���������� (��� ������������)

	cout << "������� ����� ��������������� n :\n" ; 
	cin >> n;
	cout << "�������  ����� n = " << n << "\n" ;
//{n >= 0}
	i = 0;
	y = factr1 (n, i);
//{y = fact(n)}
	cout << "����� ������������ ���������� -\n" ; 
	cout << "��������� " << n << "! = " << y << " \n" ;
	return 0 ;
}
void pr_bs (unsigned short int i)
{   for (short j=1; j <=i; j++) cout <<"_";
}

unsigned int factr1 ( unsigned int n, unsigned short int i )
{   unsigned int y;
	i++;
	pr_bs(i);
	cout << "����� ���������� " << i << " � ���������� =" << n <<"\n" ;

	if ( n > 0 ) y = n*factr1(n-1, i);
	else y = 1 ; // ��� n=0

	pr_bs(i);
	cout << "���������� ���������� " << i << " � ���������� =" << n << ",  ��������� = " << y << "\n" ;
//	i--; // ���� ���������� ����������
	return y;
}