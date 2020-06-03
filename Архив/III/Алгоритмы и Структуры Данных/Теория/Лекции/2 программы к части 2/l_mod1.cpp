/*  использование модуля с АТД "Иерархический Список" .
Интерфейс модуля в заголовочном файле "l_intrfc.h" 
и его реализация (в отдельном файле l_impl.cpp) образуют
пространство имен namespace h_list
*/
#include <iostream>
#include <cstdlib>
#include "l_intrfc.h"
#include <windows.h>

using namespace std;
using namespace h_list;

lisp concat (const lisp y, const lisp z);

lisp reverse(const lisp s);
lisp rev(const lisp s,const lisp z);

lisp flatten1(const lisp s);

	int main ( )
{   SetConsoleCP(1251);			// для вывода кирилицы
	SetConsoleOutputCP(1251);	// для вывода кирилицы

	
	lisp s1, s2, s3;
	cout << boolalpha;
	cout << "введите list1:" << endl;
	read_lisp (s1);
	cout << "введен list1: " << endl;
	write_lisp (s1);
	cout << endl;
	
	cout << "flatten1 списка = " << endl;
	s3 = flatten1 (s1);
	write_lisp (s3);
	cout << endl;
	
	s2 = reverse(s1);
	cout << "для списка:" << endl;
	write_lisp (s1);	cout << endl;
	cout << "обращенный список есть:" << endl;
	write_lisp (s2);	cout << endl;

	cout << "destroy list3: " << endl;
	destroy ( s3);
	
	cout << "end! " << endl;
	return 0;
}
//...........................
	lisp concat (const lisp y, const lisp z)
	{
	if (isNull(y)) return copy_lisp(z);
	else return cons (copy_lisp(head (y)), concat (tail (y), z));
	} // end concat
// -----------------------
	lisp reverse(const lisp s)
	{	return(rev(s,NULL));	
	}
//........................
	lisp rev(const lisp s,const lisp z)
	{
		if(isNull(s)) return(z);
		else if(isAtom(head(s))) return(rev(tail(s), cons(head(s),z)));
		else return(rev(tail(s), cons(rev(head(s), NULL),z)));
	}
//........................
	lisp flatten1(const lisp s)
	{
		if (isNull(s)) return NULL;
		else if(isAtom(s)) return cons(make_atom(getAtom(s)),NULL);
		else //s - непустой список 
		if (isAtom(head(s))) return cons( make_atom(getAtom(head(s))),flatten1(tail(s)));
		else //Not Atom(Head(s))
			return concat(flatten1(head(s)),flatten1(tail(s)));
	} // end flatten1
