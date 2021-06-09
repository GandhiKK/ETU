namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    template <typename N>
    friend class shared_ptr;  
      
    explicit shared_ptr(T *ptr = 0)
        : s_counter(new long(1)) 
        , s_ptr(ptr)
        //Constructs new shared_ptr.
    {   
    }

    ~shared_ptr()
        //If *this owns an object and it is the last shared_ptr owning it, 
        //the object is destroyed through the owned deleter.
    {
        if(isvalid())
        {
            (*s_counter)--; 
            if ((*s_counter) == 0) 
            { 
                delete s_counter; 
                delete s_ptr; 
            } 
            s_counter = nullptr;
            s_ptr = nullptr;
        }
    }

    shared_ptr(const shared_ptr<T> & other)
        : s_counter(other.s_counter)
        , s_ptr(other.s_ptr)
            //Constructs a shared_ptr which shares ownership of the object managed by other.
    {
        if(isvalid())
        {
            (*s_counter)++;
        }
    }
      
    template <typename N>
    shared_ptr(const shared_ptr<N> & other) 
        : s_counter(other.s_counter)
        , s_ptr(other.s_ptr)
    {
		if(isvalid())
        {
            (*s_counter)++;
        }
	}  

    shared_ptr& operator=(const shared_ptr<T> & other)
        //Shares ownership of the object managed by other.
    {
        shared_ptr temp(other);    // Constructor copies. Destructor destoryes.
        temp.swap(*this);       // Perform an exception safe transfer of state.
        return *this;     
    }
      
    template <typename N>
    shared_ptr& operator=(const shared_ptr<N> & other)
        //Shares ownership of the object managed by other.
    {
        shared_ptr temp(other);    // Constructor copies. Destructor destoryes.
        temp.swap(*this);       // Perform an exception safe transfer of state.
        return *this;     
    }  
      
    explicit operator bool() const
        //Checks if *this stores a non-null pointer.
    {
        return s_ptr != nullptr;   
    }

    T* get() const
        //Returns the stored pointer.
    {
        return s_ptr;
    }

    long use_count() const
        //Returns the number of different shared_ptr instances managing the current object. 
    {
        long count = 0;
        if (nullptr != s_ptr)
        {
            count = *s_counter;
        }
        return count;
    }

    T& operator*() const
        //The result of dereferencing the stored pointer.
    {
        return *s_ptr;
    }

    T* operator->() const
        //The stored pointer
    {
        return s_ptr;
    }

    void swap(shared_ptr& x) noexcept
        //Exchanges the contents of *this and x
    {
        std::swap(s_counter, x.s_counter);
        std::swap(s_ptr, x.s_ptr);
    }

    void reset(T *ptr = 0)
        //Replaces the managed object with an object pointed to by ptr.
    {
        if (ptr != s_ptr)
        {
            this->~shared_ptr();
            s_counter = new long(1);
        }
        s_ptr = ptr;                      
    } 
      
  private:
      bool isvalid() const {return (s_ptr != nullptr && s_counter != nullptr);}
            
  private:
    // data members
      long* s_counter;
      T* s_ptr;
  }; 
  
  template <typename T, typename Y>
  bool operator==(const shared_ptr<T>& ptr1, const shared_ptr<Y>& ptr2) 
  {
      return  ptr1.get() == ptr2.get();     
  }
} // namespace stepik