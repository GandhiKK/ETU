#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator() : m_node(NULL) { }

    list_iterator(const list_iterator& other) : m_node(other.m_node) { }

    list_iterator& operator = (const list_iterator& other)
        //Copy assignment operator.
    {
      // implement this
        m_node = other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
        //Checks if the contents of lhs and rhs are equal
    {
      // implement this
        bool check = other.m_node == m_node;
        return check;
    }

    bool operator != (const list_iterator& other) const
        //Checks if the contents of lhs and rhs are equal
    {
      // implement this
        bool check = other.m_node != m_node;
        return check;
    }

    reference operator * ()
    {
      // implement this
        return m_node->value; //(returns Type &)
    }

    pointer operator -> ()
    {
      // implement this
        return &m_node->value; //(returns Type *)
    }

    list_iterator& operator ++ ()
        //Значение переменной х сначала увеличивается, а затем уже вычисляется.
    {
      // implement this
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
        //Компилятор создаёт временную копию переменной х, увеличивает оригинальный х (не копию), 
        //а затем возвращает копию.
    {
      // implement this
        list_iterator temp(m_node);
        m_node = m_node->next;
        return temp;
    }

  private:
    friend class list<Type>;
    list_iterator(node<Type>* p) : m_node(p) { }
    node<Type>* m_node;
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list() : m_head(nullptr), m_tail(nullptr) { }

    ~list()
        //Destructs the list.
    {
      // implement this    
        clear();
    }


    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
        //Appends the given element value to the end of the container.
    {
      // implement this
        if (!empty()) 
        {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;                
            return;
        }
        m_tail = m_head = new node<Type>(value, nullptr, nullptr);
    }

    void push_front(const value_type& value)
        //Prepends the given element value to the beginning of the container.
    {
      // implement this
        if (!empty()) 
        {
            m_head->prev = new node<Type>(value, m_head, nullptr);
			m_head = m_head->prev;				
			return;
		}
		m_tail = m_head = new node<Type>(value, nullptr, nullptr);
    }  
    
    void pop_front()
        //Removes the first element of the container. 
    {
      // implement this
        if (m_head->next != nullptr)
        {
            m_head->next->prev = nullptr;
            m_head = m_head->next; 
            return;
        }
        delete m_head;
        m_head = nullptr;
    } 
      
    iterator insert(iterator pos, const Type& value)
        //Inserts value before pos.
    {
      // implement this
        if(pos.m_node != nullptr && pos.m_node->prev != nullptr )
        {
            node<Type>* temp = pos.m_node->prev;
            pos.m_node->prev = new node<Type>(value, pos.m_node, temp);
            temp->next = pos.m_node->prev;
            return iterator(pos.m_node->prev);
        }
        else if (pos.m_node == nullptr) 
        {
            push_back(value);
            return iterator(m_tail);
        }
        else if (pos.m_node->prev == nullptr) 
        {
            push_front(value);
            return begin();
        }
    }

    iterator erase(iterator pos)
        //Removes the element at pos.
    {
      // implement this
        if(pos.m_node->next != nullptr  && pos.m_node->prev != nullptr )
        {
            node<Type>* temp = pos.m_node;
            delete pos.m_node;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            return temp->next;
        }
        if (pos.m_node->next == nullptr) 
        {
            pop_back();
            return iterator(m_tail);
        }
        if (pos.m_node->prev == nullptr) 
        {
            pop_front();
            return begin();
        }
    }

    reference front()
        //Returns a reference to the first element in the container.
    {
      // implement this
        return m_head->value;
    }

    reference back()
        //Returns reference to the last element in the container.
    {
      // implement this
        return m_tail->value;
    }
  private:
      void clear()
        //Erases all elements from the container.
    {
      // implement this   
        while (!(m_head == nullptr))
            pop_back();
    }
      
    bool empty() const
        //Checks if the container has no elements.
    {
      // implement this
        bool check = m_head == nullptr;
        return check;
    } 
      
    void pop_back()
        //Removes the last element of the container.
    {
      // implement this
        if (m_tail->prev != nullptr)
        {
            m_tail->prev->next = nullptr;
            node<Type>* temp = m_tail->prev;
            delete m_tail;
            m_tail = temp;
            return;
        }
        delete m_tail;
        m_tail = m_head = nullptr;
    }
  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik