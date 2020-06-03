// ��������� ��� "����" (��������� ���������� � ������������ ������)� ��������� �������
// ��� ��������� ����� = Elem
// ���� ���������� ������������ ���������� #include � ����� ����� �����
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

#include "st_implementation4.h"		// �������� �� ���������� ������-�������
 
