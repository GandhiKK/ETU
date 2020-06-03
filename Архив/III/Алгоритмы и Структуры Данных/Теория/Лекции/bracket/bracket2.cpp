// Program SyntaxAnalysisOfBracket;		
// вариант с синхронным выводом входной строки (до места ошибки включительно)
/*	Определения (синтаксис)
	Bracket = скобки, Round = кругл, Square = квадр 	
	скобки ::= квадр | кругл   					
	квадр ::= + | [кругл кругл]					
	кругл ::= – | (квадр квадр)					
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std ;

bool Bracket(ifstream &infile);
bool Round (ifstream &infile, char s);
bool Square (ifstream &infile, char s );
void Error (short k);

int main ( )
{	
	setlocale (0,"Rus");			// для MVC++ 2010

	ifstream infile ("in_seq5.txt");
	if (!infile) cout << "Входной файл не открыт!" << endl;

	cout << "Анализатор скобок:" << endl;
	bool b = Bracket (infile);

	cout << endl;
	if (b) cout << "ЭТО СКОБКИ!" << endl;
	else  cout <<"НЕТ, ЭТО НЕ СКОБКИ!" << endl;

	system("PAUSE");
	return 0;
}

bool Round (ifstream &infile, char s)
// кругл ::= – | (квадр квадр)  
// s - текущий символ входной строки
{	bool k;
	if (s == '-') { return true;} 
	else if ( s == '(' ) 
		{	//кругл ::= (квадр квадр)
			if (infile >> s) 
			{	cout << s; 
				k = Square (infile,s); 
				if (k)
				{	if (infile >> s) 
					{	cout << s; 
						k = Square (infile,s);} 
					else {Error (5); return false;} // квадр - пуст!
				}
				else return false; //первый квадр ошибочен

				if (k) // оба квадр правильны
					if (infile >> s) 
					{	cout << s; 
						return (s == ')');
					}
					else {Error (6); return false;}
				else return false;
			}
			else { Error (5); return false;} // квадр - пуст!
		}
		else  { Error(7); return false;} // не – и не ( }
}
// end of Round

bool Square (ifstream &infile, char s)
// квадр ::= + | [кругл кругл]  
// s - текущий символ входной строки
{	bool k;
	if (s == '+') return true;
	else if ( s == '[' ) 
	{	//квадр ::= [кругл кругл]
		if (infile >> s) 
		{	cout << s; 
			k = Round (infile,s); 
			if (k)
			{	if (infile >> s) 
				{	cout << s; 
					k = Round (infile,s);
				}
				else {Error (8); return false;} // кругл - пуст!
			}
			else return false; //первый кругл ошибочен

			if (k) // оба кругл правильны
				if (infile >> s) 
				{	cout << s; 
					return (s == ']');
				}
				else {Error (3); return false;}
			else return false;
		}
		else { Error (8); return false;} // кругл - пуст!
	}
	else  { Error(4); return false;} // не + и не [ }
}
// end of Square


bool Bracket(ifstream &infile)
{	char s;
	bool b;
	b = false;
	if (infile >> s)
	{	cout << s; 
		if ((s == '+') || (s == '[')) b = Square (infile, s);
		else 	if ((s == '-') || (s == '(')) b = Round (infile, s);
		else Error(2);   //недопустимый начальный символ
		infile >> s; 
		if (b && !infile.eof())  Error(1);	// лишние символы
		b = (b && infile.eof());
	}
	else Error (0);		// пустая входная строка
return b;
}

void Error (short k)
{
	cout << endl << "err#" << k << endl;
 switch (k) {
  	case 0: cout << "! - Пустая входная строка" << endl; break; 			//{Bracket} 
	case 1: cout << "! - Лишние символы во входной строке" << endl; break;	//{Bracket} 
	case 2: cout << "! - Недопустимый начальный символ" << endl; break;		//{Bracket}
	case 3: cout << "! - Отсутствует ']'." << endl;	break;					//{Square} 
	case 4: cout << "! - Отсутствует '+' или '['." << endl;	break;			//{Square}
	case 5: cout << "! - Очередной квадр - пуст." << endl; break;			//{Round} 
	case 6: cout << "! - Отсутствует ')'." << endl;	break;					//{Round} 
	case 7: cout << "! - Отсутствует – или (." << endl; break;				//{Round} 
	case 8: cout << "! - Очередной кругл - пуст." << endl; break;			//{Square}
	default : cout << "! - ...";break;										// ?
 };
}	
// end of Error
