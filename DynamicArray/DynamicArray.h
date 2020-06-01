/*  
 * Template κλάση δυναμικού πίνακα με Iterators
 * Έχει χρησιμοποιηθεί το keyword inline στις μικρές μεθόδους για λόγους performance κυρίως
 * Για την υλοποίηση του δυναμικού πίνακα συμβουλεύθηκα το βιβλίο του Stroustroup στο αντίστοιχο σημείο για το πώς δουλεύει ενα διάνυσμα(vector)
 * 
 * 
 * 
 * 
 * 
 */
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
class DynamicArray
{
private:
    T *m_data; //Ο ίδιος ο δείκτης των δεδομένων
    size_t m_capacity = 10; //Μεταβλητή που χρησιμοποιείται για να δεσμεύουμε παραπάνω δεδομένα απο τα πραγματικά του δυναμικου πίνακα
    size_t m_size = 0; //Μεταβλητή που κρατάει το πραγματικό μέγεθος του πίνακα
public:
    using size_type = size_t;
    using iterator = T *;
    using reference = T &;

    friend void swap(DynamicArray<T> &lhs, DynamicArray<T> &rhs)
    {
        lhs.swap(rhs);
    }
    void swap(DynamicArray<T> &rhs)
    {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_data, rhs.m_data);
    }
    inline DynamicArray() noexcept
    {
        m_data = new T[m_capacity];
    }
    
    inline DynamicArray<T> &operator=(const DynamicArray<T> &origin)
    {
        DynamicArray<T> cp(origin);
        swap(cp);
        return *this;
    }
    inline DynamicArray<T> &operator=(DynamicArray<T> &&origin)
    {
        swap(origin);
        return *this;
    }
    inline DynamicArray(const DynamicArray<T> &origin)
    {
        m_size = origin.m_size;
        m_capacity = origin.m_capacity;
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = origin.m_data[i];
    }
    
    inline void clear() noexcept
    {

        for (size_t i = 0; i < m_size; i++)
            m_data[i].~T();
        m_size = 0;
    }
    template <typename... Args>
    inline typename DynamicArray<T>::reference emplace_back(Args &&... args)
    {
        if (m_size == m_capacity)
        {
            m_capacity += m_capacity / 2 + 1;
            reallocate();
        }
        return m_data[m_size++] = std::move(T(std::forward<Args>(args)...));
    }
    inline void push_back(const T &val)
    {
        emplace_back(val);
    }
    DynamicArray<T>::iterator erase(DynamicArray<T>::iterator iter)
    {
        iterator _iter = &m_data[iter - m_data];
        _iter->~T();
        if (_iter + 1 != end())
        {
            move_storage(_iter, _iter + 1, m_size - (_iter - m_data));
            m_size -= 1;
        }
        else
        {
            _iter = &m_data[m_size - 2];
            pop_back();
        }

        return _iter;
    }
    inline void reallocate()
    {
        T *new_storage = new T[m_capacity];
        move_storage(new_storage, m_data, m_size);
        delete[] m_data;
        m_data = new_storage;
    }
    void move_storage(T *dest, T *from, size_type n)
    {
        if (dest < from)
        {
            T *_dest = dest, *_from = from;
            for (size_t i = 0; i < n - 1; i++)
                *_dest++ = std::move(*_from++);
        }
        else if (dest > from)
        {
            T *_dest = dest + n - 1, *_from = from + n - 1;
            for (size_t i = n; i > 0; i--)
                *_dest-- = std::move(*_from--);
        }
        else
            return;
    }
    inline typename DynamicArray<T>::iterator begin() noexcept
    {
        return m_data;
    }

    inline typename DynamicArray<T>::iterator end() const noexcept
    {
        return m_data + m_size;
    }

    size_t size()
    {
        return this->m_size;
    }

    size_t capacity()
    {
        return this->m_capacity;
    }

    T &operator[](size_t N)
    {
        return this->m_data[N];
    }
    T pop_back()
    {
        int prev_size = m_size - 1;
        T itm = m_data[prev_size];
        m_data[--m_size].~T();
        return itm;
    }

    void insert(const T &datum, size_t N)
    {
        if (N > this->m_size)
        {
            throw std::runtime_error("Insertion out of range");
        }

        if (this->m_size == this->m_capacity)
        {
            this->resize();
        }

        for (int i = this->m_size; i > N; --i)
        {
            this->m_data[i] = this->m_data[i - 1];
        }
        this->m_data[N] = datum;
        this->m_size += 1;
    }
    ~DynamicArray<T>()
    {
        delete[] m_data;
    }
    void remove(size_t N)
    {
        if (N > this->m_size)
        {
            throw std::runtime_error("Remove out of range");
        }

        for (int i = N; i + 1 < this->m_size; ++i)
        {
            this->m_data[i] = this->m_data[i + 1];
        }
        this->m_size -= 1;
    }
};
#endif
