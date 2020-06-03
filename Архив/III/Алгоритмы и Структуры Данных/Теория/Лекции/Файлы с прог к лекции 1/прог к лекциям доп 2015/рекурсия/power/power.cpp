//  ������: ����������� ���������� ������� a^n
//  �������� ��������
//  ������� 1-6
//	���������������� �������������� ����������� ������ � �����������
//  ����� ��������� ��������
//  ! ������ n/2 ��������� n >> 1, ��. �.�������� "�� ���. � �����.����."
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std ;
int main ( )
{	//��� ���������� ��������� ������� ����:
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
	cout << scientific << setprecision(10) <<  endl;// ����������� ������

	cout << "������� ������������ a:" << endl ; 
	cin >> a;
	cout << "������� a:" << a << "\n" ;
	cout << "������� ���������� ������� n >= 0 :" << endl ; 
	cin >> n; 
	cout << "������� n >= 0 :" << n << "\n" ;
//{n >= 0} 
	y = power(a, n);
//(y = a^n)
	cout << "����� ������������ ���������� 1 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
//������ �������	
	y = power2(a, n);
	cout << "����� ������������ ���������� 2 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
//��� ������ �������	
	float b = 1;
	y = power3(a, n, b);
	cout << "����� ������������ ���������� 3 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
//��� ������ �������	
	b = 1;
	y = power4(a, n, b);
	cout << "����� ������������ ���������� 4 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
//��� ������ �������	
	y = power5(a, n);
	cout << "����� ������������ ���������� 5 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
//��� ������ �������	
	y = power6(a, n);
	cout << "����� ������������ ���������� 6 -\n" ; 
	cout << "��������� " << a << "^" << n << " = " << y << " \n" ;
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