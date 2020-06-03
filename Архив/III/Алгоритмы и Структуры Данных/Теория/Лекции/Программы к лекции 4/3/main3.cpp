// Программа клиент вычисляет арифметическое выражение, заданное в постфиксной форме
// Ссылочная реализация стека в динамической (связанной) памяти
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "st_interface4.h"		// указание на интерфейсную часть СД "стек"
								
using namespace std;
using namespace st_modul4;

int main () {
	char a[100]; ///= {"12 11 +"}; //{'2',' ','5',' ','+'};
// это вставка для правильной кодировки русских букв
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
//
cout << "ввод строки с постфиксной записью выражения" << endl;
ifstream fin("postfix.txt");
fin >> noskipws;	// включить манипулятор!

if (!fin ) {cout << "File not open for reading!\n"; return 1;}
int n1 = 100;
int n = 0;
while (n<n1 && fin >> a[n]) n++; // ввод строки символов
//вывод строки символов
cout << "длина строки = " << n << endl;
for (int i=0; i<n; i++) cout << a[i];
cout << endl;
cout << "вычислить!" << endl;

Stack<int> s;
			// все символы кроме "0123456789+*" будут рассматриваться как разделители!
    for (int i = 0; i < n; i++)
	{	cout << "шаг: " << i+1 << " символ = " << a[i] << endl; // dem
        if (a[i] == '+') 
          s.push(s.pop2() + s.pop2());
        if (a[i] == '*') 
          s.push(s.pop2() * s.pop2());
        if ((a[i] >= '0') && (a[i] <= '9')) 
          s.push(0);
        while ((a[i] >= '0') && (a[i] <= '9')) 
			{s.push(10*s.pop2() + (a[i++]-'0'));		
			cout << "шаг_: " << i+1 << " символ = " << a[i] << endl;// dem
			} 
      }
    cout << "Результат =" << s.pop2() << endl;

	s.destroy();
	
return (0);
}

