// Программа клиент вычисляет арифметическое выражение, заданное в постфиксной форме
// Непрерывная реализация на базе вектора 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "st_templ.h"
using namespace std;
int main ( )
{	char a[100]; //
	int maxN;
// это вставка для правильной кодировки русских букв
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
//
cout << "введите максимальный размер стека =" << endl;
cin >> maxN;
cout << "введен максимальный размер стека =" << maxN << endl;

cout << "ввод строки с постфиксной записью выражения" << endl;
ifstream fin("postfix.txt");
fin >> noskipws;	// включить манипулятор!

if (!fin ) {cout << "File not open for reading!\n"; return 1;}
int n1 = 100;
int n = 0;
while (n<n1 && fin >> a[n]) n++;
//вывод строки
cout << "длина строки = " << n << endl;
for (int i=0; i<n; i++) cout << a[i];
cout << endl;
cout << "вычислить!" << endl;

STACK<int> save(maxN);
    
for (int i = 0; i < n; i++)
      {	cout << "шаг " << i+1 << " символ = " << a[i] << endl;
        if (a[i] == '+') 
          save.push(save.pop() + save.pop());
        if (a[i] == '*') 
          save.push(save.pop() * save.pop());
        if ((a[i] >= '0') && (a[i] <= '9')) 
          save.push(0);
        while ((a[i] >= '0') && (a[i] <= '9')) 
			{save.push(10*save.pop() + (a[i++]-'0'));
			cout << "шаг_: " << i+1 << " символ = " << a[i] << endl;
			} 
      }
    cout << save.pop() << endl;
  }       
