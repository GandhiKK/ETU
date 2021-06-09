#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0)
    {
        // implement this
      m_first = nullptr;
	  m_last = nullptr;
      if (count > 0) 
      {
	      m_first = new Type[count]();
          if(!m_first)
              std::cout << "Error" << std::endl;
		  m_last = m_first + count;
	  }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last - first)
	{
        // implement this
	    std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.size())
        //используем концепцию делегирования конструкторов для создания начального массива
    {
        // implement this
      int count = 0;
        // Инициализация нашего начального массива значениями из списка инициализации
	  for (auto& element : init) 
      {
	      m_first[count] = element;
		  ++count;
	  }
    }

    vector(const vector& other) : vector(other.begin(), other.end())
    {
      // implement this
    }

    vector(vector&& other)
    {
      // implement this
        m_first = std::move(other.m_first);
	    m_last = std::move(other.m_last);
		other.m_first = nullptr;
		other.m_last = nullptr;
    }

    ~vector()
    {
      // implement this
      delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        // implement this
      if (&other == this)
            return *this;
        delete []m_first;
        m_size = other.size();
        m_first = new Type[m_size];
        for(size_t i = 0; i < m_size; i++)
            m_first[i] = other.m_first[i];
        m_last = m_first + m_size;
        return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
        if (&other == this)
            return *this;
        delete[] m_first;
        m_size = other.m_size;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_size = 0;
        other.m_first = nullptr;
        other.m_last = nullptr;
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
      //заменяет содержимое с копиями тех, кто в диапазоне [first, last)
    {
      // implement this
        size_t size = last - first;
			delete[] m_first;
			m_first = new Type[size];
			std::copy(first, last, m_first);
			m_last = m_first + size;
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:   
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

    /*  template<typename  T>
    void vector<T>::swap(vector<T> & v)
    {
        std::swap(m_size, v.m_size);
    }*/
      
  private:
    iterator m_first;
    iterator m_last;
    size_t m_size;
  };
}// namespace stepik