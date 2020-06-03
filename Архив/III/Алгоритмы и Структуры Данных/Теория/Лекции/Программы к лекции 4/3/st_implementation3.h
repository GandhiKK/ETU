// Implementation - Реализация АТД "Стек"(ссылочная реализация в динамической памяти)
// с шаблонным классом
// тип элементов стека = Elem
// этот файл реализации подключается из интерфейсного файла "st_interface4.h"(#include) 
#include <iostream>
#include <cstdlib>
//#include "st_interface4.h" // можно использовать только вместе с #pragma once в интерфейсном файле
using namespace std ;

namespace st_modul4
{
	template <typename Elem>
	Elem Stack<Elem>::top (void) 
	{// PreCondition: not null	
		if (topOfStack == NULL) { cerr << "Error: top(null) \n"; exit(1); }
		else return *topOfStack->hd;
	}
//-------------------------------------
		template <typename Elem>
		void Stack<Elem>::pop (void)
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
		else 
		{	node *oldTop = topOfStack;
			topOfStack = topOfStack->tl;
			delete oldTop->hd;
			delete oldTop;
		}
	}
//-------------------------------------
		template <typename Elem>	
		Elem Stack<Elem>::pop2(void)
	{// PreCondition: not null
		if (topOfStack == NULL) { cerr << "Error: pop(null) \n"; exit(1); }
		else 
		{	node *oldTop = topOfStack;
			Elem r = *topOfStack->hd;
			topOfStack = topOfStack->tl;
			delete oldTop->hd;
			delete oldTop;
			return r;
		}
	}
//-------------------------------------
	template <typename Elem>	
	void Stack<Elem>::push (const Elem &x)
	{	node *p;
		p = topOfStack;
		topOfStack = new node; 
		if ( topOfStack != NULL)	{ 	
			topOfStack->hd = new Elem;
			*topOfStack->hd = x;
			//cout << "push -> " << x << endl; //dem
			topOfStack->tl = p;
		}
		else {cerr << "Memory not enough\n"; exit(1);}
	}
//-------------------------------------
	template <typename Elem>	
	bool Stack<Elem>::isNull(void)
	{	return (topOfStack == NULL) ;
	}
//-------------------------------------
	template <typename Elem>	
	void Stack<Elem>::destroy (void)
	{	while ( topOfStack != NULL) {
			pop();	
		}
	}
} // end of namespace st_modul4 (stack)