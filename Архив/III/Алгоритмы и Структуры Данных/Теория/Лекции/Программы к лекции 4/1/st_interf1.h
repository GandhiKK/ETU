// интерфейс АТД "Стек" (ссылочная реализация в динамической памяти)
namespace st_modul1
{

//-------------------------------------
	typedef int base;
	
	class Stack {
	private:
		struct node; 
/*	определение структуры будет дано в другом файле (продолжении namespace st_modul) - в файле Implementation,
	а здесь достаточно объявления "struct node;"
*/
	node *topOfStack;

	public:
		Stack ()
			{ topOfStack = NULL;
			};
		base top (void);
		void pop (void);
		base pop2(void);
		void push (const base &x);
		bool isNull(void);
		void destroy (void);
	};
} 