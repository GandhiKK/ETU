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
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    list() : m_head(nullptr), m_tail(nullptr) { }

    ~list()
        //Destructs the list.
    {
      // implement this    
        clear();
    }

    list(const list& other)
        //Copy constructor.
    {
      // implement this
        m_head = nullptr;
        m_tail = nullptr;
        node<Type>* ptr = other.m_head;
        while (ptr != nullptr) 
        {
            push_back(ptr->value);
            ptr = ptr->next;
        }
    }

    list(list&& other)
        //Move constructor.
    {
      // implement this
        m_head = other.m_head;
        m_tail = other.m_tail;        
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    list& operator= (const list& other)
        //Copy assignment operator.
    {
      // implement this
        if (&other == this)
            return *this;
        clear();
        node<Type>* temp = other.m_head;
        while (temp != nullptr) 
        {
            push_back(temp->value);
            temp = temp->next;
        }
        return *this;
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