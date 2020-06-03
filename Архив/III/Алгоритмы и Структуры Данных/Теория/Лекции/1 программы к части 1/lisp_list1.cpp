#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
using namespace std ;
// линейные списки - рекурсивная обработка
// рабочий вариант для простой демонстрации на лекции (с рудиментами тестирования) 2012
	typedef char base;
	struct node {
	base *hd;
	node *tl;
	// constructor
	node ()
		{hd = NULL; tl = NULL; 
		}
	};
	typedef node *list;
	
	base head (list s);
	list tail (list s);
	list cons (base x, list s);
	void destroy (list s);
	list copy_list (list s);
	list concat_list (list s1, list s2);
	list reverse1 ( list s);
	list reverse2 ( list s);
	list rev2 ( list s, list w);

	void print_list ( list s );
	void write_list ( list s );
	list input_list (ifstream &infile);
	// доп. процедуры conc2 и conc3
	void conc2 (list &y, const list z);
	void conc3 (list &y, const list z);
	
int main ( )
{	SetConsoleCP(1251);			// для вывода кириллицы
	SetConsoleOutputCP(1251);	// для вывода кириллицы

	ifstream infile ("in_list.txt");
	if (!infile) cout << "Входной файл не открыт!" << endl;

	list lst;

	lst = input_list (infile);
	
	cout << "Итеративный вывод списка :\n";
	write_list (lst);

	cout << "Рекурсивный вывод списка :\n";
	print_list (lst);

	cout << "head = " << head (lst) << endl;
	cout << "tail = " ;
	list list2 = copy_list (tail (lst));
	print_list (list2);
	
	list list3 = copy_list (cons ( 'я', list2));
	print_list (list3);
	print_list (lst);
	print_list (list2);
	
	cout << "Concat_list: ";
	print_list (concat_list (lst, list2));
	
	cout << "Reverse1: ";
	print_list (reverse1 (list3));
	cout << "Reverse2: ";
	print_list (reverse2 (list3));
	
	print_list (list3);
	cout << "Conc2: ";
	conc2 (list3, list2);
	print_list (list3);
	
	cout << "Conc3: ";
	conc3 (list3, lst);
	print_list (list3);
	
	cout << "Destroy: ";
	destroy (list3);
	cout << "End of destroy" << endl;
	list3 = NULL;
	print_list ( list3);

	cout << "end!" << endl;


return 0;
}
//.......................
void print_list ( list s )
// рекурсивный вывод
{	if (s != NULL) {
		cout << *s->hd << " (" << int(*s->hd) <<") : ";
		print_list ( s->tl );
		}
	else { // s = nil
		cout << "nil\n";	
	}
}
//.........................
void write_list ( list s )
// итеративный вывод
{	list p = s;
	short i = 0;
	while (p != NULL) {
		i++;
		cout << i << " : " << *p->hd << "(" << int (*p->hd) << ") "<< endl;
		p = p->tl;
	}
}
//.........................
list input_list (ifstream &infile)
// ввод списка из файла - рекурсивно
{	char s; 
	if (infile >> s) return cons (s, input_list(infile));
	else return NULL;
}
//....................................
	base head (list s)
	{// PreCondition: not null (s)
		if (s != NULL) return *s->hd;
		else { cerr << "Error: head(nil) \n";
			exit(1);
		}
	}
//.......................................
	list tail (list s)
	{// PreCondition: not null (s)
		if (s != NULL) return s->tl;
		else { cerr << "Error: tail(nil) \n";
			exit(1);
		}
	}
//......................................
	list cons (base x, list s)
	{	list p;
		p = new node; 
		if ( p != NULL)	{ 	
			p->hd = new char;
			*p->hd = x;
			p->tl = s;
			return p;	
		}
		else {cerr << "Memory not enough\n";
			exit(1);
		}
	}
//...........................
	void destroy (list s)
	{
		if ( s != NULL) {
			cout << "del tail: \n" ;
			destroy ( tail(s));
			
			delete s->hd;
			cout << "del node: \n";
			delete s;
			// s = NULL;
		};
	}

//...........................
	list copy_list (list s)
	{	if (s != NULL) return cons ( head (s), copy_list (tail(s)));
		else return NULL;
	}
//.................................
	list concat_list (list s1, list s2)
	{	if (s1 == NULL) return s2;
		else return cons ( head (s1), concat_list ( tail (s1), s2));	
	}
//.......................................
	list reverse1 ( list s)
	{ 
		if(s == NULL) return NULL;
		else return concat_list ( reverse1 ( tail (s)), cons ( head(s), NULL) );
	}
//.........................
	list reverse2 ( list s)
	{
		return rev2 ( s, NULL);
	}
//.........................
	list rev2 ( list s, list w)
	{
		if (s == NULL) return w;
		else return rev2 (tail (s), cons ( head(s), w));
	}

//.........................
// процедура conc2 (y := y*z)
void conc2 (list &y, const list z)
{	
	if (y==NULL) {y = z;}
	else {
		conc2(y->tl, z);
	}
}
// процедура conc3 (итеративная)(y := y*z)
void conc3 (list &y, const list z)
{	if (y==NULL) y = z; 
	else { list q;
		q = y;
		while (q->tl != NULL) q = q->tl ;
		q->tl = z;
	}
}
	