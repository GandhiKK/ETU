#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

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

    list() : m_head(nullptr), m_tail(nullptr)
    {
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

    reference front()
        //Returns a reference to the first element in the container.
    {
      // implement this
        return m_head->value;
    }

    const_reference front() const
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

    const_reference back() const
        //Returns reference to the last element in the container.
    {
      // implement this
        return m_tail->value;
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

    void clear()
        //Erases all elements from the container.
    {
      // implement this   
        while (!(m_head == nullptr))
            pop_back();
    }

    bool empty() const
        //hecks if the container has no elements.
    {
      // implement this
        bool check = m_head == nullptr;
        return check;
    }

    size_t size() const
        //Returns the number of elements in the container.
    {
      // implement this
        unsigned int size_it = 0;
        node<Type>* temp = m_head;
        while (temp != nullptr) 
        {
            temp = temp->next;
            size_it++;            
        }
        return size_it;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik