// интерфейс АТД "Стек" (ссылочная реализация в динамической памяти)с шаблонным классом
// тип элементов стека = Elem
// файл реализации подключается директивой #include в конце этого файла
#pragma once
namespace st_modul4
{

//-------------------------------------
	template <typename Elem>
	class Stack 
	{
	private:
		struct node 
		{ //
			Elem *hd;
			node *tl;
			// constructor
			node ()
			{hd = NULL; tl = NULL; 
			};
		};// end node
	
	node *topOfStack;

	public:
		Stack ()
			{ topOfStack = NULL;
			};
		Elem top (void);
		void pop (void);
		Elem pop2(void);
		void push (const Elem &x);
		bool isNull(void);
		void destroy (void); 
	};		// end - class Stack
}			// end - namespace st_modul4

#include "st_implementation4.h"		// указание на реализацию класса-шаблона
 
