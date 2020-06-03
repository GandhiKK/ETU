// ��������� ������ ��������� �������������� ���������, �������� � ����������� �����
// ��������� ���������� ����� � ������������ (���������) ������
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "st_interface4.h"		// �������� �� ������������ ����� �� "����"
								
using namespace std;
using namespace st_modul4;

int main () {
	char a[100]; ///= {"12 11 +"}; //{'2',' ','5',' ','+'};
// ��� ������� ��� ���������� ��������� ������� ����
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
//
cout << "���� ������ � ����������� ������� ���������" << endl;
ifstream fin("postfix.txt");
fin >> noskipws;	// �������� �����������!

if (!fin ) {cout << "File not open for reading!\n"; return 1;}
int n1 = 100;
int n = 0;
while (n<n1 && fin >> a[n]) n++; // ���� ������ ��������
//����� ������ ��������
cout << "����� ������ = " << n << endl;
for (int i=0; i<n; i++) cout << a[i];
cout << endl;
cout << "���������!" << endl;

Stack<int> s;
			// ��� ������� ����� "0123456789+*" ����� ��������������� ��� �����������!
    for (int i = 0; i < n; i++)
	{	cout << "���: " << i+1 << " ������ = " << a[i] << endl; // dem
        if (a[i] == '+') 
          s.push(s.pop2() + s.pop2());
        if (a[i] == '*') 
          s.push(s.pop2() * s.pop2());
        if ((a[i] >= '0') && (a[i] <= '9')) 
          s.push(0);
        while ((a[i] >= '0') && (a[i] <= '9')) 
			{s.push(10*s.pop2() + (a[i++]-'0'));		
			cout << "���_: " << i+1 << " ������ = " << a[i] << endl;// dem
			} 
      }
    cout << "��������� =" << s.pop2() << endl;

	s.destroy();
	
return (0);
}

