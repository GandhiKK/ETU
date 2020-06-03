// ��������� ������ ��������� �������������� ���������, �������� � ����������� �����
// ����������� ���������� �� ���� ������� 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "st_templ.h"
using namespace std;
int main ( )
{	char a[100]; //
	int maxN;
// ��� ������� ��� ���������� ��������� ������� ����
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
//
cout << "������� ������������ ������ ����� =" << endl;
cin >> maxN;
cout << "������ ������������ ������ ����� =" << maxN << endl;

cout << "���� ������ � ����������� ������� ���������" << endl;
ifstream fin("postfix.txt");
fin >> noskipws;	// �������� �����������!

if (!fin ) {cout << "File not open for reading!\n"; return 1;}
int n1 = 100;
int n = 0;
while (n<n1 && fin >> a[n]) n++;
//����� ������
cout << "����� ������ = " << n << endl;
for (int i=0; i<n; i++) cout << a[i];
cout << endl;
cout << "���������!" << endl;

STACK<int> save(maxN);
    
for (int i = 0; i < n; i++)
      {	cout << "��� " << i+1 << " ������ = " << a[i] << endl;
        if (a[i] == '+') 
          save.push(save.pop() + save.pop());
        if (a[i] == '*') 
          save.push(save.pop() * save.pop());
        if ((a[i] >= '0') && (a[i] <= '9')) 
          save.push(0);
        while ((a[i] >= '0') && (a[i] <= '9')) 
			{save.push(10*save.pop() + (a[i++]-'0'));
			cout << "���_: " << i+1 << " ������ = " << a[i] << endl;
			} 
      }
    cout << save.pop() << endl;
  }       
