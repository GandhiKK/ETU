// ��������� ��� "����" (��. ������� - Sedgewick) 
// ��������� �����. ��� ��������� ��������...
// � ���������, � ���������� � ���� ������������ ����� 

template <class Item>
class STACK 
  {
    private:
      Item *s; int N; int N1; // my N1
    public:
      STACK(int maxN)
        { s = new Item[maxN]; N = 0; N1 = maxN;}  // my N1
      int empty() const
        { return N == 0; }
      void push(Item elem)
        { s[N++] = elem; 		
			if (N > N1) cout << "������!!!" << endl; // my N1
		}
      Item pop()
        { return s[--N]; }
  };
///}
