// ��������� ��� "����" (��������� ���������� � ������������ ������)
namespace st_modul1
{

//-------------------------------------
	typedef int base;
	
	class Stack {
	private:
		struct node; 
/*	����������� ��������� ����� ���� � ������ ����� (����������� namespace st_modul) - � ����� Implementation,
	� ����� ���������� ���������� "struct node;"
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