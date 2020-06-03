// Program SyntaxAnalysisOfBracket;		
// ������� � ���������� ������� ������� ������ (�� ����� ������ ������������)
/*	����������� (���������)
	Bracket = ������, Round = �����, Square = ����� 	
	������ ::= ����� | �����   					
	����� ::= + | [����� �����]					
	����� ::= � | (����� �����)					
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
	setlocale (0,"Rus");			// ��� MVC++ 2010

	ifstream infile ("in_seq5.txt");
	if (!infile) cout << "������� ���� �� ������!" << endl;

	cout << "���������� ������:" << endl;
	bool b = Bracket (infile);

	cout << endl;
	if (b) cout << "��� ������!" << endl;
	else  cout <<"���, ��� �� ������!" << endl;

	system("PAUSE");
	return 0;
}

bool Round (ifstream &infile, char s)
// ����� ::= � | (����� �����)  
// s - ������� ������ ������� ������
{	bool k;
	if (s == '-') { return true;} 
	else if ( s == '(' ) 
		{	//����� ::= (����� �����)
			if (infile >> s) 
			{	cout << s; 
				k = Square (infile,s); 
				if (k)
				{	if (infile >> s) 
					{	cout << s; 
						k = Square (infile,s);} 
					else {Error (5); return false;} // ����� - ����!
				}
				else return false; //������ ����� ��������

				if (k) // ��� ����� ���������
					if (infile >> s) 
					{	cout << s; 
						return (s == ')');
					}
					else {Error (6); return false;}
				else return false;
			}
			else { Error (5); return false;} // ����� - ����!
		}
		else  { Error(7); return false;} // �� � � �� ( }
}
// end of Round

bool Square (ifstream &infile, char s)
// ����� ::= + | [����� �����]  
// s - ������� ������ ������� ������
{	bool k;
	if (s == '+') return true;
	else if ( s == '[' ) 
	{	//����� ::= [����� �����]
		if (infile >> s) 
		{	cout << s; 
			k = Round (infile,s); 
			if (k)
			{	if (infile >> s) 
				{	cout << s; 
					k = Round (infile,s);
				}
				else {Error (8); return false;} // ����� - ����!
			}
			else return false; //������ ����� ��������

			if (k) // ��� ����� ���������
				if (infile >> s) 
				{	cout << s; 
					return (s == ']');
				}
				else {Error (3); return false;}
			else return false;
		}
		else { Error (8); return false;} // ����� - ����!
	}
	else  { Error(4); return false;} // �� + � �� [ }
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
		else Error(2);   //������������ ��������� ������
		infile >> s; 
		if (b && !infile.eof())  Error(1);	// ������ �������
		b = (b && infile.eof());
	}
	else Error (0);		// ������ ������� ������
return b;
}

void Error (short k)
{
	cout << endl << "err#" << k << endl;
 switch (k) {
  	case 0: cout << "! - ������ ������� ������" << endl; break; 			//{Bracket} 
	case 1: cout << "! - ������ ������� �� ������� ������" << endl; break;	//{Bracket} 
	case 2: cout << "! - ������������ ��������� ������" << endl; break;		//{Bracket}
	case 3: cout << "! - ����������� ']'." << endl;	break;					//{Square} 
	case 4: cout << "! - ����������� '+' ��� '['." << endl;	break;			//{Square}
	case 5: cout << "! - ��������� ����� - ����." << endl; break;			//{Round} 
	case 6: cout << "! - ����������� ')'." << endl;	break;					//{Round} 
	case 7: cout << "! - ����������� � ��� (." << endl; break;				//{Round} 
	case 8: cout << "! - ��������� ����� - ����." << endl; break;			//{Square}
	default : cout << "! - ...";break;										// ?
 };
}	
// end of Error
