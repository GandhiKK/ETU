#include <iostream>
#include <memory>
#include <utility> 
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
    // (default) constructor
    explicit Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr) 
    { 
    }
    
    ~Array() noexcept = default; 
    
    const size_t size() const 
    { 
        return m_size; 
    }
    
    T& operator [](const size_t index)
    { 
        assert(index < m_size); 
        return m_array[index]; 
    }
    
    Array(const Array& arr) : m_size(arr.m_size), m_array(m_size ? new T[m_size]() : nullptr) 
    {
         std::copy(arr.m_array.get(), arr.m_array.get() + m_size, m_array.get());    
    }

    Array(Array &&arr) noexcept : m_size(std::move(arr.size)), m_array(std::move(arr.m_array))
    {
        arr.m_size = 0;
        arr.m_array = nullptr;
    }
    
    Array& operator=(Array arr)
    {
        std::swap(this->m_array, arr.m_array);
        std::swap(this->m_size, arr.m_size);        
        return *this;
    }
private:
    size_t m_size;
    std::unique_ptr<T[]> m_array;
};