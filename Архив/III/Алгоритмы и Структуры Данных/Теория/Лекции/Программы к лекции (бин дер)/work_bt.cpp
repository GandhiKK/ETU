// ������ ������ � ��� "�������� ������" (� ����������-��������� ���������)
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include "Btree.h"
#include <windows.h>
using namespace std ;
using namespace binTree_modul;

typedef unsigned int unInt; 

binTree enterBT ();
void outBT(binTree b);
void displayBT (binTree b, int n);
unInt hBT (binTree b);
unInt sizeBT (binTree b);
void printKLP (binTree b);
void printLKP (binTree b);
void printLPK (binTree b);

ifstream infile ("KLP.txt");
int main () 
{
	binTree b;
	
	SetConsoleCP(1251);			// ��� ������ ��������
	SetConsoleOutputCP(1251);	// ��� ������ ��������
	
	b = enterBT();
	cout << "�������� ������ � ���-�������������" << endl;
	outBT(b);
	
	cout << "�������� ������ (����������): " << endl;
	displayBT (b,1);
	cout << "������ ������ = " << hBT(b) << endl;
	cout << "������ (����� �����) ������ = " << sizeBT(b) << endl;
	
	cout << "�������� ������ � ���-�������: " << endl;
	printKLP(b);
	cout << endl;

	cout << "�������� ������ � ���-�������: " << endl;
	printLKP(b);
	cout << endl;

	cout << "�������� ������ � ���-�������: " << endl;
	printLPK(b);
	cout << endl;

	destroy (b);
	outBT(b);
	cout << endl;
return (0);
}

//---------------------------------------
	binTree enterBT ()
	{	char ch;
		binTree p, q;
		infile >> ch;
		if (ch=='/') return NULL;
		else {p = enterBT(); q = enterBT(); return ConsBT(ch, p, q);}
	}
//---------------------------------------
	void outBT(binTree b) 
	{	
		if (b!=NULL) {
			cout << RootBT(b);
			outBT(Left(b));
			outBT(Right(b));
		}
		else cout << '/';
	}

//---------------------------------------
	void displayBT (binTree b, int n)
	{	// n - ������� ����
		if (b!=NULL) {
			cout << ' ' << RootBT(b);
			if(!isNull(Right(b))) {displayBT (Right(b),n+1);}
			else cout << endl; // ����
			if(!isNull(Left(b))) {
				for (int i=1;i<=n;i++) cout << "  "; // ������
				displayBT (Left(b),n+1);}
		}
		else {};
	}
//---------------------------------------
	unInt hBT (binTree b)
	{
		if (isNull(b)) return 0;
		else return max (hBT (Left(b)), hBT(Right(b))) + 1;
	}

//---------------------------------------
	unInt sizeBT (binTree b)
	{
		if (isNull(b)) return 0;
		else return sizeBT (Left(b))+ sizeBT(Right(b)) + 1;
	}
//---------------------------------------
	void printKLP (binTree b)
	{	if (!isNull(b)) {
			cout << RootBT(b);
			printKLP (Left(b));
			printKLP (Right(b));
		}
	}
//---------------------------------------
	void printLKP (binTree b)
	{	if (!isNull(b)) {
			printLKP (Left(b));
			cout << RootBT(b);
			printLKP (Right(b));
		}
	}
//---------------------------------------
	void printLPK (binTree b)
	{	if (!isNull(b)) {
			printLPK (Left(b));
			printLPK (Right(b));
			cout << RootBT(b);
		}
	}

